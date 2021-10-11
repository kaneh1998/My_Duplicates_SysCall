# A Makefile to build the project
# run with make -f Makefile

PROJECT = duplicates
HEADERS = $(PROJECT).h
OBJ = duplicates.o empty1.o findthings.o strSHA2.o

C11 = cc -std=c11
CFLAGS = -Wall -Werror

$(PROJECT) : $(OBJ)
	$(C11) $(CFLAGS) -pedantic -o $(PROJECT) $(OBJ)
	
%.o : %.c $(HEADERS)
	$(C11) $(CFLAGS) -c $<

clean:
	rm -f $(PROJECT) $(OBJ)