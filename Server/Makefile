########################################################################
####################### Makefile Template ##############################
########################################################################

# I used a makefile template but it didn't work as expected so I heavily modified it.

# Compiler settings - Can be customized.
CC = g++
CXXFLAGS = -std=c++11 -Wall -g -I.
CXXFLAGSRELEASE = -std=c++11 -Wall -Os -I.
LDFLAGS =

# Makefile settings - Can be customized.
APPNAME = Golf-Server-Debug
APPNAMER = Golf-Server-Release
EXT = .cpp
SRCDIR = src
OBJDIR = obj
OBJDIRDEBUG = obj/debug
OBJDIRRELEASE = obj/release
BINDIR = bin

############## Do not change anything from here downwards! #############
# Recursive wildcar to search in all subdirectories no matter the depth.
# Source: https://stackoverflow.com/questions/4036191/sources-from-subdirectories-in-makefile
rwildcard=$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

# Look at all the subdirectories in the src directory and compile them.
SRC := $(call rwildcard,$(SRCDIR)/,*$(EXT))
OBJD = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIRDEBUG)/%.o)
OBJR = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIRRELEASE)/%.o)
# UNIX-based OS variables & settings
RM = rm -rf
########################################################################
####################### Targets beginning here #########################
########################################################################

.PHONY: debug
debug: $(APPNAME)

# Builds the app
$(APPNAME): $(OBJD) 
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	mkdir -p $(BINDIR)
	mv $(APPNAME) $(BINDIR)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIRDEBUG)/%.o: $(SRCDIR)/%$(EXT)
	mkdir -p $(@D)
	$(CC) $(CXXFLAGS) -o $@ -c $<

.PHONY: release
release: $(APPNAMER)

# Builds the app
$(APPNAMER): $(OBJR) 
	$(CC) $(CXXFLAGSRELEASE) -o $@ $^ $(LDFLAGS)
	mkdir -p $(BINDIR)
	mv $(APPNAMER) $(BINDIR)

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIRRELEASE)/%.o: $(SRCDIR)/%$(EXT)
	mkdir -p $(@D)
	$(CC) $(CXXFLAGSRELEASE) -o $@ -c $<

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project and also deletes objdir even if its not empty
.PHONY: clean
clean:
	$(RM) $(OBJDIR) $(BINDIR) $(APPNAME)
	