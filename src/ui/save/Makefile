SOURCES = load.c save.c unload.c
CFLAGS = -Wall -g
OBJS = $(SOURCES:%.c=%.o)

all : libsave.a

libsave.a : $(OBJS)
			ar crUu $@ $^
			ranlib $@

%.o : %.c
		gcc -c $(CFLAGS) $<

%.o : %.h

clean:
		rm -f libsave.a $(OBJS)
