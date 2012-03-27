#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int main()
{

	// use freopen to hijack stdout
	FILE *fp=freopen("/dev/null","w+",stdout);

	// it should output to stdout....but to /dev/null actually.
	system("ps;ls;");

	fclose(fp);

	return 0;
}




