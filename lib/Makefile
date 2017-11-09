CC = gcc
CFLAGS = -g -Wall
INCOPT = -I../inc
OUTPUT = libbmpfuncs.a
OBJFILES = esw_bmp.o rgb2gray.o
.PHONY: clean

$(OUTPUT): $(OBJFILES)
	ar rv $(OUTPUT) $(OBJFILES)

%.o: %.c
	$(CC) $(CFLAGS) $(INCOPT) -c $< -o $@

clean:
	rm *.o $(OUTPUT)
