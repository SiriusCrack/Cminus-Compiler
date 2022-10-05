BIN = c-

lexsrc = parser.l
yaccsrc = parser.y
headers = Token.h ASTNode.h
src = main.c ASTNode.c

lexgens = lex.yy.c
yaccgens = parser.tab.h parser.tab.c parser.output
srcobjs = main.o ASTNode.o
lexyaccobjs = lex.yy.o parser.tab.o

$(BIN) : $(lexyaccobjs) $(srcobjs)
	gcc $(lexyaccobjs) $(srcobjs) -o $(BIN)

$(srcobjs) : $(headers) $(src)
	gcc $(src) -c

$(lexgens) : $(lexsrc) $(yaccgens) $(headers)
	flex $(lexsrc)

$(yaccgens) : $(yaccsrc) $(headers)
	bison -v -t -d $(yaccsrc)

clean :
	rm -f $(BIN) $(BIN).tar $(lexgens) $(yaccgens) $(srcobjs) $(lexyaccobjs) parser.out

tar	: $(lexsrc) $(yaccsrc) $(headers) $(src) makefile
	tar -cvf $(BIN).tar $(lexsrc) $(yaccsrc) $(headers) $(src) makefile
