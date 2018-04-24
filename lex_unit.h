#ifndef LEX_UNIT_H
#define LEX_UNIT_H

#include <string>

enum str_type{
  NON_TERMINAL,
  TERMINAL,
  NDEF
};

class lex_unit{
private:
  std::string m_code;
  int m_action;
  str_type m_type;
  std::string m_str;
public:
  lex_unit();
  lex_unit(std::string code, int action, str_type type, std::string str);
  ~lex_unit();
  int action();
  std::string code();
  str_type type();
  std::string str();
  void set_action(int action);
  void set_code(std::string code);
  void set_type(str_type type);
  void set_str(std::string str);
  void reset();
};
  
#endif //SCANNER_H
