CC = gcc
CFLAGS = -g -Wall
INCOPT = -I../inc
OUTPUT = libbmpfuncs.a
OBJFILES = resolution.o init.o esw_process1.o \
            esw_bmp.o rgb2gray.o bit_plane.o
.PHONY: clean

$(OUTPUT): $(OBJFILES)
	ar rv $(OUTPUT) $(OBJFILES)

%.o: %.c
	$(CC) $(CFLAGS) $(INCOPT) -c $< -o $@

clean:
	rm *.o $(OUTPUT)
