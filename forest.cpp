#include <iostream>
#include "forest.h"
#include "types.h"

using namespace std;


forest::forest(): sep_index(5){

}

forest::~forest(){

}

void forest::gen_forest(){
  tree* S0 = new tree(new concat(new star(new concat(new concat(new concat(new atom("idnter",0,NON_TERMINAL,"N"),new atom("->",0,TERMINAL,"->")),new atom("idnter",0,NON_TERMINAL,"E")),new atom(",",1,TERMINAL,","))),new atom(";",0,TERMINAL,";")),"S0");
  m_forest.push_back(S0);

  tree* N = new tree(new atom("idnter",2,TERMINAL,"IDNTER"),"N");
  m_forest.push_back(N);
  
  tree* E = new tree(new concat(new atom("idnter",0,NON_TERMINAL,"T"),new star(new concat(new atom("+",0,TERMINAL,"+"),new atom("idnter",3,NON_TERMINAL,"T")))),"E");
  m_forest.push_back(E);

  tree* T = new tree(new concat(new atom("idnter",0,NON_TERMINAL,"F"),new star(new concat(new atom(".",0,TERMINAL,"."),new atom("idnter",4,NON_TERMINAL,"F")))),"T");
  m_forest.push_back(T);

  
  tree* F = new tree(new uniune(new atom("idnter",5,TERMINAL,"IDNTER"),new uniune(new atom("elter",5,TERMINAL,"ELTER"),new uniune(new concat(new atom("(",0,TERMINAL,"("),new concat(new atom("idnter",0,NON_TERMINAL,"E"),new atom(")",0,TERMINAL,")"))),new uniune(new concat(new atom("[",0,TERMINAL,"["),new concat(new atom("idnter",0,NON_TERMINAL,"E"),new atom("]",6,TERMINAL,"]"))),new concat(new atom("(|",0,TERMINAL,"(|"),new concat(new atom("idnter",0,NON_TERMINAL,"E"),new atom("|)",7,TERMINAL,"|)"))))))),"F");
  m_forest.push_back(F);
  
}

void forest::print_forest(int offset){
  for(unsigned int i = 0; i<m_forest.size(); i++){
    cout<<"m_forest["<<i<<"] ("<<m_forest[i]->code() <<") : "<<endl;
    m_forest[i]->print_tree(offset);
    cout<<endl;
  }
}


tree* forest::get(int index){
  return m_forest[index];
}

void forest::insert(tree* t){
  m_forest.push_back(t);
}

int forest::get_index_base(string code){
  for(int i=0; i<sep_index ;i++){
    if(m_forest[i]->code() == code){
      return i;
    }
  }
  return -1;
}

int forest::get_index_other(string code){
  for(unsigned int i = sep_index; i<m_forest.size();i++){
    if(m_forest[i]->code() == code){
      return i;
    }
  }
  return -1;
}
