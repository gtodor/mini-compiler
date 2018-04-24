#ifndef FOREST_H
#define FOREST_H

#include <vector>
#include <string>
#include "tree.h"

class forest{
public:
  forest();
  ~forest();
  void gen_forest();//hardcoded trees
  void print_forest(int offset);
  tree* get(int index);
  void insert(tree* t);
  int get_index_base(std::string code);
  int get_index_other(std::string code);

private:
  std::vector<tree*> m_forest;
  int sep_index;//separation: hardcoded trees and generated trees
};




#endif //FOREST_H
