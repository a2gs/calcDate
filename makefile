CC = cc
AR = ar
RANLIB = ranlib

SRCDIR = ./src
INCDIR = ./inc
BINDIR = ./bin

CFLAGS_OPTIMIZATION = -g
#CFLAGS_OPTIMIZATION = -O3
CFLAGS_VERSION = -std=c11
CFLAGS_WARNINGS = -Wall -Wextra
CFLAGS_DEFINES = -D_XOPEN_SOURCE=700 -D_POSIX_C_SOURCE=200809L -D_POSIX_SOURCE=1 -D_DEFAULT_SOURCE=1 -D_GNU_SOURCE=1
CFLAGS = $(CFLAGS_OPTIMIZATION) $(CFLAGS_VERSION) $(CFLAGS_WARNINGS) $(CFLAGS_DEFINES)

RM = rm -rf

OBJ = $(BINDIR)/liba2gs_ToolBox_AddSubDate.o
LIB = $(BINDIR)/liba2gs_ToolBox_AddSubDate.a
SOURCES = $(SRCDIR)/libAddSubDate.c

all: clean libDate

libDate: $(SOURCES)
	$(CC) -c -o$(OBJ) -I$(INCDIR) $(SOURCES) $(CFLAGS)
	$(AR) rc $(LIB) $(OBJ)
	$(RANLIB) $(LIB)

sample: clean libDate $(SRCDIR)/sample.c
	$(CC) -o $(BINDIR)/sample $(SRCDIR)/sample.c $(CFLAGS) -I$(INCDIR) -L$(BINDIR) -la2gs_ToolBox_AddSubDate

clean:
	-$(RM) $(BINDIR)/*
