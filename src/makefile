BIN = c-

OBJECTS = main.o $(LEXYACCOBJECTS) ASTNode.o SymbolTable.o SemanticAnalysis.o IOLoader.o Placement.o yyerror.o emitcode.o codegen.o
SOURCES = main.c $(LEXGENERATIONS) $(YACCGENERATIONS) ASTNode.c SymbolTable.c SemanticAnalysis.c IOLoader.c Placement.c yyerror.c emitcode.cpp codegen.c
HEADERS = Token.h ASTNode.h SymbolTable.h SemanticAnalysis.h IOLoader.h Placement.h yyerror.h emitcode.h codegen.h
LEXYACCOBJECTS = lex.yy.o parser.tab.o
YACCGENERATIONS = parser.tab.c
LEXGENERATIONS = lex.yy.c

$(BIN) : $(OBJECTS)
	g++ $(OBJECTS) -o $(BIN)
	rm -f $(OBJECTS) parser.output

$(OBJECTS) : $(SOURCES) $(HEADERS)
	g++ $(SOURCES) -c -Wno-write-strings

$(LEXGENERATIONS) : parser.l $(YACCGENERATIONS) parser.tab.h $(HEADERS)
	flex parser.l

$(YACCGENERATIONS) : parser.y $(HEADERS)
	bison -v -t -d parser.y

clean :
	rm -f $(BIN) $(BIN).tar $(OBJECTS) parser.output

tar	: $(SOURCES) $(HEADERS) parser.l parser.y makefile
	tar -cvf $(BIN).tar $(SOURCES) $(HEADERS) parser.l parser.y makefile
