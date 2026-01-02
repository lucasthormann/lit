#include <stdio.h>
#define DS_IMPLEMENTATION
#include "ds.h"
#include <string.h>
#include <ctype.h>

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

struct token {
  enum token_kind kind;
  char *value;
};

const char *show_token_kind(enum token_kind kind) {
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

void print_token(struct token tok) {
  const char *kind = show_token_kind(tok.kind);
  printf("%s", kind);
  if (tok.value != NULL) {
    printf("(%s)", tok.value);
  }
  printf("\n");
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

  if (l->ch == EOF){
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
    lexer_read_char(l); // next in buffer
    ds_string_slice slice = {.str = l->buffer + l->pos, .len = 0};
    while (isalnum(l->ch) || l->ch == '_') {
      slice.len += 1;
      lexer_read_char(l);
    }
    char *value = NULL;
    ds_string_slice_to_owned(&slice, &value);
    return (struct token){.kind = LABEL, .value = value};
  }
  else if (isdigit(l->ch)) {
    // read until end
    ds_string_slice slice = {.str = l->buffer + l->pos, .len = 0};
    while (isdigit(l->ch)) {
      slice.len += 1;
      lexer_read_char(l);
    }
    char *value = NULL;
    ds_string_slice_to_owned(&slice, &value);
    return (struct token){.kind = INT, .value = value};
  }
  else if (isalnum(l->ch) || l->ch == '_') {
    // starts with letter or _
    ds_string_slice slice = {.str = l->buffer + l->pos, .len = 0};
    while (isalnum(l->ch) || l->ch == '_') {
      slice.len += 1;
      lexer_read_char(l);
    }
    char *value = NULL;
    ds_string_slice_to_owned(&slice, &value);
    if (strcmp(value, "input") == 0) {
      return (struct token){.kind = INPUT, .value = NULL};
    } else if (strcmp(value, "output") == 0) {
      return (struct token){.kind = OUTPUT, .value = NULL}; 
    } else if (strcmp(value, "goto") == 0) {
      return (struct token){.kind = GOTO, .value = NULL};
    } else if (strcmp(value, "if") == 0) {
      return (struct token){.kind = IF, .value = NULL};
    } else if (strcmp(value, "then") == 0) {
      return (struct token){.kind = THEN, .value = NULL};
    } else {
      return (struct token){.kind = IDENT, .value = value};
    }
  }
  else {
    ds_string_slice slice = {.str = l->buffer + l->pos, .len = 1};
    char *value = NULL;
    ds_string_slice_to_owned(&slice, &value);
    lexer_read_char(l);
    return (struct token){.kind = INVALID, .value = value};
  }
}

int lexer_tokenize(char *buffer, unsigned int length, ds_dynamic_array *tokens) {
  struct lexer lexer;
  lexer_init(&lexer, (char *)buffer, length);

  struct token tok;
  do {
    tok = lexer_next_token(&lexer);
    if (ds_dynamic_array_append(tokens, &tok) != 0) {
      DS_PANIC("Failed to append token to array");
    }
  } while (tok.kind != END);

  return 0;
}

// ---------------- Parser --------------------------

enum term_kind {
  TERM_INPUT,
  TERM_INT,
  TERM_IDENT
};

struct term_node {
  enum term_kind kind;
  union {
    char *value;
  };
};


enum expr_kind {
  EXPR_TERM,
  EXPR_PLUS,
};

strucyt expr_binary_node {
  struct term_node lhs;
  struct term_node rhs;
};

struct expr_node {
  enum expr_kind kind;
  union {
    struct term_node term;
    struct expr_binary_node add;
  }
};

enum rel_kind {
  REL_LESS_THAN,
};

sturct rel_node {
  enum rel_kind kind;
  union {
    struct term_binary_node less_than;
  };
};

enum instr_kind {
  INSTR_ASSIGN,
  INSTR_IF,
  INSTR_GOTO,
  INSTR_OUTPUT,
  INSTR_LABEL
};

struct assign_node {
  char *ident;
  struct expr_node expr;
};

struct if_node {
  struct rel_node rel;
  struct instr_node *instr;
};

struct goto_node {
  char *label;
};

struct output_node {
  struct term_node term;
};

struct label_node {
  char *label;
};

struct instr_node {
  enum instr_kind kind;
  union {
    struct assign_node assign;
    struct if_node if_;
    sturct goto_node goto_;
    struct output_node output;
    struct label_node label;
  };
};

struct program_node {
  ds_dynamic_array instrs;
};

struct parser {
  ds_dynamic_array tokens;
  unsigned int index;
};

void parser_init(ds_dynamic_array tokens, struct parser *p) {
  p->tokens = tokens;
  p->index = 0;
}

void parser_current(struct parser *p, struct token *token) {
  ds_dynamic_array_get(&p->tokens, p->index, token);
}

void parser_advance(struct parser *p) {
  p->index++;
}

void parse_expr(struct parser *p, struct expr_node *expr) {
  struct token token;
  struct term_node lhs, rhs;

  parser_term(p, &lhs);

  parser_current(p, &token);
  if(token.kind == PLUS) {
    parser_advance(p);
    parse_term(p, &rhs;

    expr->add.lhs = lhs;
    expr->add.rhs = rhs;
  }
  else {
    expr->term = lhs;
  }
}

void parse_assign(struct parser *p, struct instr_node *instr) {
  struct token token;
  parser_current(p, &token);
  instr->assign.ident = token.value;
  parser_advance(p);

  parser_current(p, &token);
  if(token.kind != EQUAL) {
    DS_PANIC("Expected equal found %s", show_token_kind(token.kind));
  }
  parser_advance(p);

  parse_expr(p, &instr->assign.expr);
}

void parse_program(struct parser *p, struct program_node *program) {
  ds_dynamic_array_init(&program->instrs, sizeof(struct instr_node));

  struct token token;
  do {
    struct instr_node instr;

    parser_current(p, &token);
    if(token.kind == IDENT) {
      parse_assign(p, &instr);
    }
    else if(token.kind == IF) {
      parse_if(p, &instr);
    }
    else if(token.kind == GOTO) {
      parse_goto(p, &instr);
    }
    else if(token.kind == OUTPUT) {
      parse_output(p, &instr);
    }
    else if(token.kind == LABEL) {
      parse_label(p, &instr);
    } 
    else {
      DS_PANIC("unexpected toke %s", show_token_kind(token.kind));
    }
    parser_advance(p);

    ds_dynamic_array_append(&program->instrs, &instr);

    parser_current(p, &token);
  } while(token.kind != END);
}

int main() {
  char *buffer = NULL;
  int length = ds_io_read_file(NULL, &buffer);

  ds_dynamic_array tokens;
  ds_dynamic_array_init(&tokens, sizeof(struct token));

  lexer_tokenize(buffer, length, &tokens);
  for (unsigned int i = 0; i < tokens.count; i++) {
    struct token tok;
    ds_dynamic_array_get(&tokens, i, &tok);
    print_token(tok);
  }
}
