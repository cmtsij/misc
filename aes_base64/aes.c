#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "openssl/aes.h"

#include "aes.h"


int AES_ENCRYPT_CBC(unsigned char *in, int in_len, unsigned char *key, unsigned char *iv,unsigned char **out )
{
	//Check Input
	if( (in == NULL) || (in_len <= 0) )
		return -1;

	//KEY and IV	
	AES_KEY ENC_KEY;
	if ( AES_set_encrypt_key(key, AES_CBC_BITS, &ENC_KEY) != 0 ) {
		//set key error
		return -1;
	}
	unsigned char IV[AES_IV_LEN]={0};
	memcpy(IV,iv,AES_IV_LEN);


	//Padding Input buffer
	int pad_len = AES_BLOCK_SIZE-in_len%AES_BLOCK_SIZE;
	unsigned char *IN = (unsigned char *) malloc(in_len + pad_len);
	
	memcpy(IN,in,in_len);
	int pdi=0;
	for( pdi=0 ; pdi < pad_len; pdi++ )
		IN[in_len+pdi]=pad_len%AES_BLOCK_SIZE;


	//malloc Output buffer
	int out_len= in_len+pad_len;
	*out = (unsigned char *) malloc(out_len);

	//ENCRYTP
	AES_cbc_encrypt(IN,*out,out_len,&ENC_KEY,IV,AES_ENCRYPT);

	if(IN)
		free(IN);

	//return cipher length
	return out_len;
}

int AES_DECRYPT_CBC(unsigned char *in, int in_len, unsigned char *key, unsigned char *iv,unsigned char **out )
{
	//Check Input
	if( (in == NULL) || (in_len <= 0) )
		return -1;
	if( (in_len%AES_BLOCK_SIZE) != 0  )
		return -1; 

	//KEY and IV	
	AES_KEY DEC_KEY;
	if ( AES_set_decrypt_key(key, AES_CBC_BITS, &DEC_KEY) != 0 ) {
		//set key error
		return -1;
	}
	unsigned char IV[AES_IV_LEN]={0};
	memcpy(IV,iv,AES_IV_LEN);


	//malloc Output buffer
	int out_len = in_len;
	*out = (unsigned char *) malloc(in_len);


	//DECRYPT
	AES_cbc_encrypt(in,*out,out_len,&DEC_KEY,IV,AES_DECRYPT);


	//fix padding length
	out_len = out_len-( ((*out)[out_len-1]==0) ? (16) : ((*out)[out_len-1]) );

	return out_len;
}




