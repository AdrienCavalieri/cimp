SOURCES = brightness.c  bwconversion.c  contrast.c  fill.c  grayscale.c  negate.c replaceColor.c
CFLAGS = -Wall -g
OBJS = $(SOURCES:%.c=%.o)

all : libeditcolor.a

libeditcolor.a : $(OBJS)
			ar crUu $@ $^
			ranlib $@

%.o : %.c
		gcc -c $(CFLAGS) $<

clean:
		rm -f libeditcolor.a $(OBJS)
