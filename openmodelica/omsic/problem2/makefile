

CC=gcc
CFLAGS= -Wall -Wextra -ansi -pedantic -g
#CFLAGS = -falign-functions -msse2 -mfpmath=sse ${MODELICAUSERCFLAGS} 
CXX=g++
LD=$(CC) -shared
# LDFLAGS=@LDFLAGS@ @LIBS@

OPENMODELICAHOME = /d/workspace/OpenModelica/build

RUNTIMEPATH=$(OPENMODELICAHOME)/lib/omc/omsi

#RUNTIMELIBS = -lOMSIBase -lOMSU -lOMSISolver
RUNTIMELIBS = -lOMSISolver -lOMSU_static -lOMSIBase_static
#RUNTIMELIBSDIR = -L$(OPENMODELICAHOME)/lib/omc/omsi
RUNTIMELIBSDIR = -L.
RUNTIMEINCLUDES = -I$(OPENMODELICAHOME)/include/omc/omsi -I$(OPENMODELICAHOME)/include/omc/omsi/solver \
 -I$(OPENMODELICAHOME)/include/omc/omsi/base \
 -I$(OPENMODELICAHOME)/include/omc/omsi/fmi2 -I$(OPENMODELICAHOME)/include/omc/omsic/

EXPADLIB = -lexpat
EXPATLIBDIR = -L$(OPENMODELICAHOME)/../OMCompiler/3rdParty/FMIL/build/ExpatEx/



MAINFILE=solve_loop_test.c
# INIT_FILES=problem2_init_equations.c \
#  \
# 
SIM_FILES=problem2_omsic.c\
 problem2_sim_equations.c \
 problem2_sim_algSyst_0.c \
 problem2_sim_derMat_0.c
CFILES= $(MAINFILE) $(INIT_FILES) $(SIM_FILES)
OFILES=$(CFILES:.c=.o)
GENERATEDFILES=$(MAINFILE) problem2_FMU.makefile # ...


INCLUDES = $(RUNTIMEINCLUDES) -I.
LIBS = $(RUNTIMELIBS) $(EXPADLIB)
LIBSDIR = $(RUNTIMELIBSDIR) $(EXPATLIBDIR)

.PHONY: clean OMSIC copyLibs

all:
	omc problem2.mos

compile: $(OFILES) copyLibs OMSIC
	$(CC) $(CFLAGS) $(OFILES) -Wl,-rpath=$(RUNTIMEPATH) $(LIBSDIR) $(LIBS) -o problem2_test

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

OMSIC:
	make -C $(OPENMODELICAHOME)/../OMCompiler -f Makefile.omdev.mingw OMSI OMBUILDDIR=$(OPENMODELICAHOME) -j

copyLibs:
	cp -f $(OPENMODELICAHOME)/lib/omc/omsi/*_static.a .
	cp -f $(OPENMODELICAHOME)/lib/omc/omsi/libOMSISolver.dll .


test: OMSIC copyLibs compile
	./problem2_test.exe


clean:
	rm -f problem2_*.* modelDescription.xml problem2.libs *.dll *.a *.exe problem2 *.o
