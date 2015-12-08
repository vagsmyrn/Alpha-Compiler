# build tools
CC=gcc
FLEX=flex
BISON=bison
# gcc options
OFLAGS=-Wall -g 

# remove
RM=rm -fr

all:	vm_print.o vm.o execute.o vm_lib_funcs.o
	$(CC) $(OFLAGS) -o vm vm.o vm_print.o execute.o vm_lib_funcs.o

vm_print.o: vm_print.c
	$(CC) $(OFLAGS) -c vm_print.c

execute.o: execute.c
	$(CC) $(OFLAGS) -c execute.c

vm.o: vm.c
	$(CC) $(OFLAGS) -c vm.c

vm_lib_funcs.o: vm_lib_funcs.c
	$(CC) $(OFLAGS) -c vm_lib_funcs.c
	
clean:
	$(RM) *.o vm

