#ifndef ANALYSER_H
#define ANALYSER_H

#include <string>
#include <vector>
#include <stack>
#include "scanner.h"
#include "forest.h"
#include "types.h"

class analyser{
public:
  analyser(forest* f, std::string file_name);
  ~analyser();
  bool analyse(int index);
  bool analyse_gpl(int index);
  void print_dicot();
  void print_dicont();
  void insertt(std::string str);
  void insertnt(std::string str);
  std::string searcht(std::string str);
  std::string searchnt(std::string str);
  void print_pcode();
  std::vector<std::string> get_pcode();

private:
  forest* m_forest;
  scanner* m_scanner;
  lex_unit lu;
  std::vector<std::string> m_dicot;
  std::vector<std::string> m_dicont;
  std::stack<node*> temp;
  std::vector<std::string> pcode;
  std::stack<std::string> tempcode;
  bool analyse(node* n);
  bool analyse_gpl(node* n);
  void g0action(int action);
  void gplaction(int action);
};

#endif//ANALYSER_H
