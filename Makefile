# define the C compiler to use
CC       = gcc
# define comipler flags
CFLAGS   = -std=c19 -Wall -fmax-errors=10 -Wextra
# define library paths in addition to /usr/lib
LFLAGS   = 
# define libraries to use
LIBS     = 
# define the object files that this project needs
OBJFILES = 
# define the name of the executable file
MAIN     = 

all: $(MAIN)

$(MAIN): %.c
	$(CC) $(CFLAGS) -o $@ $(MAIN)



encrypt : encrypt.c key.c
	gcc encrypt.c key.c -o encrypt
brute : brute.c key.c
	gcc brute.c key.c -o brute