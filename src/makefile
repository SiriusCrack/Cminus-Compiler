BIN = c-

lexsrc = parser.l
yaccsrc = parser.y
headers = Token.h ASTNode.h SymbolTable.h SemanticAnalysis.h IOLoader.h Placement.h yyerror.h emitcode.h codegen.h
src = lex.yy.c parser.tab.c main.c ASTNode.c SymbolTable.c SemanticAnalysis.c IOLoader.c Placement.c yyerror.c emitcode.cpp codegen.cpp

lexgens = lex.yy.c
yaccgens = parser.tab.h parser.tab.c parser.output
srcobjs = main.o ASTNode.o SymbolTable.o SemanticAnalysis.o IOLoader.o Placement.o yyerror.o emitcode.o codegen.o
lexyaccobjs = lex.yy.o parser.tab.o

$(BIN) : $(lexyaccobjs) $(srcobjs)
	g++ $(lexyaccobjs) $(srcobjs) -o $(BIN)

$(srcobjs) : $(headers) $(src)
	g++ $(src) -c -Wno-write-strings

$(lexgens) : $(lexsrc) $(yaccgens) $(headers)
	flex $(lexsrc)

$(yaccgens) : $(yaccsrc) $(headers)
	bison -v -t -d $(yaccsrc)

clean :
	rm -f $(BIN) $(BIN).tar $(lexgens) $(yaccgens) $(srcobjs) $(lexyaccobjs) parser.out

tar	: $(lexsrc) $(yaccsrc) $(headers) $(src) makefile
	tar -cvf $(BIN).tar $(lexsrc) $(yaccsrc) $(headers) $(src) makefile
