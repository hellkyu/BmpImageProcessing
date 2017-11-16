CC = gcc
CFLAGS = -g -Wall
INCDIR = ../inc
LIBDIR = ../lib
OUTPUT = imgprc 
.PHONY: clean

$(OUTPUT): main.o $(LIBDIR)/libbmpfuncs.a
	$(CC) $(CFLAGS) -o $@ $< -L$(LIBDIR) -lbmpfuncs -lm

main.o: main.c
	$(CC)  $(CFLAGS) -c $< -o $@ -I$(INCDIR)

clean: 
	rm *.o $(OUTPUT)
