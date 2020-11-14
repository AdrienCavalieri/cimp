SOURCES = picture.c color.c selection.c
OBJS = $(SOURCES:%.c=%.o)
CFLAGS = -Wall -g

all : libdata.a

libdata.a : $(OBJS)
			ar crUu $@ $^
			ranlib $@

%.o : %.c
		gcc -c $(CFLAGS) $<

clean:
		rm -f libdata.a $(OBJS)
