BIN = c-

lexsourcefiles = parser.l
yaccsourcefiles = parser.y
headers = scanType.h ASTNode.h NodeVector.h
headersourcefiles = ASTNode.c NodeVector.c

lexgens = lex.yy.c
yaccgens = parser.tab.h parser.tab.c parser.output
headerobjs = ASTNode.o NodeVector.o
lexyaccobjs = lex.yy.o parser.tab.o

$(BIN) : $(lexyaccobjs) $(headerobjs)
	gcc $(lexyaccobjs) $(headerobjs) -o $(BIN)

$(headerobjs) : $(headers) $(headersourcefiles)
	gcc $(headersourcefiles) -c

$(lexgens) : $(lexsourcefiles) $(yaccgens) $(headers)
	flex $(lexsourcefiles)

$(yaccgens) : $(yaccsourcefiles) $(headers)
	bison -v -t -d $(yaccsourcefiles)

clean :
	rm -f $(BIN) $(lexgens) $(yaccgens) $(headerobjs) $(lexyaccobjs)

tar	: $(lexsourcefiles) $(yaccsourcefiles) $(headers) $(headersourcefiles) makefile
	tar -cvf $(BIN).tar $(lexsourcefiles) $(yaccsourcefiles) $(headers) $(headersourcefiles) makefile