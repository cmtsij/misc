#ifndef AES_H
#define AES_H

#define AES_CBC_BITS	(128)
#define AES_KEY_LEN 	(AES_CBC_BITS/8)
#define AES_IV_LEN 	(AES_BLOCK_SIZE)


extern int AES_ENCRYPT_CBC(unsigned char *in, int in_len, unsigned char *key, unsigned char *iv,unsigned char **out );
extern int AES_DECRYPT_CBC(unsigned char *in, int in_len, unsigned char *key, unsigned char *iv,unsigned char **out );

#endif	//AES_H
