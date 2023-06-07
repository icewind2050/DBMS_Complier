sql:sql.o sqlParse.tab.o lex.yy.o
	gcc sql.o sqlParse.tab.o lex.yy.o -o sql

sql.o:sql.c
	gcc -c sql.c -o sql.o

sqlParse.tab.o:sqlParse.tab.c
	gcc -c sqlParse.tab.c -o sqlParse.tab.o

lex.yy.o:lex.yy.c
	gcc -c lex.yy.c -o lex.yy.o

sqlParse.tab.c:sqlParse.y
	bison -d sqlParse.y
	
lex.yy.c:sqlLex.l
	flex sqlLex.l	

.PHONY:clean
clean:
	rm -rf ./*.o
	rm -rf ./sql
	rm -rf ./sqlParse.tab.c
	rm -rf ./sqlParse.tab.h
	rm -rf ./lex.yy.c

