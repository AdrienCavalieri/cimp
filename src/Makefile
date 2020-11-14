CC = gcc
CFLAGS = -Wall -g
LDLIBS = -lm -lSDL2 -lSDL2_image -lreadline -lturbojpeg
LDIR = -Lui -Lui/save -Lediting/color -Lediting/move -Lediting/size -Ldata -Lutils
MYLIBS = -lui -lsave -leditcolor -leditmove -leditsize -ldata -lutils

all:
		make -C utils
		make -C data
		make -C editing
		make -C ui
		make cimp

cimp : cimp.c */*.a */*/*.a
		$(CC) -o $@ cimp.c $(LDIR) $(MYLIBS) $(LDLIBS)

clean :
		make -C utils clean
		make -C data clean
		make -C editing clean
		make -C ui clean
		rm -f  cimp *.o
