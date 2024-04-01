# Makefile for building embedded application.
# by Brian Fraser

# Edit this file to compile extra C files into their own programs.
TARGETS = neoPixelRGBW-main


PUBDIR = $(HOME)/cmpt433/public/myApps

OUTDIR = $(PUBDIR)
CROSS_TOOL = arm-linux-gnueabihf-
CC_CPP = $(CROSS_TOOL)g++
CC_C = $(CROSS_TOOL)gcc

CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror -Wshadow
# -pg for supporting gprof profiling.
# CFLAGS += -pg


# Convert the targets to full-path executables to delete.
OUTPUTS= $(addprefix $(OUTDIR)/, $(TARGETS))

# all: $(TARGETS) PrimeThread
all: $(TARGETS)

$(TARGETS): neoPixelRGBW-Linux.o
	$(CC) $(CFLAGS) $@.c neoPixelRGBW-Linux.o -o $(OUTDIR)/$@ $(LDFLAGS)

# Build the shared object file for neoPixelRGBW-Linux.c
neoPixelRGBW-Linux.o: neoPixelRGBW-Linux.c neoPixelRGBW-Linux.h
	$(CC) $(CFLAGS) -c neoPixelRGBW-Linux.c -o neoPixelRGBW-Linux.o


$(TARGETS):
	$(CC_C) $(CFLAGS) $@.c -o $(OUTDIR)/$@ -lpthread

PrimeThread:
	make --directory=primeThread

clean:
	rm -f $(OUTPUTS)
