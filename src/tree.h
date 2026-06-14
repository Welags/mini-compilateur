/* tree.h */
#ifndef TREE_H
#define TREE_H
typedef enum {
  E,
  T,
  divstar,
  id,
  program,
  declarations,
  type,
  functions,
  function,
  parameters,
  body,
  instructions,
  heading,
  assign,
  condition,
  if_,
  else_,
  while_,
  return_,
  arguments,
  or_,
  and_,
  compare,
  order,
  add,
  sub,
  positif,
  negatif,
  num,
  character,
  not_,
  structure,
  contenustruct,
  declaration,
  call_function,
  field_dot

 


  /* list all other node labels, if any */
  /* The list must coincide with the string array in tree.c */
  /* To avoid listing them twice, see https://stackoverflow.com/a/10966395 */
} label_t;

typedef struct Node {
  label_t label;
  struct Node *firstChild, *nextSibling;
  int lineno;
  char ident[64];
} Node;

Node *makeNode(label_t label);
Node *makeNodeString(label_t label,char *valeur);
void addSibling(Node *node, Node *sibling);
void addChild(Node *parent, Node *child);
void deleteTree(Node*node);
void printTree(Node *node);

#define FIRSTCHILD(node) node->firstChild
#define SECONDCHILD(node) node->firstChild->nextSibling
#define THIRDCHILD(node) node->firstChild->nextSibling->nextSibling
#endif