#include <iostream>
#include "node.h"

using namespace std;


node::node(string classe): m_classe(classe){

}

node::~node(){

}

string node::classe(){
  return m_classe;
}

