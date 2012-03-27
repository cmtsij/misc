/*********************************************
 * 
 * system_gets like fgets.
 * It run some command and get the first line result.
 * 
 * ******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * system_gets_value_buff(char *cmd,char *buf,int bufsize)
{
	FILE *fp=NULL;
	
	//popen to get system() output
	if( (fp=popen(cmd,"r")) == NULL ){
		return NULL;
	}
	
	//get one line
	if (fgets(buf,bufsize-1,fp) == NULL ){
		pclose(fp);
		return NULL;
	}

	//replace "\n" to "\0"
	char *c=NULL;
	while( (c=strchr(buf,'\n'))!=NULL ){
		*c='\0';
	}

	pclose(fp);
	return buf;
}

//const local buff to prevent rewrite the return string.
char const *system_gets_value(char *cmd)
{
	static char buff[1024]={0};

	system_gets_value_buff(cmd,buff,sizeof(buff));

	return (char const *) buff;

}

int main(int argc,char *argv[])
{
	if( argc == 2 ){
		char *cmd=argv[1];
		//char buff[1024]={0};
		//printf( "%s\n", system_get_buff(cmd,buff,sizeof(buff)) );
		char const *str= system_gets_value(cmd);
		printf("system output: [%s]\n",str);
	}
	return 0;






}








