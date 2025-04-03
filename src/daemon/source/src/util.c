
#include "util.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int strtrm(char * str) {
   char * start = str;
   if (!str || !(*str))
      return 0;

   char * buf = calloc(sizeof(char), (strlen(str) + sizeof('\0')));
   int buf_pos = -1;

   while (*str != '\0') {

      /* cull whitespace */
      while (isspace(*str))
         ++str;

      /* add the characters to the string */
      while (*str && !isspace(*str)) {

         buf[++buf_pos] = *str;

         ++str;

      }

      /* catch the null byte because it will be there :) */
      if (*str)
         buf[++buf_pos] = ' ';

   }

   if (buf[buf_pos] == ' ')
      buf[buf_pos] = '\0';
   else
      buf[++buf_pos] = '\0';

   buf_pos += 1;

   memcpy(start,buf,buf_pos);
   free(buf);

   return buf_pos;
}

int load(char * path, char ** buf) {

   size_t buf_len = 1024;
   *buf = malloc(buf_len);
   if (*buf == NULL)
      goto failure;

   int fptr = open(path,O_RDONLY);
   if (fptr == -1) 
      goto failure;

   int coll = 0, gettr;
   while ( (gettr = read(fptr,(*buf)+coll,1)) ) {
      if (gettr == -1 && errno != EINTR)
         goto failure;
      else
         coll += gettr;
      if (coll == buf_len) {
         buf_len *= 2;
         *buf = realloc(*buf,buf_len);
         if (*buf == NULL)
            goto failure;
      }
   }

   buf_len = coll;
   *buf = realloc(*buf,buf_len);
   if (*buf == NULL)
      goto failure;

   return buf_len;

failure:
   {
      free(*buf);
      *buf = NULL;
      return -1;
   }
}

char * fload(FILE * fptr) {

   size_t buf_len = 1024;
   char * buf;
   buf = malloc(buf_len);
   if (buf == NULL)
      goto failure;

   int coll = 0, gettr;
   while ( (gettr = fread((buf)+coll,1,1,fptr)) ) {
      if (gettr == 0 && !feof(fptr))
         goto failure;
      else
         coll += gettr;
      if (coll == buf_len) {
         buf_len *= 2;
         buf = realloc(buf,buf_len);
         if (buf == NULL)
            goto failure;
      }
   }

   buf_len = coll;
   buf = realloc(buf,buf_len);
   if (buf == NULL)
      goto failure;

   return buf;

failure:
   {
      free(buf);
      return NULL;
   }
}
