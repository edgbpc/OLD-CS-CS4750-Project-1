# Makefile with suffix rules

CC	= gcc
CFLAGS	= -g
TARGET1 = proc_fan
TARGET2 = testsim
OBJS1 	= proc_fan.o makeargv.o 
OBJS2 	= testsim.o
LIBOBJS =
LIBS =
MYLIBS =


.SUFFIXES: .c .o


all: $(TARGET1) $(TARGET2)

proc_fan: $(OBJS1)
	$(CC) $(CFLAGS) $(OBJS1) -o $@

testsim: $(OBJS2)
	$(CC) $(CFLAGS) $(OBJS2) -o $@


.c.o:
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	/bin/rm -f *.o *~ $(TARGET)

