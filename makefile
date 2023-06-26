sql:sql.o sql.tab.o lex.yy.o
	gcc sql.o sql.tab.o lex.yy.o -o sql

sql.o:sql.c
	gcc -c sql.c -o sql.o

sql.tab.o:sql.tab.c
	gcc -c sql.tab.c -o sql.tab.o

lex.yy.o:lex.yy.c
	gcc -c lex.yy.c -o lex.yy.o

sql.tab.c:sql.y
	bison -d sql.y
	
lex.yy.c:sql.l
	flex sql.l	

.PHONY:clean
clean:
	rm -rf ./*.o
	rm -rf ./sql
	rm -rf ./sql.tab.c
	rm -rf ./sql.tab.h
	rm -rf ./lex.yy.c

