#include <iostream>
#include <unistd.h>
#include "interpreter.h"

using namespace std;


interpreter::interpreter(vector<string> pcode): m_pcode(pcode),
						m_pilex(20,0),
						c0(0),
						spx(-1)
{

}

int interpreter::findvar(string var){
  for(auto& x : vars){
    if(x.first == var){
      return x.second;
    }
  }
  vars.insert(std::pair<string,int>(var,vars.size()));
  //cout<<endl<<"spx ="<<spx<<" and vars.size() ="<<vars.size()<<endl;
  if((unsigned int)spx > vars.size()-1){
    for(unsigned int i=spx; i>vars.size()-1; i--){
      m_pilex[i+1] = m_pilex[i];
    }
  }
  m_pilex[vars.size()-1] = 0;
  spx++;
  
  return vars.size()-1;
}

void interpreter::interpret(string inst){
  if(inst == "lda"){
    spx++;
    string var = m_pcode[c0+1];
    int addr = findvar(var);
    //cout<<"returned address = "<<addr<<endl;
    m_pilex[spx] = addr;
    c0= c0+2;
  }else if(inst == "ldv"){
    spx++;
    string var = m_pcode[c0+1];
    int addr = findvar(var);
    //cout<<"var = "<<var<<" address = "<<addr<<endl;
    m_pilex[spx] = m_pilex[addr];
    c0=c0+2;
  }else if(inst == "ldc"){
    spx++;
    m_pilex[spx] = stoi(m_pcode[c0+1]);
    c0 = c0+2;
  }else if(inst == "aff"){
    m_pilex[m_pilex[spx-1]] = m_pilex[spx];
    spx = spx - 2;
    c0++;
  }else if(inst == "jmp"){
    int pos = stoi(m_pcode[c0+1]);
    c0 = pos;
  }else if(inst == "jif"){
    if(m_pilex[spx] != 0){
      c0 = c0+2;
    }else{
      int pos = stoi(m_pcode[c0+1]);
      c0 = pos;
    }
    spx--;
  }else if(inst == "or"){
    int val1 = m_pilex[spx];
    int val2 = m_pilex[spx-1];
    spx--;
    m_pilex[spx] = val1 || val2;
    c0++;
  }else if(inst == "and"){
    int val1 = m_pilex[spx];
    int val2 = m_pilex[spx-1];
    spx--;
    m_pilex[spx] = val1 && val2;
    c0++;
  }else if(inst == "not"){
    if(m_pilex[spx] != 0){
      m_pilex[spx] = 0;
    }else{
      m_pilex[spx] = 1;
    }
    c0++;
  }else if(inst == "eg"){
    if(m_pilex[spx] == m_pilex[spx-1]){
      spx--;
      m_pilex[spx] = 1;
    }else{
      spx--;
      m_pilex[spx] = 0;
    }
    c0++;
  }else if(inst == "sup"){
    if(m_pilex[spx-1] > m_pilex[spx]){
      spx--;
      m_pilex[spx] = 1;
    }else{
      spx--;
      m_pilex[spx] = 0;
    }
    c0++;
  }else if(inst == "supe"){
    if(m_pilex[spx-1] >= m_pilex[spx]){
      spx--;
      m_pilex[spx] = 1;
    }else{
      spx--;
      m_pilex[spx] = 0;
    }
    c0++;
  }else if(inst == "inf"){
    if(m_pilex[spx-1] < m_pilex[spx]){
      spx--;
      m_pilex[spx] = 1;
    }else{
      spx--;
      m_pilex[spx] = 0;
    }
    c0++;
  }else if(inst == "diff"){
    if(m_pilex[spx-1] != m_pilex[spx]){
      spx--;
      m_pilex[spx] = 1;
    }else{
      spx--;
      m_pilex[spx] = 0;
    }
    c0++;
  }else if(inst == "infe"){
    if(m_pilex[spx-1] <= m_pilex[spx]){
      spx--;
      m_pilex[spx] = 1;
    }else{
      spx--;
      m_pilex[spx] = 0;
    }
    c0++;
  }else if(inst == "add"){
    int val1 = m_pilex[spx];
    int val2 = m_pilex[spx-1];
    spx--;
    m_pilex[spx] = val1 + val2;
    c0++;
  }else if(inst == "write"){
    cout<<m_pilex[spx]<<endl;
    c0++;
  }else if(inst == "mult"){
    int val1 = m_pilex[spx];
    int val2 = m_pilex[spx-1];
    spx--;
    m_pilex[spx] = val1 * val2;
    c0++;
  }else if(inst == "subst"){
    int val1 = m_pilex[spx];
    int val2 = m_pilex[spx-1];
    spx--;
    m_pilex[spx] = val2 - val1;
    c0++;
  }else if(inst == "div"){
    int val1 = m_pilex[spx];
    int val2 = m_pilex[spx-1];
    spx--;
    m_pilex[spx] = val2 / val1;
    c0++;
  }else if(inst == "rd"){
    spx++;
    int n;
    cin>>n;
    m_pilex[spx] = n;
    m_pilex[m_pilex[spx-1]] = m_pilex[spx];
    spx = spx - 2;
    c0 = c0+1;
  }
}

void interpreter::execute(){
  while(m_pcode[c0] != "stop"){
    if(m_pcode[c0] == "rd" || m_pcode[c0] == "write"){
      cout<<"code = "<<m_pcode[c0]<<" : ";
    }
    interpret(m_pcode[c0]);
    //print_pilex();
    //sleep(1);
  }
}

void interpreter::print_pcode(){
  cout<<"m_pcode = {";
  for(unsigned int i = 0; i<m_pcode.size(); i++){
    cout<<m_pcode[i]<<" , ";
  }
  cout<<"} spx = "<<spx<<endl;
}

void interpreter::print_pilex(){
  cout<<"m_pilex = [";
  for(int i=0; i<=spx; i++){
    cout<<m_pilex[i]<<" ,";
  }
  cout<<"]"<<endl;
}
