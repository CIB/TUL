# C compiler
CC = gcc

# Standard flags for C++ 
CFLAGS ?= -g

# Standard preprocessor flags (common for CC and CXX) 
CPPFLAGS ?= 

# Standard linker flags 
LDFLAGS ?= -static

CPPDEPS = -MT$@ -MF`echo $@ | sed -e 's,\.o$$,.d,'` -MD -MP
MINIMAL_CFLAGS =  -I.  $(CPPFLAGS) $(CXXFLAGS)
MINIMAL_OBJECTS = error.o filesystem.o time.o

### Conditionally set variables: ###


### Targets: ###

all: libtul.a

install: 

uninstall: 

clean: 
	rm -f ./*.o
	rm -f ./*.d
	rm -f libtul.a

libtul.a: $(MINIMAL_OBJECTS)
	ar rcs $@ $(MINIMAL_OBJECTS)

error.o: ./src/error.c
	$(CC) -c -o $@ $(MINIMAL_CFLAGS) $(CPPDEPS) $<
	
filesystem.o: ./src/filesystem.c
	$(CC) -c -o $@ $(MINIMAL_CFLAGS) $(CPPDEPS) $<

time.o: ./src/time.c
	$(CC) -c -o $@ $(MINIMAL_CFLAGS) $(CPPDEPS) $<


# Dependencies tracking:
-include ./*.d
