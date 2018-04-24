#include <iostream>
#include "analyser.h"
#include "interpreter.h"

using namespace std;
/*
void print_lu(lex_unit& lu){
  cout<<"code ="<< lu.code() <<" action ="<<lu.action()
      <<" str ="<<lu.str()<<" type ="<<lu.type()<<endl;
}
*/

int main(int argc, char** argv){

  if(argc != 3){
    cout<<"usage: compilator gpl program_to_compile"<<endl;
    return 1;
  }
  
  forest* f = new forest();
  f->gen_forest();  
  //f->print_forest(2);

  analyser* an = new analyser(f,argv[1]);
  try{
    if(an->analyse(0)){
      cout<<"OK!!"<<endl;
    }else{
      cout<<"NOT OK!"<<endl;
    }
  }catch(runtime_error& e){
    cout<<"error: "<<e.what()<<endl;
  }

  an->print_dicot();
  an->print_dicont();

  f->print_forest(2);

  analyser* agpl = new analyser(f,argv[2]);
  try{
    if(agpl->analyse_gpl(5)){
      cout<<"OK!"<<endl;
    }else{
      cout<<"NOT OK!"<<endl;
    }
  }catch(runtime_error& e){
    cout<<"error: "<<e.what()<<endl;
  }

  agpl->print_dicot();
  agpl->print_dicont();


  agpl->print_pcode();

  interpreter* e = new interpreter(agpl->get_pcode());

  e->execute();
  
  return 0;
}
