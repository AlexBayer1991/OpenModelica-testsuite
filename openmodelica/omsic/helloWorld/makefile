

CC=gcc
CFLAGS= -Wall -Wextra -ansi -pedantic -g
#CFLAGS = -falign-functions -msse2 -mfpmath=sse ${MODELICAUSERCFLAGS} 
CXX=g++
LD=$(CC) -shared
# LDFLAGS=@LDFLAGS@ @LIBS@

OPENMODELICAHOME = /d/workspace/OpenModelica/build

RUNTIMEPATH=$(OPENMODELICAHOME)/lib/omc/omsi

RUNTIMELIBS = -lOMSISolver -lOMSU_static -lOMSIBase_static
RUNTIMELIBSDIR = -L.
RUNTIMEINCLUDES = -I$(OPENMODELICAHOME)/include/omc/omsi -I$(OPENMODELICAHOME)/include/omc/omsi/solver \
 -I$(OPENMODELICAHOME)/include/omc/omsi/base \
 -I$(OPENMODELICAHOME)/include/omc/omsi/fmi2 -I$(OPENMODELICAHOME)/include/omc/omsic/

EXPADLIB = -lexpat
EXPATLIBDIR = -L$(OPENMODELICAHOME)/../OMCompiler/3rdParty/FMIL/build/ExpatEx/

MODELNAME =helloWorld

MAINFILE=test.c
# INIT_FILES=problem2_init_equations.c \
#  \
# 
SIM_FILES=$(MODELNAME)_omsic.c\
 $(MODELNAME)_sim_equations.c
CFILES= $(MAINFILE) $(INIT_FILES) $(SIM_FILES)
OFILES=$(CFILES:.c=.o)
GENERATEDFILES=$(MAINFILE) $(MODELNAME)_FMU.makefile # ...


INCLUDES = $(RUNTIMEINCLUDES) -I.
LIBS = $(RUNTIMELIBS) $(EXPADLIB)
LIBSDIR = $(RUNTIMELIBSDIR) $(EXPATLIBDIR)

.PHONY: clean

all:
	omc $(MODELNAME).mos

compile: $(OFILES) copyLibs OMSIC
	$(CC) $(CFLAGS) $(OFILES) -Wl,-rpath=$(RUNTIMEPATH) $(LIBSDIR) $(LIBS) -o $(MODELNAME)_test

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

OMSIC:
	make -C $(OPENMODELICAHOME)/../OMCompiler -f Makefile.omdev.mingw OMSI OMBUILDDIR=$(OPENMODELICAHOME) -j

copyLibs:
	cp -f $(OPENMODELICAHOME)/lib/omc/omsi/*_static.a .
	cp -f $(OPENMODELICAHOME)/lib/omc/omsi/libOMSISolver.dll .


test: OMSIC copyLibs compile
	./$(MODELNAME)_test.exe


clean:
	rm -f $(MODELNAME)_*.* modelDescription.xml $(MODELNAME).libs *.dll *.a *.exe $(MODELNAME) *.o
