#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <vector>
#include <string>
#include <map>

class interpreter{
private:
  std::vector<std::string> m_pcode;
  std::vector<int> m_pilex;
  std::map<std::string,int> vars;
  int c0;
  int spx;
  
public:
  interpreter(std::vector<std::string> pcode);
  void execute();
  void interpret(std::string inst);
  int findvar(std::string var);
  void print_pcode();
  void print_pilex();
};






#endif //INTERPRETER
