BIN = c-
CODE = parser
CC = gcc

SRCS = $(CODE).y $(CODE).l
HDRS = ASTNode.h
OBJS = lex.yy.o $(CODE).tab.o

$(BIN) : $(OBJS)
	$(CC) $(OBJS) -o $(BIN)

lex.yy.c : $(CODE).l $(CODE).tab.h $(HDR)
	flex $(CODE).l

$(CODE).tab.h $(CODE).tab.c : $(CODE).y
	bison -v -t -d $(CODE).y

clean :
	rm -f *~ $(OBJS) $(BIN) lex.yy.c $(CODE).tab.h $(CODE).tab.c $(BIN).txt

tar	: $(HDR) $(SRCS) makefile
	tar -cvf $(BIN).tar $(HDRS) $(SRCS) makefile