#ifndef TREE_H
#define TREE_H

#include "node.h"
#include <string>

class tree{
public:
  tree(node* root,std::string code);
  ~tree();
  void print_tree(int offset);
  node* root();
  std::string code();

private:
  node* m_root;
  std::string m_code;
};




#endif //TREE_H
