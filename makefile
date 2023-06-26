sql:sql.o parse.tab.o lex.yy.o
	gcc sql.o parse.tab.o lex.yy.o -o sql

sql.o:sql.c
	gcc -c sql.c -o sql.o

parse.tab.o:parse.tab.c
	gcc -c parse.tab.c -o parse.tab.o

lex.yy.o:lex.yy.c
	gcc -c lex.yy.c -o lex.yy.o
	
lex.yy.c:sql.l
	flex sql.l	

parse.tab.c:parse.y
	bison -d parse.y
	
.PHONY:clean
clean:
	rm -rf ./*.o
	rm -rf ./sql
	rm -rf ./parse.tab.c
	rm -rf ./parse.tab.h
	rm -rf ./lex.yy.c

