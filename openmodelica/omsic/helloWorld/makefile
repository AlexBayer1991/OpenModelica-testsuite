
CC=gcc
CFLAGS= -Wall -Wextra -ansi -pedantic -g
CXX=g++
LD=$(CC) -shared

RUNTIMEPATH=./$(MODELNAME).fmutmp/binaries/win64/$(MODELNAME).a

MODELNAME =helloWorld

CFILES= test.c
OFILES=$(CFILES:.c=.o)

INCLUDES = -I$(MODELNAME).fmutmp/sources/include \
 -I$(MODELNAME).fmutmp/sources/include/base \
 -I$(MODELNAME).fmutmp/sources/include/solver
FMILIB = helloWorld.a


.PHONY: clean

all: omc compile
	./$(MODELNAME)_test.exe
	
omc:
	omc $(MODELNAME).mos

compile: $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -Wl,-rpath=$(RUNTIMEPATH) $(FMILIB) -o test

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

clean:
	rm -f $(MODELNAME)_*.* modelDescription.xml $(MODELNAME).libs *.dll *.a *.exe $(MODELNAME) *.o
	rm -R -f $(MODELNAME).fmutmp