bison -d x_econv.y
flex x_econv.l
g++ main_class.cc x_econv.tab.c lex.yy.c -lfl -o x_econv
