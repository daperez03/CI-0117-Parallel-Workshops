APPNAME=hello

all : $(APPNAME) lint memcheck helgrind
$(APPNAME) : $(APPNAME).c
	cc -g -Wall -Wextra $(APPNAME).c -o $(APPNAME) -pthread

.PHONY: lint
lint :
	cpplint --filter=-readability/casting $(APPNAME).c 

.PHONY: memcheck
memcheck :
	valgrind --quiet --tool=memcheck ./$(APPNAME)

.PHONY: helgrind 
helgrind :
	valgrind --quiet --tool=helgrind ./$(APPNAME)

.PHONY: clean
clean :
	rm -f $(APPNAME)
