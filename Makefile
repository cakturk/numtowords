#############################################################################
# Makefile for building: numtowords
#############################################################################

CC            = gcc
DEFINES       =
CFLAGS        = -pipe -g -Wall -Wp,-D_FORTIFY_SOURCE=2 -mtune=generic -Wall $(DEFINES)
INCPATH       =
LINK          = gcc
LFLAGS        =
LIBS          =
AR            = ar cqs
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip --strip-unneeded
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

OBJECTS       = main.o \
		numtowords.o
TARGET        = numtowords

first: all

####### Implicit rules
.SUFFIXES: .o .c .cpp .cc .cxx .C

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"


all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

release: $(TARGET)
	$(STRIP) $(TARGET)

clean:
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core.*

main.o: main.c 
	$(CC) -c $(CFLAGS) $(INCPATH) -o main.o main.c

numtowords.o: numtowords.c 
	$(CC) -c $(CFLAGS) $(INCPATH) -o numtowords.o numtowords.c
