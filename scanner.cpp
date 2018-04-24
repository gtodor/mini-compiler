#include <iostream>
#include <cctype>
#include <sstream>
#include <vector>
#include <cstdlib>
#include "scanner.h"

using namespace std;

scanner::scanner(std::string file_name){
  file.open(file_name.c_str());
  if(file){
    file.seekg(0,ios::end);
    int length = file.tellg();
    file.seekg(0,ios::beg);

    char* buffer = new char[length];

    file.read(buffer,length);

    for(int i = 0; i<length; i++){
      text.push_back(buffer[i]);
    }
     
    file.close();
    delete[] buffer;

    // while(!text.empty()){
    //   cout<<text.front();
    //   text.pop_front();
    // }
  }else{
    throw std::runtime_error("File could not be loaded");
  }
}

scanner::~scanner(){

}

void scanner::remove_whitespaces(){
  if(text.empty()) return;
  char c = text.front();
  while(c == ' ' || c == '\n' || c == '\t'){
    text.pop_front();
    if(text.empty()) return;
    c = text.front();
    //cout<<"removing white"<<endl;
  }
}


bool scanner::find_elem(string val){
  for(unsigned int i = 0; i< complex_symbols.size(); i++){
    if(complex_symbols[i] == val) return true;
  }
  for(unsigned int i = 0; i<simple_symbols.size(); i++){
    if(simple_symbols[i] == val) return true;
  }
  return false;
}

bool scanner::find_elem(vector<string> arr, string val){
  for(unsigned int i = 0; i<arr.size(); i++){
    if(arr[i] == val) return true;
  }
  return false;
}

int scanner::scan(lex_unit& lu , bool gpl){
  vector<string> complex_symbols = {"->","==","<=",">=","!=","(|","|)"};
  vector<string> simple_symbols = {".",",",";","]","[","(",")","+","*","=",">","<","-","/"};
  //cout <<"cslen = "<< cslen<< endl;
  if(text.empty()) return 0;//end of the file
  char c1 = text.front();
  
  //Build a symbol
  if(!(isdigit(c1) || isalpha(c1) || c1 == '\"' || c1 == '\'')){
    stringstream ss;
    ss<<c1;
    text.pop_front();
    if(text.empty()) return 0;
    char c2 = text.front();
    
    //test if the symbol is alone
    if(c2 == ' ' || isalpha(c2) || isdigit(c2)){
      if(find_elem(simple_symbols,ss.str())==true){
	lu.set_code(ss.str());
	lu.set_type(TERMINAL);
	lu.set_str(ss.str());
	remove_whitespaces();
	return 1;
      }
      cout<<"symbol "<<ss.str()<<" not valid"<<endl;
      return -1;
    }else{

      ss << c2;

      //test if the two symbols make a complex symbol or not
      if(find_elem(complex_symbols,ss.str()) == true){
	text.pop_front();
	lu.set_code(ss.str());
	lu.set_type(TERMINAL);
	lu.set_str(ss.str());
	
	if(text.empty()) return 0;
	char b = text.front();

	//test if next there is an action
	if(b == '#'){
	  text.pop_front();
	  if(text.empty()) return 0;
	  b = text.front();
	  stringstream saction;
	  while(isdigit(b)){
	    saction << b;
	    text.pop_front();
	    if(text.empty()) return 0;
	    b = text.front();
	  }
	  int action = atoi(saction.str().c_str());
	  lu.set_action(action);
	}
	
	remove_whitespaces();
	return 1;
      }
      string res = ss.str();
      res.erase(1);//removes the second character

      //test if the first symbol is valid
      if(find_elem(simple_symbols,res)==true){
	//cout<<"WRITING SINGLE CHAR"<<endl;
	//text.pop_front();
	lu.set_code(res);
	lu.set_type(TERMINAL);
	lu.set_str(res);

	//verify if next char is #
	if(c2 == '#'){
	  //cout<<"holla"<<endl;
	  text.pop_front();
	  if(text.empty()) return 0;
	  char a = text.front();
	  stringstream saction;
	  while(isdigit(a)){
	    saction << a;
	    
	    text.pop_front();
	    if(text.empty()) return 0;
	    a = text.front();
	  }
	  int action = atoi(saction.str().c_str());
	  lu.set_action(action);
	}
	
	remove_whitespaces();
	return 1;
      }
      cout<<"symbol "<<res<<" is not valid"<<endl;
      return -1;
    }
  }else if(c1 == '\"' || c1 == '\''){//build a terminal string
    text.pop_front();
    if(text.empty()) return 0;
    c1 = text.front();
    stringstream ss;
    while(c1 != '\''  && c1 != '\"'){
      ss << c1;
      text.pop_front();
      if(text.empty()) return 0;
      c1 = text.front();
    }
    text.pop_front();
    string res = ss.str();
    
    lu.set_code("elter");
    
    lu.set_type(TERMINAL);
    lu.set_str(res);

    if(text.empty()) return 0;
    char b = text.front();
    
    //verify if next char is #
    if(b == '#'){
      //cout<<"holla"<<endl;
      text.pop_front();
      if(text.empty()) return 0;
      b = text.front();
      stringstream saction;
      while(isdigit(b)){
	//cout<<"b ="<<b<<endl;
	saction << b;
	text.pop_front();
	if(text.empty()) return 0;
	b = text.front();
      }
      int action = atoi(saction.str().c_str());
      lu.set_action(action);
    }

    remove_whitespaces();
    return 1;
    
  }else if(isalpha(c1)){//build a nonterminal string
    text.pop_front();
    stringstream ss;
    ss << c1;
    
    if(text.empty()) return 0;
    c1 = text.front();
    
    while((isalpha(c1) || isdigit(c1)) && c1 != ' '){
      ss << c1;
      text.pop_front();
      if(text.empty()) return 0;
      c1 = text.front();
      
    }
    string res = ss.str();
    //cout<<"res = "<<res<<endl;
    if(gpl == true){
      if(find_elem(gpl_keywords,res)){
	lu.set_code(res);
      }else{
	lu.set_code("variable");
      }
      lu.set_type(TERMINAL);
    }else{
      lu.set_code("idnter");
      lu.set_type(NON_TERMINAL);
    }
    
    lu.set_str(res);

    if(text.empty()) return 0;
    char b = text.front();
    
    //verify if next char is #
    if(b == '#'){
      text.pop_front();
      if(text.empty()) return 0;
      b = text.front();
      stringstream saction;
      while(isdigit(b)){
	saction << b;
	text.pop_front();
	if(text.empty()) return 0;
	b = text.front();
      }
      int action = atoi(saction.str().c_str());
      lu.set_action(action);
    }
    
    remove_whitespaces();
    return 1;
  }else if(isdigit(c1)){//build a number
    text.pop_front();
    stringstream ss;
    ss << c1;
    
    if(text.empty()) return 0;
    c1 = text.front();
    
    while(isdigit(c1)){
      ss << c1;
      text.pop_front();
      if(text.empty()) return 0;
      c1 = text.front();
    }
    if(isalpha(c1)){
      cout<<"number can not be followed by letters"<<endl;
      return -1;
    }
    //int number = atoi(ss.str().c_str());
    lu.set_code("number");
    lu.set_action(0);
    lu.set_str(ss.str());
    lu.set_type(TERMINAL);

    remove_whitespaces();
    return 1;
  }
  return 1;
}
