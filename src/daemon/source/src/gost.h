
#ifndef __GOST_CIPHER

#define __GOST_CIPHER
#include <stdint.h>
#include <stddef.h>

/* a full and hopefully resuable implimentation of 
 * the GOST 28147-89 encryption algorithm          */

typedef uint32_t gost_key[8];

typedef uint32_t gost_s_box[16];

/* modes to run GOST in:
 *    Electronic code book
 *    Counter encryption
 *    Cypher feedback (most secure)
 */
enum gost_mode { GOSTM_ECB, GOSTM_CE, GOSTM_CF };

extern const gost_s_box gost_default_s_box;

#define GOST_C1 0b00000001000000010000000100000100
#define GOST_C2 0b00000001000000010000000100000001

#define GOST_KEYHEADER "<<< GOST 28147-89 KEY BEGIN >>>"
#define GOST_KEYFOOTER "<<< GOST 28147-89 KEY END >>>"

/* options for the gost cipher */
struct gost_opt {
   /* the mode to encrpyt/decrypt data in */
   enum gost_mode mode;
   /* the key to use for encrpytion/decryption */
   gost_key const * key;
   /* the s-box to use 
    * The default s-box will be provided if this
    * value is set to NULL */
   gost_s_box const * s_box;
   /* the initialization constant to use if the 
    * mode expects one */
   uint64_t initialization_const;
};

/* Encrpyt the data passed in blocks using the GOST cipher described in RFC 5830
 * and the ГОСТ Р 34.12─2015 specification.
 */
int gost_encrypt(uint64_t * blocks, size_t block_count, struct gost_opt * opts);

/* Decrpyt the data passed in blocks using the GOST cipher described in RFC 5830
 * and the ГОСТ Р 34.12─2015 specification.
 */
int gost_decrypt(uint64_t * blocks, size_t block_count, struct gost_opt * opts);

/* Construct a message authentification code using the GOST cipher 
 * return -1 on error and 0 on success.
 * Operation defined in RFC 5830 section 8
 * Note that the specification defines a variable mac, here the full 32 bit 
 * mac is returned. This is improvement by exclusion xD
 */
int gost_mac(uint32_t * mac, uint64_t * blocks, size_t block_count, struct gost_opt * opts);

/* generates a gost key, filling the passed value 
 * Returns -1 if an error occured, and 0 on success 
 *
 * Note: This function will use the intel/AMD assembly
 *       instruction RDRAND if it is avaliable on the
 *        given architecture, but will instead use the
 *        linux random, srand, clock, and time calls to
 *        generate the random seed. A compiler warning will
 *        print if RDRAND is not avaliable. Use of gost_keygen
 *        is discouraged in the case that RDRAND is not
 *        avaliable on your system.                          */
int gost_keygen(gost_key * key);

/* create a string with the header, footer and base64 key
 * for use in later functions.                           
 * Return -1 on error and 0 on success                 */
int gost_keystr(char * buf, gost_key * key);

/* Write the key and some other information into the specified
 * file as base64 (RFC 4648) for retrival by the associated 
 * gost_loadkey function. Note that the program seeks for the
 * header, so the key can be included in a larger file if the
 * header line is preserved.
 * Return -1 on error and 0 on success 
 */
int gost_storekey(char * path, gost_key * key);

/* Read the key from the file given by path, collecting the
 * gost key that was presumably placed there by gost_storekey
 * and loading it into key.
 * Return -1 on error and 0 on success.
 * Note: This function will only load 1024 bytes of a file at
 *       a time into memory, so it can safely be called on
 *       large files if there is some need for that.        */
int gost_loadkey(char * path, gost_key * key);

#endif
