#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "openssl/sha.h"
#include "openssl/aes.h"
#include "openssl/crypto.h"
#define DBG_P(fmt,args...) \
	        printf("[%20s]\t%6d\t "fmt,__FUNCTION__,__LINE__,##args); 
#define	B64_DEF_LINE_SIZE	72
#define	B64_MIN_LINE_SIZE	4
#define MAC_LEN			17
#define MAX_CUSTOMER_LEN	47
#define AES_KEY_LEN		32
#define MAX_BUF			2048
static const char cb64[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char cd64[]="|$$$}rstuvwxyz{$$$$$$$>?@ABCDEFGHIJKLMNOPQRSTUVW$$$$$$XYZ[\\]^_`abcdefghijklmnopq";

void encodeblock( unsigned char in[3], unsigned char out[4], int len )
{
    out[0] = cb64[ in[0] >> 2 ];
    out[1] = cb64[ ((in[0] & 0x03) << 4) | ((in[1] & 0xf0) >> 4) ];
    out[2] = (unsigned char) (len > 1 ? cb64[ ((in[1] & 0x0f) << 2) | ((in[2] & 0xc0) >> 6) ] : '=');
    out[3] = (unsigned char) (len > 2 ? cb64[ in[2] & 0x3f ] : '=');
}
void decodeblock( unsigned char in[4], unsigned char out[3] )
{   
    out[ 0 ] = (unsigned char ) (in[0] << 2 | in[1] >> 4);
    out[ 1 ] = (unsigned char ) (in[1] << 4 | in[2] >> 2);
    out[ 2 ] = (unsigned char ) (((in[2] << 6) & 0xc0) | in[3]);
}
int b64_enc( char *input, char *output, int alen)
{
	if(input==NULL||output==NULL||alen<0){
		return -1;
	}
	unsigned char in[3], out[4];
	int i,j,k, len, blocksout = 0;
	j=0;
	k=0;
	while(j<alen) {
		len = 0;
		for( i = 0; i < 3; i++ ) {
			in[i] = input[j];
			if(j<alen) {
				len++;
			}
			else {
				in[i] = 0;
			}
			j++;
		}
		if( len ) {
			encodeblock( in, out, len );
			for( i = 0; i < 4; i++ ) {
				//putc( out[i], outfile );
				output[k]=out[i];
				//printf("%c",out[i]);
				k++;
			}
			blocksout++;
		}
		if(j<alen) {
			if( blocksout >= (B64_DEF_LINE_SIZE/4) || j>=alen) {
				//printf("\r\n");
				blocksout = 0;
			}
		}
	}
	return k;
}
int b64_dec( char *input, char *output, int alen)
{
	if(input==NULL||output==NULL||alen<0){
		return -1;
	}
	unsigned char in[4], out[3], v;
	int i, len;
	int j=0;
	int k=0;
	int l=0;
	while( j<alen ) {
		for( len = 0, i = 0; i < 4 && j<alen; i++ ) {
			v = 0;
			while( j<alen && v == 0 ) {
				if(input[j]=='='){
					l++;
				}
				v = (unsigned char) input[j];
				v = (unsigned char) ((v < 43 || v > 122) ? 0 : cd64[ v - 43 ]);
				if( v ) {
					v = (unsigned char) ((v == '$') ? 0 : v - 61);
				}
				j++;
			}
			if( j<(alen-l+1)) {
				len++;
				if( v ) {
					in[ i ] = (unsigned char) (v - 1);
				}
			}else {
				in[i] = 0;
			}
		}
		if( len ) {
			decodeblock( in, out );
			for( i = 0; i < len - 1; i++ ) {
				output[k]=out[i];
				k++;
			}
		}
	}
	return k;
}

int BASE64_ENC(unsigned char *in, int in_len, unsigned char **out )
{
	//Check Input
	if( (in == NULL) || (in_len <= 0) )
		return -1;

	//Malloc output buffer
	int out_len = ( in_len/3 + ((in_len%3)?(1):(0)) ) * 4 ;
	*out = malloc( out_len );

	//base64 encode
	b64_enc(in, *out, in_len);

	return	out_len;

}


int BASE64_DEC(unsigned char *in, int in_len, unsigned char **out )
{
	//Check Input
	if( (in == NULL) || (in_len <= 0) )
		return -1;

	//Malloc output buffer
	*out = malloc( in_len );

	//base64 encode
	return b64_dec(in, *out, in_len);
}


