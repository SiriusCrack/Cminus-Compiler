BIN = c-
CODE = parser
CC = gcc

SRCS = $(CODE).y $(CODE).l
HDRS = ASTNode.h scanType.h NodeVector.h
OBJS = lex.yy.o $(CODE).tab.o

$(BIN) : $(OBJS)
	$(CC) $(OBJS) ASTNode.c NodeVector.c -o $(BIN)

lex.yy.c : $(CODE).l $(CODE).tab.h $(HDR)
	flex $(CODE).l

$(CODE).tab.h $(CODE).tab.c : $(CODE).y
	bison -v -t -d $(CODE).y

clean :
	rm -f *~ $(OBJS) $(BIN) lex.yy.c $(CODE).tab.h $(CODE).tab.c $(BIN).txt $(CODE).output

tar	: $(HDR) $(SRCS) makefile
	tar -cvf $(BIN).tar $(HDRS) $(SRCS) makefile