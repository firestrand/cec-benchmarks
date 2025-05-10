# Makefile for compiling test functions
# Tested on the following system:
# Compiler name and version: gcc-3.3.4
# Operating system name and version: Gentoo Linux 2004.3
# Kernel name and version: 2.6.9-gentoo-r9
# Machine architecture: i686
# Last edited on: 10 March 2005
# Author: Santosh Tiwari (tiwaris@iitk.ac.in)
# Updated for runtime function selection in 2024

CC=gcc

LD=gcc

RM=rm -f

CFLAGS=-Wall -ansi -pedantic -g

#CFLAGS=-O2 -march=pentium4 -pipe -fomit-frame-pointer
#LDFLAGS=-s

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

MAIN = main

all: $(MAIN)

$(MAIN): $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $(MAIN) -lm

%.o: %.c global.h sub.h rand.h
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) $(OBJ) $(MAIN) core.* *~ *.out

# Special target for initial compilation and testing all functions
test: all
	@echo "Testing compilation and all functions..."
	@cd .. && python utility_scripts/run_cec2005.py --all --type zeros

