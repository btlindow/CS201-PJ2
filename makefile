OBJS = main.o scanner.o node.o queue.o bst.o avl.o
OPTS = -Wall -Wextra -g -std=c99

trees: $(OBJS)
	gcc $(OPTS) $(OBJS) -o trees

main.o: main.c scanner.h node.h queue.h bst.h avl.h
	gcc $(OPTS) -c main.c

scanner.o: scanner.c scanner.h
	gcc $(OPTS) -c scanner.c

node.o: node.c node.h
	gcc $(OPTS) -c node.c

queue.o: queue.c queue.h node.h
	gcc $(OPTS) -c queue.c

bst.o:	bst.c	bst.h	node.h queue.h
	gcc $(OPTS) -c bst.c

avl.o: avl.c avl.h node.h queue.h
	gcc $(OPTS) -c avl.c

test: trees
	@echo ###############################
	@echo TESTING SIMPLE BST
	@echo trees -b corpus.txt instructions.txt
	@echo ###############################
	./trees -b corpus.txt instructions.txt
	@echo ###############################
	@echo TESTING AVL TREE
	@echo trees -a corpus.txt instructions.txt
	@echo ###############################
	./trees -a corpus.txt instructions.txt
	@echo ###############################

clean:
	rm -f trees $(OBJS)
