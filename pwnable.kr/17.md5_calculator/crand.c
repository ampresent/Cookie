#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "Python.h"

unsigned int hash(unsigned int t){
	int i;
	unsigned int s;
	srand(time(0)-t);
	s = 0;
	rand();
	for (i=0;i<7;i++){
		unsigned int ri = rand();
		fprintf(stderr, "%x ", ri);
		switch(i){
			case 2:
			case 5:
				s -= ri;
				break;
			default:
				s += ri;
		}
	}
	fprintf(stderr, "\n");
	return s;
}

PyObject* wrap_hash(PyObject* self, PyObject* args){
	int t, result;
	if (!PyArg_ParseTuple(args, "I", &t))
		return NULL;
	result = hash(t);
	return Py_BuildValue("I", result);
}

static PyMethodDef exampleMethods[] = {
	{"hash", wrap_hash, METH_VARARGS, ""},
	{NULL, NULL}
};

void initcrand(){
	PyObject* m;
	m = Py_InitModule("crand", exampleMethods);
}


