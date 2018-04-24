#ifndef SCANNER_H
#define SCANNER_H

#include <fstream>
#include <vector>
#include <string>
#include <list>
#include "lex_unit.h"

class scanner{
private:
  std::ifstream file;
  std::list<char> text;
  std::vector<std::string> complex_symbols = {"->","==","<=",">=","!=","(|","|)"};
  std::vector<std::string> simple_symbols = {".",",",";","]","[","(",")","+","*",">","<","-","/"};
  std::vector<std::string> gpl_keywords = {"Program","Begin","End","if","then","else","while","true","false","write","EndProg","EndIf","Repeat","do","read"};
public:
  scanner(std::string file_name);
  ~scanner();
  void remove_whitespaces();
  int scan(lex_unit& lu, bool gpl=false);
  bool find_elem(std::string val);
  bool find_elem(std::vector<std::string> arr,std::string val);
};

#endif //SCANNER_H
