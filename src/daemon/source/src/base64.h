
#ifndef __BASE64_CONVERSIONS

#define __BASE64_CONVERSIONS
#include <stddef.h>
#include <stdint.h>

/* conversions to and from base64
 * based on the specifications in
 * RFC 4648                      */

/* the base64 alphabet */
extern const char base64_alphabet[65];
extern const char base64url_alphabet[65];

/* convert nmemb bytes in src to 
 * base64, storing the result in dest 
 * Return the number of bytes written
 * to dest                         */
int base64_to(char * dest, uint8_t * src, size_t nmemb);

/* Convert nmemb bytes in src to the associated
 * binary data from base64 and place the result
 * in dest
 * Returns the number of bytes written        */
int base64_from(uint8_t * dest, char * src, size_t nmemb);

/* same as base64_*, but provide an alphabet of 65 characters
 * (64 + 1 padding) to be used as the alphabet for conversion */
/* see base64_to */
int base64_to_alphabet(char * dest, uint8_t * src, size_t nmemb, const char * alphabet);
/* see base64_from */
int base64_from_alphabet(uint8_t * dest, char * src, size_t nmemb, const char * alphabet);

#endif
