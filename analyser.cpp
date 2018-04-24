#include <iostream>
#include "analyser.h"

using namespace std;

void print(lex_unit& lu){
  cout<<"code ="<< lu.code() <<" action ="<<lu.action()
      <<" str ="<<lu.str()<<" type ="<<lu.type()<<endl;
}

void analyser::insertt(string str){
  bool found = false;
  for(unsigned int i=0; i<m_dicot.size();i++){
    if(m_dicot[i] == str){
      found = true;
      break;
    }
  }
  if(!found){
    m_dicot.push_back(str);
  }
}

void analyser::insertnt(string str){
  bool found = false;
  for(unsigned int i=0; i<m_dicont.size();i++){
    if(m_dicont[i] == str){
      found = true;
      break;
    }
  }
  if(!found){
    m_dicont.push_back(str);
  }
}

analyser::analyser(forest* f, string file_name):
  m_forest(f),
  m_scanner(new scanner(file_name))
{
  
}

analyser::~analyser()
{
  delete m_forest;
  delete m_scanner;
}

bool analyser::analyse(int index){
  node* start = m_forest->get(index)->root();
  m_scanner->scan(lu);
  print(lu);
  return analyse(start);
}

bool analyser::analyse(node* n){
  if(n->classe() == "concat"){
    concat* cnode = (concat*) n;
    if(analyse(cnode->left())){
      return analyse(cnode->right());
    }
    return false;
  }
  if(n->classe() == "uniune"){
    uniune* unode = (uniune*) n;
    if(analyse(unode->left())){
      return true;
    }else{
      return analyse(unode->right());
    }
  }
  if(n->classe() == "star"){
    star* snode = (star*) n;
    while(analyse(snode->next())){

    }
    return true;
  }
  if(n->classe() == "un"){
    un* unnode =(un*) n;
    analyse(unnode->next());
    return true;
  }
  if(n->classe() == "atom"){
    atom* anode = (atom*) n;
    lex_unit* l = anode->lexunit();
    switch(l->type()){
    case TERMINAL:{
      if(l->code() == lu.code()){
	if(l->action() != 0){
	  g0action(l->action());
	}
	if(lu.code() == "elter"){
	  insertt(lu.str());
	}else if(lu.code() == "idnter"){
	  insertnt(lu.str());
	}
	lu.reset();
	m_scanner->scan(lu);
	//cout<<"elem analysed with success"<<endl;
	//print(lu);
	return true;
      }else{
	return false;
      }
    }break;
    case NON_TERMINAL:{
      //cout<<"researching index of the tree where to jump: ";
      int index_next_tree = m_forest->get_index_base(l->str());
      if(index_next_tree == -1){
	throw runtime_error("index of tree could not be found");
      }
      //cout<<index_next_tree<<endl;
      node* other_node = m_forest->get(index_next_tree)->root();
      if(analyse(other_node)){
	if(l->action() != 0){
	  g0action(l->action());
	}
	
	return true;
      }else{
	return false;
      }
    }break;
    default: return false;
    }
  }
  return false;
}

string analyser::searchnt(string str){
  insertnt(str);
  return str;
}

string analyser::searcht(string str){
  insertt(str);
  return str;
}



void analyser::g0action(int action){
  switch(action){
  case 1:{
    node* n1 = temp.top();
    temp.pop();
    node* n2 = temp.top();
    atom* title = (atom*)n2;
    temp.pop();
    tree* t = new tree(n1,title->lexunit()->str());
    m_forest->insert(t);
  }break;
  case 2 :{
    node* res = new atom("idnter",lu.action(),NON_TERMINAL,searchnt(lu.str()));
    temp.push(res);
  }break;
  case 3:{
    node* n1 = temp.top();
    temp.pop();
    node* n2 = temp.top();
    temp.pop();
    node* res = new uniune(n2,n1);
    temp.push(res);
  }break;
  case 4:{
    node* n1 = temp.top();
    temp.pop();
    node* n2 = temp.top();
    temp.pop();
    node* res = new concat(n2,n1);
    temp.push(res);
  }break;
  case 5:{
    if(lu.type() == TERMINAL){
      string code;
      if(lu.code() == "elter"){
        if(lu.str() == "IDNTER"){
	  code = "idnter";
	}else{
	  code = lu.str();
	}
      }
      node* res = new atom(code,lu.action(),TERMINAL,searcht(lu.str()));
      temp.push(res);
    }else{
      node* res = new atom("idnter",lu.action(),NON_TERMINAL,searchnt(lu.str()));
      temp.push(res);
    }
  }break;
  case 6:{
    node* n = temp.top();
    temp.pop();
    node* res = new star(n);
    temp.push(res);
  }break;
  case 7:{
    node* n = temp.top();
    temp.pop();
    node* res = new un(n);
    temp.push(res);
  }break;
  default:break;
  }
}

void analyser::print_dicot(){
  cout<<"dicot : "<<endl;
  for(unsigned int i=0; i<m_dicot.size();i++){
    cout<<m_dicot[i]<<" | ";
  }
  cout<<endl;
}

void analyser::print_dicont(){
  cout<<"dicont : "<<endl;
  for(unsigned int i = 0; i<m_dicont.size(); i++){
    cout<<m_dicont[i]<<" | ";
  }
  cout<<endl;
}

bool analyser::analyse_gpl(int index){
  node* start = m_forest->get(index)->root();
  m_scanner->scan(lu,true);
  print(lu);
  return analyse_gpl(start);
}

bool analyser::analyse_gpl(node* n){
  if(n->classe() == "concat"){
    concat* cnode = (concat*) n;
    if(analyse_gpl(cnode->left())){
      return analyse_gpl(cnode->right());
    }
    return false;
  }
  if(n->classe() == "uniune"){
    uniune* unode = (uniune*) n;
    if(analyse_gpl(unode->left())){
      return true;
    }else{
      return analyse_gpl(unode->right());
    }
  }
  if(n->classe() == "star"){
    star* snode = (star*) n;
    while(analyse_gpl(snode->next())){

    }
    return true;
  }
  if(n->classe() == "un"){
    un* unnode =(un*) n;
    analyse_gpl(unnode->next());
    return true;
  }
  if(n->classe() == "atom"){
    atom* anode = (atom*) n;
    lex_unit* l = anode->lexunit();
    //cout<<"elem in the tree: ";
    //print(*l);
    //cout<<"elem read : ";
    //print(lu);
    //cout<<endl;
    switch(l->type()){
    case TERMINAL:{
      if(l->code() == lu.code()){
	if(l->action() != 0){
	  gplaction(l->action());
	}
	if(lu.code() == "elter"){
	  insertt(lu.str());
	}else if(lu.code() == "idnter"){
	  insertnt(lu.str());
	}
	lu.reset();
	m_scanner->scan(lu,true);
	//cout<<"elem analysed with success"<<endl;
	//print(lu);
	return true;
      }else{
	return false;
      }
    }break;
    case NON_TERMINAL:{
      //cout<<"researching index of the tree where to jump: ";
      int index_next_tree = m_forest->get_index_other(l->str());
      if(index_next_tree == -1){
	throw runtime_error("index of tree could not be found");
      }
      //cout<<index_next_tree<<endl;
      node* other_node = m_forest->get(index_next_tree)->root();
      if(analyse_gpl(other_node)){
	if(l->action() != 0){
	  gplaction(l->action());
	}
	
	return true;
      }else{
	return false;
      }
    }break;
    default: return false;
    }
  }
  return false;
}

void print_stack(stack<string> st){
  stack<string> temp(st);
  cout<<"stack : [";
  while(!temp.empty()){
    cout<<temp.top()<<" ,";
    temp.pop();
  }
  cout<<" ]"<<endl;
}

void analyser::gplaction(int action){
  //cout<<endl<<"action = "<<action<<endl;
  //print_pcode();
  //print_stack(tempcode);
  //cout<<endl;
  switch(action){
  case 1:{
    pcode.push_back("lda");
    pcode.push_back(lu.str());
  }break;
  case 2:{
    tempcode.push("aff");
  }break;
  case 3:{
    pcode.push_back("ldc");
    pcode.push_back(lu.str());
    string inst = tempcode.top();
    tempcode.pop();
    pcode.push_back(inst);
  }break;
  case 4:{
    pcode.push_back("jif");
    pcode.push_back("");
    int add = pcode.size()-1;
    //cout<<"add (action 4) = "<<add<<endl;
    string address = to_string(add);
    //cout<<"address = "<<address<<endl;
    tempcode.push(address);
  }break;
  case 5:{
    pcode.push_back("jmp");
    int add = atoi(tempcode.top().c_str());
    //cout<<"add (action 5) = "<<add<<endl;
    tempcode.pop();
    string address = to_string(pcode.size()+1);
    //cout<<"address= "<<address<<endl;
    pcode[add]=address;
    string str = to_string(pcode.size());
    //cout<<"str = "<<str;
    tempcode.push(str);
    pcode.push_back("");
  }break;
  case 6:{
    cout<<tempcode.top()<<endl;
    int addr = atoi(tempcode.top().c_str());
    //cout<<"addr (action 6) = "<<addr<<endl;
    tempcode.pop();
    pcode[addr] = to_string(pcode.size());
  }break;
  case 7:{
    tempcode.push("or");
  }break;
  case 8:{
    string inst = tempcode.top();
    tempcode.pop();
    pcode.push_back(inst);
  }break;
  case 9:{
    tempcode.push("and");
  }break;
  case 10:{
    tempcode.push("not");
  }break;
  case 11:{
    pcode.push_back("ldc");
    pcode.push_back(lu.str());
  }break;
  case 12:{
    pcode.push_back("1");
  }break;
  case 13:{
    tempcode.push("eg");
  }break;
  case 14:{
    tempcode.push("sup");
  }break;
  case 15:{
    tempcode.push("inf");
  }break;
  case 16:{
    tempcode.push("supe");
  }break;
  case 17:{
    tempcode.push("infe");
  }break;
  case 18:{
    tempcode.push("add");
  }break;
  case 19:{
    pcode.push_back("stop");
  }break;
  case 20:{
    string inst = tempcode.top();
    tempcode.pop();
    pcode.push_back(inst);
  }break;
  case 21:{
    pcode.push_back("ldv");
    pcode.push_back(lu.str());
  }break;
  case 22:{
    string inst = tempcode.top();
    tempcode.pop();
    pcode.push_back(inst);
    inst = tempcode.top();
    if(inst == "aff"){
      tempcode.pop();
      pcode.push_back(inst);
    }
  }break;
  case 23:{
    pcode.push_back("write");
  }break;
  case 24:{
    tempcode.push("diff");
  }break;
  case 25:{
    pcode.push_back("0");
  }break;
  case 26:{
    string address = tempcode.top();
    tempcode.pop();
    int addr = stoi(address);
    pcode.push_back("jmp");
    string jtaddr = to_string(addr - 6);
    pcode.push_back(jtaddr);
    pcode[addr] = to_string(pcode.size());
  }break;
  case 27:{
    tempcode.push("mult");
  }break;
  case 28:{
    tempcode.push("subst");
  }break;
  case 29:{
    tempcode.push("div");
  }break;
  case 30:{
    pcode.push_back("rd");
  }break;
  }
}

void analyser::print_pcode(){
  cout<<"pcode : [";
  for(unsigned int i=0; i<pcode.size(); i++){
    cout<<pcode[i]<<" ,";
  }
  cout<<" ]"<<endl;
}


vector<string> analyser::get_pcode(){
  return pcode;
}

