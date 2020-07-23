CC = g++
CLIBS = -lwsock32 -lmingw32 -lSDL2main -lSDL2 -lkernel32 -ladvapi32 -lgdi32 -limm32 -lmsvcrt -lole32 -loleaut32 -lsetupapi -lshell32 -luser32 -lversion -lwinmm -lSDL2_image
INCLUDES = -Iinclude -IC:/CppLibraries/include/SDL2 -I../lib
LIBPATH = -LC:/CppLibraries/lib
OUTPUT = test
DEBUGOUTPUTDIR = bin/debug
RELEASEOUTPUTDIR = bin/release
OBJDIR = bin/objects
SRCDIR = src
CPPVERSION = c++17

#SOURCES = $(wildcard **/*.cpp)
SOURCES = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/*/*.cpp)
POBJECTS = $(SOURCES:$(SRCDIR)/%.cpp=%.o)
OBJECTS = $(addprefix $(OBJDIR)/, $(POBJECTS))

$(OUTPUT): $(OBJECTS)
	@mkdir -p bin/debug
	$(CC) $(OBJECTS) $(INCLUDES) $(LIBPATH) -Wl,-Bstatic $(CLIBS) -std=$(CPPVERSION) -static -g -o $(DEBUGOUTPUTDIR)/$(OUTPUT)
	@echo "\n"Debug build completed\; Enter $(DEBUGOUTPUTDIR)/$(OUTPUT) to run."\n"

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(INCLUDES) $(LIBPATH) -Wl,-Bstatic $(CLIBS) -std=$(CPPVERSION) -static -c -g $< -o $@

clean:
	rm -r $(OBJDIR)/* $(DEBUGOUTPUTDIR)/$(OUTPUT) #$(RELEASEOUTPUTDIR)/$(OUTPUT)

#release: $(OBJECTS)
#	$(CC) $(OBJECTS) $(CLIBS) -O3 -o $(RELEASEOUTPUTDIR)/$(OUTPUT)
#	@echo "\n"Release build completed\; Enter $(RELEASEOUTPUTDIR)/$(OUTPUT) to run."\n"
