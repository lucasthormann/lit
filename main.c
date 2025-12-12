#include <stdio.h>
#define DS_IMPLEMENTATION
#include "ds.h"
#include <string.h>
#include <ctype.h>

struct token {
  enum token_kind kind;
  char *value;
}

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
  INVALID,
  END
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
   case END:
    return "end";
   }
}

struct lexer { // lexer data structure
  char *buffer; //buffer that we are going to read
  unsigned int buffer_len; // buffer length
  unsigned int pos; // position
  unsigned int read_pos; // read position
  char ch; // current character
};

static char lexer_peek_char(struct lexer *l) { // peeks at top element in 
  if (l->read_pos >= l->buffer_len) {           // the buffer
    return EOF;
  }

  return l->buffer[l->read_pos];
}

static char lexer_read_char(struct lexer *l) { // advances the buffer
  l->ch = lexer_peek_char(l);
  l->pos = l->read_pos;
  l-> read_pos += 1;

  return l->ch;
}

static void skip_whitespaces(struct lexer *l) { // skips white spaces in input
  while (isspace(l->ch)) {
    lexer_read_char(l);
  }
}

static void lexer_init(struct lexer *l, char *buffer, unsigned int buffer_len) { // initiaize lexer (iterator) with a buffer
  l->buffer = buffer;
  l->buffer_len = buffer_len;
  l->pos = 0;
  l->read_pos = 0;
  l->ch = 0;

  lexer_read_char(l);
}

static struct token lexer_next_token(struct lexer *l) { 
  skip_whitespaces(l);

  if (l->ch = EOF){
    lexer_read_char(l);
    return (struct token){.kind = END, .value = NULL};
  }
  else if (l->ch == '=') {
    lexer_read_char(l);
    return (struct token){.kind = EQUAL, .value = NULL};
  } 
  else if (l->ch == '+') {
    lexer_read_char(l);
    return (struct token){.kind = PLUS, .value = NULL};
  }
  else if (l->ch == '<') {
    lexer_read_char(l);
    return (struct token){.kind = LESS_THAN, .value = NULL};
  }
  else if (l->ch == ':') {
    // read until end
  }
  else if (isdigit(l->ch)) {
    // read until end
  }
  else if (isalnum(l->ch) || l->ch = '_') {
    // starts with letter or _
  }
  else {
    ds_string_slice slice = {.str = l->buffer + l->pos, .len = 1};
    char *value = NULL;
    ds_string_slice_to_owned(&slice, &value);
    lexer_read_char(l);
    return (struct token){.kind = INVALID, .value = value};
  }
}

int main() {
  char *buffer = NULL;
  ds_io_read_file(NULL, &buffer);

  printf("%s\n", buffer);
}
