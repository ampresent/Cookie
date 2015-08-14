#include "stdio.h"
#include "stdlib.h"

int main(){
	printf("%u",rand() ^ 0xdeadbeef);
	return 0;
}
