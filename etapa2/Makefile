#  Etapa 2 - Compiladores 2024/1
#      Autor: Matheus Lima 

etapa2: y.tab.o lex.yy.o main.o hash.o
	gcc -o etapa2 y.tab.o lex.yy.o main.o hash.o
main.o: main.c
	gcc -c main.c
hash.o: hash.c
	gcc -c hash.c
y.tab.o: y.tab.c
	gcc -c y.tab.c
y.tab.c: parser.y
	yacc parser.y -d -v
lex.yy.o: lex.yy.c
	gcc -c lex.yy.c
lex.yy.c: scanner.l
	flex --header-file=lex.yy.h scanner.l 
clean:
	rm *.o lex.yy.c lex.yy.h y.tab.c y.output y.tab.h etapa2
