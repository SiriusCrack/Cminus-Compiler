BIN = c-

OBJECTS = main.o $(LYOBJS) ScanUtils.o
SOURCES = main.c $(LEXGEN) $(YACCGEN) ScanUtils.c
HEADERS = ScanUtils.h
LYOBJS = lex.yy.o parser.tab.o
LEXGEN = lex.yy.c
YACCGEN = parser.tab.c

$(BIN) : $(OBJECTS)
	gcc $(OBJECTS) -o $(BIN)
	rm -f $(OBJECTS) parser.out

$(OBJECTS) : $(SOURCES) $(HEADERS)
	gcc $(SOURCES) -c

$(LEXGEN) : parser.l $(YACCGEN) parser.tab.h $(HEADERS)
	flex parser.l

$(YACCGEN) : parser.y $(HEADERS)
	bison -v -t -d parser.y

clean :
	rm -f $(BIN) $(BIN).tar $(OBJECTS) parser.out

tar :
	tar -cvf $(BIN).tar $(SOURCES) $(HEADERS) parser.l parser.y makefile
