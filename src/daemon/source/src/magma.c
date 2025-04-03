
#include "gost.h"
#include "util.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* use of the gost cipher in the command line */

int main(int argc, char ** argv) {

   char * help_message = 
      "magma\n"
      "Implimentation of the GOST 28147-89 block cipher algorithm\n"
      "\n"
      "\tmagma -[edvVhmg] [-M mode] [-k key] [-f file] [-o file] [-n nonce]\n"
      "\n"
      "options:\n"
      "\t-e         => encrypt mode (default)\n"
      "\t-d         => decrypt mode\n"
      "\t-k [file]  => load key from the given file\n"
      "\t-v         => version information\n"
      "\t-V         => verbose output\n"
      "\t-h         => help (this message)\n"
      "\t-n [nonce] => set nonce to given value\n"
      "\t-m         => generate mac\n"
      "\t-g         => generate key\n"
      "\t-f [file]  => target file to read from\n"
      "\t-o [file]  => target file to write to\n"
      "\t-M [mode]  => cipher mode. One of [ ECB, CE, CF ]\n"
      "\t-K         => print path of key in use\n"
      "\t-P         => preserve trailing '\\0' chars in final block\n"
      "\t-R         => check if keygen was compiled using the rdrand intrinsic\n"
      "note:\n"
      "\ttarget file will default to stdin for input and\n"
      "\tstdout for output.\n"
      "\n"
      "\tdefault cipher mode is ECB if no nonce is specified\n"
      "\tand CF if a nonce is specified\n"
      "\n"
      "\tthe following paths will be searched for a key if\n"
      "\tno key path is specified. Search order is as shown:\n"
      "\t\t[ gost.key, ~/.magma/gost.key, /etc/gost.key ]\n";

   char * version_message = 
      "magma v1.0.0 written by qeftser\n";

   enum gost_mode mode = GOSTM_ECB;
   gost_key key;
   struct gost_opt options;
   bzero(&options,sizeof(struct gost_opt));
   options.key = &key;
   options.s_box = &gost_default_s_box;

   int encrypt = 1;
   int keygen = 0;
   int verbose = 0;
   int mac = 0;
   int rdrand_check = 0;
   int preserve_zeros = 0;
   char * key_path = NULL;
   char * set_mode = NULL;
   int print_keypath = 0;
   char * target_path = "stdin";
   FILE * target = stdin;
   char * dest_path = "stdout";
   FILE * dest = stdout;

   int c;

   while ( (c = getopt(argc,argv,"edk:vVhn:mgf:i:o:M:KPR")) != -1) {

      switch (c) {

         case 'e':
            encrypt = 1;
            break;

         case 'd':
            encrypt = 0;
            break;

         case 'k':
            key_path = optarg;
            break;

         case 'v':
            fprintf(stdout,"%s",version_message);
            return 0;
            break;

         case 'V':
            verbose = 1;
            break;

         case 'h':
            fprintf(stdout,"%s",help_message);
            return 0;
            break;

         case 'n':
            options.initialization_const = strtol(optarg,NULL,0);
            options.mode = GOSTM_CF;
            break;

         case 'm':
            mac = 1;
            break;

         case 'g':
            keygen = 1;
            break;

         case 'i':
         case 'f':
            target = fopen(optarg,"r");
            target_path = optarg;
            if (target == NULL) {
               fprintf(stderr,"%s not reachable\n",optarg);
               exit(errno);
            }
            break;

         case 'o':
            dest = fopen(optarg,"w");
            dest_path = optarg;
            if (dest == NULL) {
               fprintf(stderr,"%s not reachable\n",optarg);
               exit(errno);
            }
            break;

         case 'M':
            set_mode = optarg;
            break;

         case 'K':
            print_keypath = 1;
            break;

         case 'P':
            preserve_zeros = 1;
            break;

         case 'R':
            rdrand_check = 1;
            break;
      }
   }

   if (rdrand_check || verbose) {
      if (__RDRND__)
         fprintf(stdout,"compiled with rdrand\n");
      else
         fprintf(stdout,"compiled without rdrand\n");
   }


   if (keygen) {

      gost_key key;

      if (verbose) fprintf(stderr,"generating key\n");

      gost_keygen(&key);

      if (verbose) fprintf(stderr,"generated key number:\n" 
                                  "%08x%08x%08x%08x%08x%08x%08x%08x\n",
                           key[0],key[1],key[2],key[3],key[4],key[5],key[6],key[7]);

      char buf[512];

      if (gost_keystr(buf,&key)) {
         fprintf(stderr,"key generation error\n");
         return errno;
      }

      fwrite(buf,strlen(buf),1,dest);

      if (verbose) fprintf(stderr,"key written to %s\n",dest_path);

      fclose(dest);
      fclose(target);

      return errno;

   }

   if (key_path == NULL) {

      if (verbose) fprintf(stderr,"no key provided\n");

      key_path = "gost.key";

      if (verbose) fprintf(stderr,"trying key %s\n",key_path);
      if (gost_loadkey(key_path,&key)) {

      key_path = "~/.gost/gost.key";

      if (verbose) fprintf(stderr,"trying key %s\n",key_path);
      if (gost_loadkey(key_path,&key)) {

      key_path = "/etc/gost.key";

      if (verbose) fprintf(stderr,"trying key %s\n",key_path);
      if (gost_loadkey(key_path,&key)) {

      key_path = NULL;

      }
      }
      }

      if (key_path == NULL) {
         fprintf(stderr,"no key provided\n");
         return 1;
      }

   }
   else {

      if (verbose) fprintf(stderr,"loading key from %s\n",key_path);
      if (gost_loadkey(key_path,&key)) {

         fprintf(stderr,"no key provided\n");
         return 1;

      }

   }

   if (verbose) fprintf(stderr,"provided key number:\n" 
                               "%08x%08x%08x%08x%08x%08x%08x%08x\n",
                        key[0],key[1],key[2],key[3],key[4],key[5],key[6],key[7]);
   if (verbose) fprintf(stderr,"provided nonce: %016lx\n",options.initialization_const);

   if (set_mode) {
      if (!strcmp(set_mode,"ECB"))
         options.mode = GOSTM_ECB;
      else if (!strcmp(set_mode,"CE"))
         options.mode = GOSTM_CE;
      else if (!strcmp(set_mode,"CF"))
         options.mode = GOSTM_CF;
      else if (verbose)
         fprintf(stderr,"invalid mode requested\n");
   }

   if (verbose) {
      switch (options.mode) {
         case GOSTM_ECB:
            fprintf(stderr,"mode is ECB\n");
            break;
         case GOSTM_CE:
            fprintf(stderr,"mode is CE\n");
            break;
         case GOSTM_CF:
            fprintf(stderr,"mode is CF\n");
            break;
      }
   }

   if (print_keypath || verbose) {
      fprintf(stdout,"keypath: %s\n",key_path);
   }

   fseek(target,0L,SEEK_SET);
   char * data = fload(target);
   fseek(target,0L,SEEK_END);
   int data_len = ftell(target);

   if (mac) {

      if (data_len % 8 != 0) {
         data = realloc(data, data_len + (8 - data_len%8));
         if (data == NULL) {
            fprintf(stderr,"internal error\n");
            exit(errno);
         }
         memset(data+data_len,0,(8 - data_len%8));
         data_len += (8 - data_len%8);
      }

      if (verbose) fprintf(stderr,"generating mac for %s\n",target_path);

      uint32_t mac_num;

      if (gost_mac(&mac_num,(uint64_t *)data,data_len/sizeof(uint64_t),&options)) {
         fprintf(stderr,"mac failed\n");
         free(data);
         exit(errno);
      }

      fprintf(stdout,"GOST 28147-89 MAC: %08x\n",mac_num);

      goto end;

   }

   if (encrypt) {

      if (data_len % 8 != 0) {
         data = realloc(data, data_len + (8 - data_len%8));
         if (data == NULL) {
            fprintf(stderr,"internal error\n");
            exit(errno);
         }
         memset(data+data_len,0,(8 - data_len%8));
         data_len += (8 - data_len%8);
      }

      if (verbose) fprintf(stderr,"performing encryption on %s\n",target_path);

      if (gost_encrypt((uint64_t *)data,data_len/sizeof(uint64_t),&options)) {
         fprintf(stderr,"internal error\n");
         exit(errno);
      }

      fwrite(data,data_len,1,dest);

      if (verbose) fprintf(stderr,"encryption written to %s\n",dest_path);

   }
   else {

      if (verbose) fprintf(stderr,"performing decryption on %s\n",target_path);

      if (gost_decrypt((uint64_t *)data,data_len/sizeof(uint64_t),&options)) {
         fprintf(stderr,"internal error\n");
         exit(errno);
      }

      if (!preserve_zeros) {
         while (data_len > 1 && !data[data_len-1])
            --data_len;
      }

      fwrite(data,data_len,1,dest);

      if (verbose) fprintf(stderr,"decryption written to %s\n",dest_path);

   }


end:
   free(data);
   fclose(dest);
   fclose(target);

   return 0;
}
