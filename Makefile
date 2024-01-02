# This Makefile is used to build the project,
# automatically copying the data/parameters files
# according to the chosen scenario.

# Abort if more than one target is specified.
ifneq ($(words $(MAKECMDGOALS)),1)
$(error Please choose one and only one scenario to run.)
endif


CXX = gcc #/opt/intel/oneapi/compiler/latest/bin/icx
CGFLAGS = -Wall -std=gnu99 -lm -fopenmp -pg -fno-builtin -Wno-unused-parameter
CFLAGS = $(CGFLAGS) $(COPT)

# Project files.
SRCDIR = src
SRCFILES = $(wildcard $(SRCDIR)/*.c)
space := $(subst ,, )
ifndef PROG
PROG = knn_$(MAKECMDGOALS)_$(subst $(space),_,$(DT))_$(subst $(space),_,$(COPT))_$(subst $(space),_,$(OPTFLAGS)).out
endif
.PHONY: testing a1a a1b a2 a3 clean gprof .build .a 


.build:
ifndef COPT # Compiler flags. Use COPT to set optimization flags.
$(warning COPT is not set. Using default COPT=-O0.)
COPT = -O0
endif

ifndef DT
$(warning DT is not set. Using default DT=1 (double).)
DT = 1
endif

ifndef OPTFLAGS
$(warning OPTFLAGS is not set. No code optimizations in place.)
endif

.a: .build
	cp data/scenario-wisdm/* $(SRCDIR)
	
a1a: .a
	$(eval SCENARIO_FLAGS = -D K=3 -D VARIABLE_PARAMETERS -D VERIFY=1)
	$(CXX) -D DT=$(DT) $(CFLAGS) $(SCENARIO_FLAGS) $(OPTFLAGS) $(SRCFILES)  -o $(PROG)
	
a1b: .a
	$(eval SCENARIO_FLAGS = -D K=20 -D VARIABLE_PARAMETERS -D VERIFY=1)
	$(CXX) -D DT=$(DT) $(CFLAGS) $(SCENARIO_FLAGS) $(OPTFLAGS) $(SRCFILES) -o $(PROG)

a1c: .a
	$(eval SCENARIO_FLAGS = -D K=3 -D VERIFY=1 -D DT=2)
	$(CXX) $(CFLAGS) $(SCENARIO_FLAGS) $(OPTFLAGS) $(SRCFILES)  -o $(PROG)

a2: .build
	cp data/scenario-gen100x8x10000/* $(SRCDIR)
	$(CXX) -D DT=$(DT) $(CFLAGS) $(OPTFLAGS) $(SRCFILES) -o $(PROG)

a3: .build
	cp -r data/scenario-gen100x8x50000/* $(SRCDIR)
	$(eval READ=2)
	$(CXX) -D DT=$(DT) $(CFLAGS) $(OPTFLAGS) $(SRCFILES) -o $(PROG)

gprof:
ifndef FILE
	$(error FILE is not set. Please specify the executable to run.)
endif
	./$(FILE)
	gprof $(FILE) gmon.out > analysis-$(FILE).txt
	rm gmon.out

clean:
	rm *.out *.txt $(SRCDIR)/*.dat $(SRCDIR)/params.h