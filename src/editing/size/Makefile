SOURCES = crop.c  resize.c
CFLAGS = -Wall -g
OBJS = $(SOURCES:%.c=%.o)

all : libeditsize.a

libeditsize.a : $(OBJS)
			ar crUu $@ $^
			ranlib $@

%.o : %.c
		gcc -c $(CFLAGS) $<

clean:
		rm -f libeditsize.a $(OBJS)
