#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#define MAXBUFSIZE 1024

char buf[MAXBUFSIZE];

int main(int argc, char* argv[]){
	putenv("\xde\xad\xbe\xef=\xca\xfe\xba\xbe");
	char* p = strrchr(argv[0], '/');

	strcat(buf, "/usr/bin/zsh ");
	strncpy(buf+strlen(buf), argv[0], p-argv[0]);
	strcat(buf+strlen(buf), "/work.sh");
	//sprintf(buf, "/usr/bin/zsh %s/work.sh", p);
	system(buf);
	return 0;
}
