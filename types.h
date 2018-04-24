#ifndef TYPES_H
#define TYPES_H

#include "node.h"
#include "lex_unit.h"

class concat : public node{
public:
  concat(node* left, node* right);
  ~concat();
  void print_node(int offset);
  node* left();
  node* right();

private:
  node* m_left;
  node* m_right;
};


class uniune : public node{
public:
  uniune(node* left, node* right);
 ~uniune();
  void print_node(int offset);
  node* left();
  node* right();

private:
 node* m_left;
 node* m_right;
};

class star : public node{
public:
  star(node* next);
  ~star();
  void print_node(int offset);
  node* next();

private:
  node* m_next;
};

class un : public node{
public:
  un(node* next);
  ~un();
  void print_node(int offset);
  node* next();

private:
  node* m_next;
};

class atom : public node{
public:
  atom(std::string code, int action, str_type type, std::string str);
  ~atom();
  lex_unit* lexunit();
  void print_node(int offset);

private:
  lex_unit* m_lexunit;
};



#endif //TYPES_H
