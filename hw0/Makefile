CC = gcc
CFLAGS = -g

RM = /bin/rm -f 

##################################
# MAKE ALL
##################################
all: wc map main

# Make wc
wc: wc.o
	$(CC) $(CFLAGS) -o wc wc.o
wc.o: wc.c
	$(CC) $(CFLAGS) -c wc.c -o wc.o

# Make map
map: map.o
	$(CC) $(CFLAGS) -o map map.o
map.o: map.c
	$(CC) $(CFLAGS) -c map.c -o map.o

# Make main
main: main.o
	$(CC) $(CFLAGS) -o main main.o
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o


##################################
# Clean up files
##################################
clean: wcClean mapClean mainClean

wcClean:
	$(RM) wc.o wc

mapClean:
	$(RM) map.o map

mainClean:
	$(RM) main.o main
 

