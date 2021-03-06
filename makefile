PROJECT=program #executable file name
CC=g++
CFLAGS= -Wall
DEBUGFLAGS= -g
RELEASEFLAGS= -O2
LIBS=-lSDL -lGL -lGLU -lSDL_image

#directories:
INCLUDE=include
SRCDIR=src
OBJDIR=obj

#needed source files
SRC=$(wildcard src/*.cpp)


OBJSR=$(patsubst src/%.cpp,obj/release/%.o,$(SRC))
OBJSD=$(patsubst src/%.cpp,obj/debug/%.o,$(SRC))

all: debug/$(PROJECT) release/$(PROJECT) 
release/$(PROJECT): $(OBJSR) 
	$(CC) $(CFLAGS) $(RELEASEFLAGS) -I $(INCLUDE) -o release/$(PROJECT) $^ $(LIBS)
debug/$(PROJECT): $(OBJSD)
	$(CC) $(CFLAGS) $(DEBUGFLAGS) -I $(INCLUDE) -o debug/$(PROJECT) $^ $(LIBS)


$(OBJSD): obj/debug/%.o : src/%.cpp
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< $(LIBS) -o $@

$(OBJSR): obj/release/%.o : src/%.cpp
	$(CC) $(CFLAGS) -I $(INCLUDE) -c $< $(LIBS) -o $@
clean:
	rm -f obj/debug/*.o obj/release/*.o debug/$(PROJECT) release/$(PROJECT)
