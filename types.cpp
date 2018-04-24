#include <iostream>
#include "types.h"

using namespace std;

string type_to_string(int type){
  if(type == 0) return "NTER";
  if(type == 1) return "TER";
  return "NON_DEF";
}


concat::concat(node* left, node* right):
  node("concat"),
  m_left(left),
  m_right(right)
{
  
}

concat::~concat(){
  delete m_left;
  delete m_right;
}

void concat::print_node(int offset){
  for(int i = 0; i<offset;i++){
    cout<<"-";
  }
  cout<<">"<<m_classe<<endl;
  //cout<<"left: ";
  m_left->print_node(offset*2);
  //cout<<"right: ";
  m_right->print_node(offset*2);
}

node* concat::left(){
  return m_left;
}

node* concat::right(){
  return m_right;
}

uniune::uniune(node* left, node* right):
  node("uniune"),
  m_left(left),
  m_right(right)
{
  
}

uniune::~uniune(){
  delete m_left;
  delete m_right;
}

void uniune::print_node(int offset){
  for(int i = 0; i<offset;i++){
    cout<<"-";
  }
  cout<<">"<<m_classe<<endl;
  m_left->print_node(offset*2);
  m_right->print_node(offset*2);
  
}

node* uniune::left(){
  return m_left;
}

node* uniune::right(){
  return m_right;
}


star::star(node* next):
  node("star"),
  m_next(next)
{
 
}

star::~star(){
  delete m_next;
}

void star::print_node(int offset){
  for(int i = 0; i<offset;i++){
    cout<<"-";
  }
  cout<<">"<<m_classe<<endl;
  m_next->print_node(offset*2);
}

node* star::next(){
  return m_next;
}


un::un(node* next):
  node("un"),
  m_next(next)
{
  
}

un::~un(){
  delete m_next;
}

void un::print_node(int offset){
  for(int i = 0; i<offset;i++){
    cout<<"-";
  }
  cout<<">"<<m_classe<<endl;
  m_next->print_node(offset*2);
}

node* un::next(){
  return m_next;
}


atom::atom(std::string code, int action, str_type type, std::string str):
  node("atom"),
  m_lexunit(new lex_unit(code,action,type,str))
{
  
}

atom::~atom(){
  delete m_lexunit;
}

lex_unit* atom::lexunit(){
  return m_lexunit;
}

void atom::print_node(int offset){
  for(int i=0; i<offset; i++){
    cout<<"-";
  }
  cout<<">"<<m_lexunit->code()<<" "<<type_to_string(m_lexunit->type())<<" "<<m_lexunit->action()<<" "<<m_lexunit->str()<<endl;
}

