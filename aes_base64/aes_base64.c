#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include "aes_base64.h"


// 69E7E8DC98995D12D643C1559C3FAD0D
unsigned char key[AES_KEY_LEN] = {0x69, 0xE7, 0xE8, 0xDC, 0x98, 0x99, 0x5D,  0x12, 0xD6, 0x43, 0xC1, 0x55, 0x9C, 0x3F, 0xAD, 0x0D};
unsigned char iv[AES_IV_LEN]   = {0};


int reader_dec(char* infile, char* outfile, int method)
{
	int ret = 0;

	FILE* fin = fopen(infile,"r");
	if(!fin)
		return -1;

	FILE* fout = fopen(outfile,"w");
	if(!fout)
		return -1;

	//get file size
	int fsize = 0;
	fseek( fin, 0, SEEK_END );
	fsize = ftell( fin );
	rewind( fin );
	
	//read in buffer
	unsigned char* buff = malloc(fsize);
	if(!buff)
		return -1;
	fread( buff, fsize, 1, fin );
	fclose(fin);

	
	unsigned char*	in = buff;
	int 		in_len = fsize;
	unsigned char*	out = NULL;
	int 		out_len = 0;
	
	//decode by base64
	if( method&METHOD_BASE64 ) {
		out_len = BASE64_DEC( in, in_len, &out);
		if( out_len >0 ) {
			free( in );
			in = out;
			in_len = out_len;
		}else {
			ret = -1;
		}
	}


	//decode by aes
	if( method&METHOD_AES ) {
		out_len = AES_DECRYPT_CBC( in, in_len, key, iv , &out);
		if( out_len >0 ) {
			free( in );
			in = out;
			in_len = out_len;
		}else {
			ret = -1;
		}
	}

	//write to file.
	if( (ret == 0) && (in!=NULL) && (in_len>0) ) { 
		fwrite(in , in_len, 1, fout );
		fclose(fout);
	}

	free( in );
	return ret;

}

int writer_enc(char* infile, char* outfile, int method)
{
	int ret = 0;

	FILE* fin = fopen(infile,"r");
	if(!fin)
		return -1;

	FILE* fout = fopen(outfile,"w");
	if(!fout)
		return -1;

	//get file size
	int fsize = 0;
	fseek( fin, 0, SEEK_END );
	fsize = ftell( fin );
	rewind( fin );
	
	//read in buffer
	unsigned char* buff = malloc(fsize);
	if(!buff)
		return -1;
	fread( buff, fsize, 1, fin );
	fclose(fin);


	unsigned char*	in = buff;
	int 		in_len = fsize;
	unsigned char*	out = NULL;
	int 		out_len = 0;
	
	//encode by aes
	if( method&METHOD_AES ) {
		out_len = AES_ENCRYPT_CBC( in, in_len, key, iv , &out);
		if( out_len >0 ) {
			free( in );
			in = out;
			in_len = out_len;
		}else {
			ret = -1;
		}
	}


	//encode by base64
	if( method&METHOD_BASE64 ) {
		out_len = BASE64_ENC( in, in_len, &out);
		if( out_len >0 ) {
			free( in );
			in = out;
			in_len = out_len;
		}else {
			ret = -1;
		}
	}

	//write to file.
	if( (ret == 0) && (in!=NULL) && (in_len>0) ) { 
		fwrite(in , in_len, 1, fout );
		fclose(fout);
	}

	free( in );
	return ret;

}






//int certtool(int argc,char *argv[])
int main(int argc,char *argv[])
{
	int opt;
	extern char *optarg;
	extern int optind, opterr, optopt;

	if(argc != 4){
		printf("Usage:\n"
				"\tencode => %s -e [input file] [output file]\n"
				"\tdecode => %s -d [input file] [output file]\n"
				,argv[0],argv[0]);
		return -1;
	}	

	int ret=0;

	if(strcmp(argv[1],"-e")==0){
		printf("Encode...");
		ret=writer_enc(argv[2],argv[3], METHOD_AES|METHOD_BASE64 );
	}else if(strcmp(argv[1],"-d")==0){
		printf("Decode...");

		ret=reader_dec(argv[2],argv[3], METHOD_AES|METHOD_BASE64 );
			
	}else{
		printf("Invalid option.\n");
		ret=-1;
	}		

	printf("%s\n",(!ret)?("ok"):("fail"));

	return 0;








/* 
	unsigned char in[]="1234567890\n";
	int in_len=strlen(in);


	unsigned char key[AES_KEY_LEN]={0};
	unsigned char iv[AES_KEY_LEN]={0};

	//sample function for encryption
	unsigned char *cipher=NULL;
	int cipher_len=AES_ENCRYPT_CBC(in, in_len, key, iv, &cipher );
	if(cipher_len > 0 ) {
		//sample function for decryption
		unsigned char *plain=NULL;
		int plain_len=AES_DECRYPT_CBC(cipher, cipher_len, key, iv, &plain );

		printf("%d\n%s",plain_len,plain);

		free(plain);
	}	
	free(cipher);

	return 0;
*/ 
}


