#include <stdio.h>
#include <stdlib.h>

#define	MB	(1024*1024)

void usage(char *name)
{
	printf("Generate the binary that the content is the address on where should be burned\n");
	printf("Usage:   %s address len\n",name );
	printf("example: %s 0x20000000 0x600000\n",name );
	return;
}

int main(int argc, char *argv[])
{
	if(argc != 3){
		usage(argv[0]);
		return -1;
	}
	unsigned int base=strtoul(argv[1],NULL,16);
	unsigned int end=base+strtoul(argv[2],NULL,16);
	
	char fname[FILENAME_MAX]={0};
	sprintf(fname,"address_0x%08X-0x%08X.bin",base,end);
	
	FILE *fp=NULL;
	fp=fopen(fname,"w");
	if(fp == NULL){
		return -1;
	}
		
	unsigned int i=base;	
	for(i; i<end ;i+=4 )
	{
		int j=htonl(i);
		fwrite(&j,4,1,fp);
	}

	fclose(fp);

	printf("File generated: %s\n",fname);

	return 0;






}

