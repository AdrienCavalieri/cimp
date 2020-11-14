SOURCES = ccp.c  erase.c  rotate.c  symmetry.c
CFLAGS = -Wall -g
OBJS = $(SOURCES:%.c=%.o)

all : libeditmove.a

libeditmove.a : $(OBJS)
			ar crUu $@ $^
			ranlib $@

%.o : %.c
		gcc -c $(CFLAGS) $<

clean:
		rm -f libeditmove.a $(OBJS)
