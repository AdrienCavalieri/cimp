SOURCES = commandReader.c window.c show.c select.c userReader.c
CFLAGS = -Wall -g
OBJS = $(SOURCES:%.c=%.o)

all :
		make -C save
		make libui.a

libui.a : $(OBJS)
			ar crUu $@ $^
			ranlib $@

%.o : %.c
		gcc -c $(CFLAGS) $<

%.o : %.h

clean:
		make -C save clean
		rm -f libui.a $(OBJS)
