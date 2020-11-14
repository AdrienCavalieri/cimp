SOURCES = printer.c
CFLAGS = -Wall -g
OBJS = $(SOURCES:%.c=%.o)

all : libutils.a

libutils.a : $(OBJS)
			ar crUu $@ $^
			ranlib $@

%.o : %.c
		gcc -c $(CFLAGS) $<

%.o : %.h

clean:
		rm -f libutils.a $(OBJS)
