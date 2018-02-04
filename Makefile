# Makefile with suffix rules

CC	= gcc
CFLAGS	= -g
TARGET 	= proc_fan
OBJS 	= proc_fan.o
LIBOBJS =
LIBS =
MYLIBS =

.SUFFIXES: .c .o

$(TARGER): $(OBS)
	$(CC) -o $@ $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	/bin/rm -f *.o *~ $(TARGET)

