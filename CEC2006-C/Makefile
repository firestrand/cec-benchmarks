# Makefile for CEC2006 Constrained Optimization Benchmark
#
# This builds a standalone executable for testing CEC2006 functions
#

CC = gcc
CFLAGS = -Wall -O2 -g
LDFLAGS = -lm

# Object files
OBJS = main.o fcnsuite.o

# Target executable
TARGET = main

# Default target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compile main.c
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

# Compile fcnsuite.c (remove DLLIMPORT for standalone)
fcnsuite.o: fcnsuite.c
	$(CC) $(CFLAGS) -DDLLIMPORT= -c fcnsuite.c

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET) core *.out

# Test with a simple example
test: $(TARGET)
	@echo "Testing G01 with zeros input..."
	@for i in `seq 1 13`; do echo "0.0" >> test_input.txt; done
	./$(TARGET) 1 -1 test_input.txt
	@rm -f test_input.txt

.PHONY: all clean test