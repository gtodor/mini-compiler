#include <iostream>
#include "tree.h"

using namespace std;

tree::tree(node* root,string code) : m_root(root), m_code(code){

}

tree::~tree(){
  delete m_root;
}

void tree::print_tree(int offset){
  m_root->print_node(offset);
}

node* tree::root(){
  return m_root;
}

string tree::code(){
  return m_code;
}
