#include <stdio.h>
#define OS_IO_IMPLEMENTATION
#include "ds.h"

enum token_kind {
  IDENT,
  LABEL,
  INT,
  INPUT,
  OUTPUT,
  GOTO,
  IF,
  THEN,
  EQUAL,
  PLUS,
  LESS_THAN,
  INVALID
};

const char *show_token(enum token_kind kind) {
  switch (kind) {
  case IDENT:
    return "ident";
   case LABEL:
    return "label";
   case INT:
    return "int";
   case INPUT:
    return "input";
   case OUTPUT:
    return "output";
   case GOTO:
    return "goto";
   case IF:
    return "if";
   case THEN:
    return "then";
   case EQUAL:
    return "equal";
   case PLUS:
    return "plus";
   case LESS_THAN:
    return "less_than";
   case INVALID:
    return "invalid";
   }
}

struct lexer { // lexer data structure
  char *buffer; //buffer that we are going to read
  unsigned int buffer_len; // buffer length
  unsigned int pos; // position
  unsigned int read_pos; // read position
  char ch; // current character
};

static char lexer_peek_char(struct lexer *l) { // advances the buffer
  if (l->read_pos >= l->buffer_len) {
    return EOF;
  }

  return l->buffer[l->read_pos];
}

int main() {
  char *buffer = NULL;
  ds_io_read_file(NULL, &buffer);

  printf("%s\n", buffer);
}
