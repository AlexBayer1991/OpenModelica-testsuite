

CC=gcc
CFLAGS= -Wall -Wextra -ansi -pedantic
#CFLAGS = -falign-functions -msse2 -mfpmath=sse ${MODELICAUSERCFLAGS} 
CXX=g++
LD=$(CC) -shared
# LDFLAGS=@LDFLAGS@ @LIBS@

OPENMODELICAHOME = /d/workspace/OpenModelica/build

RUNTIMEPATH=.

RUNTIMELIBS = -lOMSIBase -lOMSU -lOMSISolver
RUNTIMELIBSDIR = -L$(OPENMODELICAHOME)/lib/omc/omsi
RUNTIMEINCLUDES = -I$(OPENMODELICAHOME)/include/omc/omsi -I$(OPENMODELICAHOME)/include/omc/omsi/solver \
 -I$(OPENMODELICAHOME)/include/omc/omsi/base \
 -I$(OPENMODELICAHOME)/include/omc/omsi/fmi2 -I$(OPENMODELICAHOME)/include/omc/omsic/

MAINFILE=solve_loop_test.c
# INIT_FILES=problem2_init_equations.c \
#  \
# 
SIM_FILES=problem2_sim_equations.c \
 problem2_sim_algSyst_0.c \
 problem2_sim_derMat_0.c
CFILES= $(MAINFILE) $(INIT_FILES) $(SIM_FILES)
OFILES=$(CFILES:.c=.o)
GENERATEDFILES=$(MAINFILE) problem2_FMU.makefile # ...


INCLUDES = $(RUNTIMEINCLUDES) -I.
LIBS = $(RUNTIMELIBS) -Lexpad
LIBSDIR = $(RUNTIMELIBSDIR)

.PHONY: installOMSILibs clean

all:
	omc problem2.mos

compile: $(OFILES)
	$(CC) $(CFLAGS) $(OFILES) -Wl,-rpath=$(RUNTIMEPATH) $(LIBSDIR) $(LIBS) -o problem2_test

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

installOMSILibs:
	make -C $(OPENMODELICAHOME)/../OMCompiler/SimulationRuntime/OMSI/ -f Makefile.omdev.mingw install -j
	make -C $(OPENMODELICAHOME)/../OMCompiler/SimulationRuntime/OMSIC/ -f Makefile.omdev.mingw install -j
	cp -f $(OPENMODELICAHOME)/lib/omc/omsi/*.dll .

test: installOMSILibs compile
	./problem2_test.exe

fast_test: compile
	./problem2_test.exe

clean:
	rm -f problem2_*.* modelDescription.xml problem2.libs *.dll problem2.exe problem2
