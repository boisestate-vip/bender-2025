
#include "gost.h"
#include "base64.h"
#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#if __RDRND__
#include <immintrin.h>
#endif

/* As defined in ГОСТ Р 34.12─2015 */
const gost_s_box gost_default_s_box = {
     0x1857cb6c, 
     0x7edf8384, 
     0xe2f52526, 
     0xd56a1832, 
     0x0698d29a,
     0x59214fa5,
     0x81c6fa5b,
     0x3cad6dc9,
     0x4fb07e1e,
     0xf47901e8,
     0xab83a74d,
     0x601e5477,
     0x9d4b3cb0,
     0xca34e9d3,
     0xb3e2960f,
     0x270cb0f1 
};

uint64_t gost_encrypt_step(const uint64_t Tp, const gost_key X, const gost_s_box K) {

   /* initialization */
   uint32_t N1, N2, CM1, CM2, R;
   N1 = Tp & 0xffffffff;
   N2 = Tp >> 32;

   uint32_t W[32] = { X[0], X[1], X[2], X[3], X[4], X[5], X[6], X[7], 
                      X[0], X[1], X[2], X[3], X[4], X[5], X[6], X[7], 
                      X[0], X[1], X[2], X[3], X[4], X[5], X[6], X[7], 
                      X[7], X[6], X[5], X[4], X[3], X[2], X[1], X[0] };

   /* rounds 1 - 31 */
   for (int i = 0; i < 31; ++i) {

      CM1 = N1 + W[i];

      R = (K[(CM1&0x0000000f)>> 0]&0x0000000f) | (K[(CM1&0x000000f0)>> 4]&0x000000f0) |
          (K[(CM1&0x00000f00)>> 8]&0x00000f00) | (K[(CM1&0x0000f000)>>12]&0x0000f000) |
          (K[(CM1&0x000f0000)>>16]&0x000f0000) | (K[(CM1&0x00f00000)>>20]&0x00f00000) |
          (K[(CM1&0x0f000000)>>24]&0x0f000000) | (K[(CM1&0xf0000000)>>28]&0xf0000000);

      R = ((R << 11) | (R >> 21));

      CM2 = R ^ N2;

      N2 = N1;
      N1 = CM2;

   }

   /* final round */
   CM1 = N1 + W[31];

   R = (K[(CM1&0x0000000f)>> 0]&0x0000000f) | (K[(CM1&0x000000f0)>> 4]&0x000000f0) |
       (K[(CM1&0x00000f00)>> 8]&0x00000f00) | (K[(CM1&0x0000f000)>>12]&0x0000f000) |
       (K[(CM1&0x000f0000)>>16]&0x000f0000) | (K[(CM1&0x00f00000)>>20]&0x00f00000) |
       (K[(CM1&0x0f000000)>>24]&0x0f000000) | (K[(CM1&0xf0000000)>>28]&0xf0000000);

   R = ((R << 11) | (R >> 21));

   CM2 = R ^ N2;

   N2 = CM2;

   /* finished block */
   return (uint64_t)(((uint64_t)N2 << 32) | (uint64_t)N1);
}

uint64_t gost_decrypt_step(const uint64_t Tp, const gost_key X, const gost_s_box K) {

   /* initialization */
   uint32_t N1, N2, CM1, CM2, R;
   N1 = Tp & 0xffffffff;
   N2 = Tp >> 32;

   uint32_t W[32] = { X[0], X[1], X[2], X[3], X[4], X[5], X[6], X[7], 
                      X[7], X[6], X[5], X[4], X[3], X[2], X[1], X[0], 
                      X[7], X[6], X[5], X[4], X[3], X[2], X[1], X[0], 
                      X[7], X[6], X[5], X[4], X[3], X[2], X[1], X[0] };

   /* rounds 1 - 31 */
   for (int i = 0; i < 31; ++i) {

      CM1 = N1 + W[i];

      R = (K[(CM1&0x0000000f)>> 0]&0x0000000f) | (K[(CM1&0x000000f0)>> 4]&0x000000f0) |
          (K[(CM1&0x00000f00)>> 8]&0x00000f00) | (K[(CM1&0x0000f000)>>12]&0x0000f000) |
          (K[(CM1&0x000f0000)>>16]&0x000f0000) | (K[(CM1&0x00f00000)>>20]&0x00f00000) |
          (K[(CM1&0x0f000000)>>24]&0x0f000000) | (K[(CM1&0xf0000000)>>28]&0xf0000000);

      R = ((R << 11) | (R >> 21));

      CM2 = R ^ N2;

      N2 = N1;
      N1 = CM2;

   }

   /* final round */
   CM1 = N1 + W[31];

   R = (K[(CM1&0x0000000f)>> 0]&0x0000000f) | (K[(CM1&0x000000f0)>> 4]&0x000000f0) |
       (K[(CM1&0x00000f00)>> 8]&0x00000f00) | (K[(CM1&0x0000f000)>>12]&0x0000f000) |
       (K[(CM1&0x000f0000)>>16]&0x000f0000) | (K[(CM1&0x00f00000)>>20]&0x00f00000) |
       (K[(CM1&0x0f000000)>>24]&0x0f000000) | (K[(CM1&0xf0000000)>>28]&0xf0000000);

   R = ((R << 11) | (R >> 21));

   CM2 = R ^ N2;

   N2 = CM2;

   /* finished block */
   return (uint64_t)(((uint64_t)N2 << 32) | (uint64_t)N1);
}

int gost_encrypt(uint64_t * blocks, size_t block_count, struct gost_opt * opts) {

   if (opts->s_box == NULL) 
      opts->s_box = &gost_default_s_box;

   switch (opts->mode) {

      case GOSTM_ECB:

         for (int i = 0; i < block_count; ++i)
            blocks[i] = gost_encrypt_step(blocks[i],*opts->key,*opts->s_box);

         break;

      case GOSTM_CE:

         {
            uint64_t CM5, N12, Gc;
            uint32_t N3, N4;

            N12 = opts->initialization_const;

            N12 = gost_encrypt_step(N12,*opts->key,*opts->s_box);

            N3 = N12 & 0xffffffff;
            N4 = N12 >> 32;

            for (int i = 0; i < block_count; ++i) {

               N4 = (N4 + GOST_C1)%UINT_MAX;
               N3 = (N3 + GOST_C2);

               N12 = ((uint64_t)(((uint64_t)N4 << 32) | (uint64_t)N3));

               Gc = gost_encrypt_step(N12,*opts->key,*opts->s_box);

               blocks[i] ^= Gc;
            }

         }
         break;

      case GOSTM_CF:

         {
            uint64_t CM5, N12;
            uint32_t N3, N4;

            N12 = opts->initialization_const;

            N12 = gost_encrypt_step(N12,*opts->key,*opts->s_box);

            blocks[0] ^= N12;

            for (int i = 1; i < block_count; ++i) {
               N12 = blocks[i-1];

               N12 = gost_encrypt_step(N12,*opts->key,*opts->s_box);

               blocks[i] ^= N12;
            }

         }

         break;

      default:
         errno = ENOTSUP;
         return -1;
         break;
   }

   return 0;
}

int gost_decrypt(uint64_t * blocks, size_t block_count, struct gost_opt * opts) {

   if (opts->s_box == NULL) 
      opts->s_box = &gost_default_s_box;

   switch (opts->mode) {

      case GOSTM_ECB:

         for (int i = 0; i < block_count; ++i)
            blocks[i] = gost_decrypt_step(blocks[i],*opts->key,*opts->s_box);

         break;

      case GOSTM_CE:

         {
            uint64_t CM5, N12, Gc;
            uint32_t N3, N4;

            N12 = opts->initialization_const;

            N12 = gost_encrypt_step(N12,*opts->key,*opts->s_box);

            N3 = N12 & 0xffffffff;
            N4 = N12 >> 32;

            for (int i = 0; i < block_count; ++i) {

               N4 = (N4 + GOST_C1)%UINT_MAX;
               N3 = (N3 + GOST_C2);

               N12 = ((uint64_t)(((uint64_t)N4 << 32) | (uint64_t)N3));

               Gc = gost_encrypt_step(N12,*opts->key,*opts->s_box);

               blocks[i] ^= Gc;
            }

         }
         break;

      case GOSTM_CF:

         {
            uint64_t CM5, N12, Gc;
            uint32_t N3, N4;

            N12 = opts->initialization_const;

            N12 = gost_encrypt_step(N12,*opts->key,*opts->s_box);

            Gc = blocks[0];
            blocks[0] ^= N12;

            for (int i = 1; i < block_count; ++i) {
               N12 = gost_encrypt_step(Gc,*opts->key,*opts->s_box);

               Gc = blocks[i];
               blocks[i] ^= N12;
            }

         }

         break;

      default:
         errno = ENOTSUP;
         return -1;
         break;
   }

   return 0;
}

int gost_mac(uint32_t * mac, uint64_t * blocks, size_t block_count, struct gost_opt * opts) {

   if (opts->s_box == NULL) 
      opts->s_box = &gost_default_s_box;

   /* initialization */
   uint32_t N1, N2, CM1, CM2, R;
   uint64_t N12;
   N1 = blocks[0] & 0xffffffff;
   N2 = blocks[0] >> 32;

   const gost_key * X = opts->key;
   const gost_s_box * K = opts->s_box;

   uint32_t W[32] = { X[0][0], X[0][1], X[0][2], X[0][3], X[0][4], X[0][5], X[0][6], X[0][7], 
                      X[0][0], X[0][1], X[0][2], X[0][3], X[0][4], X[0][5], X[0][6], X[0][7] };


   for (int i = 1; i < block_count; ++i) {

      /* encryption rounds 1 - 16 */
      for (int i = 0; i < 16; ++i) {

         CM1 = N1 + W[i];

         R = (K[0][(CM1&0x0000000f)>> 0]&0x0000000f) | (K[0][(CM1&0x000000f0)>> 4]&0x000000f0) |
             (K[0][(CM1&0x00000f00)>> 8]&0x00000f00) | (K[0][(CM1&0x0000f000)>>12]&0x0000f000) |
             (K[0][(CM1&0x000f0000)>>16]&0x000f0000) | (K[0][(CM1&0x00f00000)>>20]&0x00f00000) |
             (K[0][(CM1&0x0f000000)>>24]&0x0f000000) | (K[0][(CM1&0xf0000000)>>28]&0xf0000000);

         R = ((R << 11) | (R >> 21));

         CM2 = R ^ N2;

         N2 = N1;
         N1 = CM2;
      }

      N12 = ((uint64_t)(((uint64_t)N2 << 32) | (uint64_t)N1));

      N12 ^= blocks[i];

      N1 = N12 &0xffffffff;
      N2 = N12 >> 32;

   }

   /* set the mac from the last result */
   *mac = N1;

   return 0;
}

#if __RDRND__

int gost_keygen(gost_key * key) {
   for (int i = 0; i < 8; ++i) {

      for (int attempts = 0; attempts < 16; ++attempts) {

         if ( __builtin_ia32_rdrand32_step((*key)+i) )
            break;

      }
   }

   return 0;
}

#else
#warning [No RDRAND Support] (Avoid use of gost_keygen)

int gost_keygen(gost_key * key) {

   srandom(time(NULL)*clock());

   for (int i = 0; i < 8; ++i) {

      key[0][i] = random();

   }

   return 0;
}

#endif

int gost_keystr(char * buf, gost_key * key) {

   char time_str[26];
   time_t time_now;

   if (((time_t)-1) == time(&time_now))
      return -1;

   if (ctime_r(&time_now,time_str) == NULL)
      return -1;

   char header[256];
   char footer[128];

   if (snprintf(header,256,"GOST 28147-89 KEY GENERATED ON %s%s\n",time_str,GOST_KEYHEADER) < 0)
      return -1;
   if (snprintf(footer,128,"\n%s\n",GOST_KEYFOOTER) < 0)
      return -1;

   char key_str[256];

   int len = base64_to(key_str,(uint8_t *)*key,8*sizeof(uint32_t));

   strcpy(buf,header);
   strcat(buf,key_str);
   strcat(buf,footer);

   return 0;
}

int gost_storekey(char * path, gost_key * key) {

   int fd = open(path,O_CREAT | O_WRONLY, 444);
   if (fd == -1)
      return -1;
   
   char buf[512];

   gost_keystr(buf,key);

   size_t written = strlen(buf);

   written -= write(fd,buf,written);
   if (written != 0)
      goto failure;

   /* use fsync and check man:close! */
   if (fsync(fd) == -1) 
      goto failure;

   if (close(fd) == -1) {
      remove(path);
      return -1;
   }

   return 0;

failure:
   {
      close(fd);
      remove(path);
      return -1;
   }
}

int gost_loadkey(char * path, gost_key * key) {

   int fd = open(path, O_RDONLY);

   char buf[1025];
   bzero(&buf,1025);

   ssize_t res;
   size_t read_t = 0;
   char * loc;

   struct stat fstatus;
   bzero(&fstatus,sizeof(fstatus));

   /* init the buffer */
   res = read(fd,buf,1024);
   if (res == -1)
      goto failure;

   read_t += res;

   fstat(fd,&fstatus);

   /* we will read in 512 byte sequences at a time, and search over
    * 1024 bit sequences to ensure that we capture the entire input
    * and won't accidentally fragment our data                    */

   do {

      if ( (loc = strstr(buf,GOST_KEYHEADER)) ) {
         int offset = (int)(loc - buf);

         /* go to the start of the key header */
         if (lseek(fd,offset,SEEK_SET) == ((off_t)-1)) {
            fprintf(stderr,"failed on lseek\n");
            goto failure;
         }

         res = read(fd,buf,256);

         if (res == -1) {
            fprintf(stderr,"failed on res\n");
            goto failure;
         }

         buf[256] = '\0';

         loc = strchr(buf,'\n');

         if (loc++ == NULL) {
            fprintf(stderr,"failed on loc++\n");
            goto failure;
         }

         char * loc2 = strchr(loc,'\n');

         if (loc2 == NULL) {
            fprintf(stderr,"failed on loc2\n");
            goto failure;
         }

         base64_from((uint8_t *)*key,loc,(loc2 - loc));

         close(fd);

         return 0;
      }

      memcpy(buf,buf+512,512);

      res = read(fd,buf+512,512);

      if (res == -1)
         goto failure;

      read_t += res;

   } while (read_t < fstatus.st_size);

   printf("string not found\n");

failure:
   {
      bzero(*key,sizeof(gost_key));
      close(fd);
      return -1;
   }
}
