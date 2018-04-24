#include <iostream>
#include "lex_unit.h"


using namespace std;

lex_unit::lex_unit():
  m_code(""),
  m_action(0),
  m_type(NDEF),
  m_str("")
{

}

lex_unit::lex_unit(std::string code, int action, str_type type, std::string str):
  m_code(code),
  m_action(action),
  m_type(type),
  m_str(str)
{

}

lex_unit::~lex_unit(){

}

int lex_unit::action(){
  return m_action;
}

string lex_unit::code(){
  return m_code;
}

str_type lex_unit::type(){
  return m_type;
}

string lex_unit::str(){
  return m_str;
}

void lex_unit::set_action(int action){
  m_action = action;
}

void lex_unit::set_code(std::string code){
  m_code = code;
}

void lex_unit::set_type(str_type type){
  m_type = type;
}

void lex_unit::set_str(std::string str){
  m_str = str;
}


void lex_unit::reset(){
  m_str = "";
  m_type = NDEF;
  m_action = 0;
  m_code = "";
}
