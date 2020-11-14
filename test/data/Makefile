CC = gcc
CFLAGS = -Wall -g
LDLIBS = -lm -lSDL2 -lSDL2_image $(shell pkg-config --libs check)
DEPEND = ../../src/data/picture.o ../../src/data/color.o ../../src/data/selection.o ../../src/utils/printer.o

all:
		make -C ../../src/data
		make testPicture
		make testColor
		make testSelection

testColor: testColor.c $(DEPEND)
		$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

testPicture: testPicture.c $(DEPEND)
		$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

testSelection: testSelection.c $(DEPEND)
		$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)
clean:
		rm −f testPicture testColor testSelection *.o
