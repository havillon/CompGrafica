# Define the link target.
linkTarget = cg

# Define libraries that we need,
LIBS = -lSDL2

# Define flags.
# CFLAGS = -std=c++17 -pg
CFLAGS = -std=c++17

# Define the object files that we need to use.
objects = main.o \
	setup.o \
	$(patsubst %.cpp,%.o,$(wildcard ./src/*.cpp)) \
  $(patsubst %.cpp,%.o,$(wildcard ./src/algebraLinear/*.cpp)) \
  $(patsubst %.cpp,%.o,$(wildcard ./src/cenario/*.cpp)) \
  $(patsubst %.cpp,%.o,$(wildcard ./src/objeto/*.cpp))
					
# Define the rebuildables.
rebuildables = $(objects) $(linkTarget)

# Rule to actually perform the build.
$(linkTarget): $(objects)
	g++ -g -o $(linkTarget) $(objects) $(LIBS) $(CFLAGS)
	
# Rule to create the .o files.
%.o: %.cpp
	g++ -o $@ -c $< $(CFLAGS)