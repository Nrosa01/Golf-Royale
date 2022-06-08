########################################################################
####################### Makefile Template ##############################
########################################################################

# I used a makefile template but it didn't work as expected so I heavily modified it.

# Compiler settings - Can be customized.
ifeq ($(os),windows)
APPNAME := Golf-Royale-Debug.exe
APPNAMER := Golf-Royale-Release.exe
CC := x86_64-w64-mingw32-g++
CXXFLAGS := -std=c++11 -Wall -g -I/usr/local/win64/x86_64-w64-mingw32/include
CXXFLAGSRELEASE := -std=c++11 -Wall -Os -I/usr/local/win64/x86_64-w64-mingw32/include
LDFLAGS := 
LIBS := `/usr/local/win64/x86_64-w64-mingw32/bin/sdl2-config --libs`
DLLDIR := /usr/local/win64/x86_64-w64-mingw32/bin/
# These two are for static linking, good luck making that work lol
# LDFLAGS := -static -static-libgcc
# LIBS := `/usr/local/win64/x86_64-w64-mingw32/bin/sdl2-config --static-libs`
OBJDIRDEBUG := obj/windows/debug
OBJDIRRELEASE := obj/windows/release
BINDIR := bin/windows
else
os := linux
APPNAME := Golf-Royale-Debug
APPNAMER := Golf-Royale-Release
CC := g++
CXXFLAGS := -std=c++11 -Wall -g
CXXFLAGSRELEASE := -std=c++11 -Wall -Os
LDFLAGS := -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lpthread
LIBS := 
OBJDIRDEBUG = obj/linux/debug
OBJDIRRELEASE = obj/linux/release
BINDIR := bin/linux
endif

# Makefile settings - Can be customized.
EXT = .cpp
SRCDIR = src
OBJDIR = obj

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
	$(info Compiling for $(os)...)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)
	mkdir -p $(BINDIR)
	mv $(APPNAME) $(BINDIR)
ifeq ($(os),windows)
		cp $(DLLDIR)/*.dll $(BINDIR)
endif

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIRDEBUG)/%.o: $(SRCDIR)/%$(EXT)
	mkdir -p $(@D)
	$(CC) $(CXXFLAGS) -o $@ -c $<

.PHONY: release
release: $(APPNAMER)

# Builds the app
$(APPNAMER): $(OBJR) 
	$(info$(os))
	$(CC) $(CXXFLAGSRELEASE) -o $@ $^ $(LDFLAGS) $(LIBS)
	mkdir -p $(BINDIR)
	mv $(APPNAMER) $(BINDIR)
ifeq ($(os),windows)
		cp $(DLLDIR)/*.dll $(BINDIR)
endif

# Building rule for .o files and its .c/.cpp in combination with all .h
$(OBJDIRRELEASE)/%.o: $(SRCDIR)/%$(EXT)
	mkdir -p $(@D)
	$(CC) $(CXXFLAGSRELEASE) -o $@ -c $<

################### Cleaning rules for Unix-based OS ###################
# Cleans complete project and also deletes objdir even if its not empty
.PHONY: clean
clean:
	$(RM) $(OBJDIR) $(BINDIR) $(APPNAME)
	