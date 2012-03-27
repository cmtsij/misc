#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <execinfo.h>

#define DDD		do{fprintf(stderr,"%s():%d\n",__FUNCTION__,__LINE__);}while(0)

void __attribute__((__no_instrument_function__))
__cyg_profile_func_enter(void *this_func, void *call_site)
{
	void *trace[1000];
	char **messages = (char **)NULL;
	int i, trace_size = 0;

	trace_size = backtrace(trace, 1000);
	messages = backtrace_symbols(trace, trace_size);

#if DUMP_ALL
	for(i=0;i<trace_size;i++){
		printf("[%d:%s]\n",i,messages[]);
	}
	printf("\n");
#else
	printf("enter func=%s\n", messages[1]);
#endif

	free(messages);
}

void __attribute__((__no_instrument_function__))
__cyg_profile_func_exit(void *this_func, void *call_site)
{
	void *trace[1000];
	char **messages = (char **)NULL;
	int i, trace_size = 0;

	trace_size = backtrace(trace, 1000);
	messages = backtrace_symbols(trace, trace_size);
	printf("exit func=%s\n", messages[1]);
	free(messages);
}

int a()
{
	DDD;
	return 0;
}

int b()
{
	a();
	DDD;
	return 0;
	
}

int ccc()
{
	b();
	DDD;
	return 0;
	
}

int main(int argc,char *argv[])
{
	DDD;
	ccc();
	return 0;
}
