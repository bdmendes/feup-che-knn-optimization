# This Makefile is used to build the project,
# automatically copying the data/parameters files
# according to the chosen scenario.

# Abort if more than one target is specified.
ifneq ($(words $(MAKECMDGOALS)),1)
$(error Please choose one and only one scenario to run.)
endif

# Compiler flags. Use COPT to set optimization flags.
ifndef COPT
$(warning COPT is not set. Using default COPT=-O0.)
COPT = -O0
endif
CXX = gcc #/opt/intel/oneapi/compiler/latest/bin/icx
CGFLAGS = -Wall -std=gnu99 -lm -fopenmp -pg -fno-builtin -Wno-unused-parameter
CFLAGS = $(CGFLAGS) $(COPT)

# Project files.
SRCDIR = src
SRCFILES = $(wildcard $(SRCDIR)/*.c)
space := $(subst ,, )
PROG = knn_$(MAKECMDGOALS)_$(subst $(space),_,$(COPT)).out

.PHONY: testing a1a a1b a2 a3 clean gprof

ifndef DT
$(warning DT is not set. Using default DT=1 (double).)
DT = 1
endif

a1a:
	cp data/scenario-wisdm/* $(SRCDIR)
	$(CXX) -D VERIFY=1 -D K=3 -D DT=$(DT) $(CFLAGS) $(SRCFILES) -o $(PROG)

a1b:
	cp data/scenario-wisdm/* $(SRCDIR)
	$(CXX) -D VERIFY=1 -D K=20 -D DT=$(DT) $(CFLAGS) $(SRCFILES) -o $(PROG)

a2:
	cp data/scenario-gen100x8x10000/* $(SRCDIR)
	$(CXX) -D K=20 -D DT=$(DT) -D NUM_TRAINING_SAMPLES=8004 -D NUM_TESTING_SAMPLES=1996 -D NUM_FEATURES=100 -D NUM_CLASSES=8 $(CFLAGS) $(SRCFILES) -o $(PROG)

a3:
	cp -r data/scenario-gen100x8x50000/* $(SRCDIR)
	$(CXX) -D K=20 -D DT=$(DT) -D NUM_TRAINING_SAMPLES=40002 -D NUM_TESTING_SAMPLES=9998 -D NUM_FEATURES=100 -D NUM_CLASSES=8 $(CFLAGS) $(SRCFILES) -o $(PROG)

gprof:
ifndef FILE
	$(error FILE is not set. Please specify the executable to run.)
endif
	./$(FILE)
	gprof $(FILE) gmon.out > analysis-$(FILE).txt
	rm gmon.out

clean:
	rm *.out *.txt $(SRCDIR)/*.dat $(SRCDIR)/params.h