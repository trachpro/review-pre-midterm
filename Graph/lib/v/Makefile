# Makefile for v-lib -- C extended libraries written by Viet Anh Nguyen
# Email: vietanh.dev@gmail.com

CFLAGS = -O

all: libv.a

OBJS = v_io.o v_string.o

libv.a: $(OBJS)
	ar -rcs libv.a $(OBJS)
	ranlib libv.a

clean:
	rm -f *.o libv.a

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c
