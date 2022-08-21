
all : hello lint
hello : hello.c
	cc -g -Wall -Wextra hello.c -o hello -pthread
.PHONY: lint
lint :
	cpplint --filter=-readability/casting hello.c 
.PHONY: clean
clean :
	rm -f hello
