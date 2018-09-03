#include "parser.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define COUNT 4

// Virtual Machine Bytecodes
#define IAND	0x7e
#define IOR		0x80
#define IXOR	0x82
#define INEG	0x74

#define IADD	0x60
#define ISUB	0x64
#define IMUL	0x68
#define IDIV	0x6c
#define IREM	0x70

#define DUP		0x59
#define BIPUSH	0x10

#define ISTORE	0x36
#define ILOAD	0x15

parser_t* parser_init(const char* filepath) {
	parser_t* self = malloc(sizeof(parser_t));
	self->bytecode = malloc(sizeof(*self->bytecode) * COUNT);
	memset(self->bytecode, 0, sizeof(*self->bytecode) * COUNT);	
	
	if (filepath == NULL) {
		self->file = stdin;
	} else {
		self->file = fopen(filepath, "rb");
	}

	return self;
}

void parser_destroy(parser_t* self) {
	if (self->file != stdin) {
		fclose(self->file);
	}
	free(line);
	free(self);
}

size_t parser_read(parser_t* self) {
	return fread((char*)self->bytecode, sizeof(*self->bytecode), COUNT, self->file);
}

char* parser_get_bytecode(parser_t* self) {
	return self->bytecode;
}

size_t parser_length(parser_t* self) {
	return strlen(self->bytecode);
}

int parser_eof(parser_t* self) {
	return feof(self->file);
}

// with testing purposes only
// compile with: gcc -Wall -Werror -std=c99 -pedantic -ggdb -O0 parser.c vmachine.c vars.c stack.c node.c -o testparser
// run with: ./testparser <num-vars> <filename>
