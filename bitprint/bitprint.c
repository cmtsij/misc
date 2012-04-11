#include <stdio.h>
#include <stdlib.h>








#define bitprint(val)	do{\
							int i=0;	\
							for( i=(sizeof(val)<<3)-1;i>=0;i-- ){	\
								printf("%u%s",!!(val & (1<<(i))), ((i)%4==0&&i!=0)?(" "):("") );\
							}\
						}while(0)


int main(int argc,char *argv[])
{
	if(argc != 2){
		return -1;
	}
		
	unsigned char value=strtoul(argv[1],NULL,16);
	
	bitprint(value);
	
	return 0;
}
