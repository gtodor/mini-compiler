#ifndef NODE_H
#define NODE_H

#include <string>

class node{
public:
  node(std::string classe);
  virtual ~node();
  std::string classe();
  virtual void print_node(int offset) = 0;

protected:
  std::string m_classe;
};





#endif //NODE_H
