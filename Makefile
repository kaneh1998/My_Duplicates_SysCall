# A Makefile to build the project
# run with make -f Makefile
# Changing from -c to -pedantic fucks it up atm
# Changing from -o to -pedantic fucks it up too

PROJECT = duplicates
HEADERS = $(PROJECT).h
OBJ = duplicates.o empty1.o empty2.o strSHA2.o

C11 = cc -std=c11
CFLAGS = -Wall -Werror

$(PROJECT) : $(OBJ)
	$(C11) $(CFLAGS) -o $(PROJECT) $(OBJ)
	
%.o : %.c $(HEADERS)
	$(C11) $(CFLAGS) -c $<

clean:
	rm -f $(PROJECT) $(OBJ)