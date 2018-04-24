all: compilator

compilator: main.cpp analyser.cpp scanner.cpp forest.cpp tree.cpp node.cpp types.cpp lex_unit.cpp interpreter.cpp
	g++ -Wall -Wextra -std=c++11 $^ -o $@

main.cpp: scanner.h

analyser.cpp: analyser.h forest.cpp

scanner.cpp: scanner.h lex_unit.h

forest.cpp: forest.h

tree.cpp: tree.h

node.cpp: node.h

types.cpp: types.h

lex_unit.cpp: lex_unit.h

interpreter.cpp: interpreter.h

PHONY: clean

clean:
	@rm *.o *~ ./compilator
