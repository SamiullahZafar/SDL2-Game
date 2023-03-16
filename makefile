PROG = pp06
CC = gcc

OUT = build

SEARCHPATH += src
vpath %.c $(SEARCHPATH)
vpath %.h $(SEARCHPATH)

DEPS += common.h structs.h

_OBJS += block.o
_OBJS += camera.o
_OBJS += draw.o
_OBJS += entities.o
_OBJS += init.o input.o io.o
_OBJS += main.o map.o
_OBJS += pizza.o player.o platform.o
_OBJS += sound.o stage.o
_OBJS += textures.o text.o
_OBJS += util.o

OBJS = $(patsubst %,$(OUT)/%,$(_OBJS))

# top-level rule to create the program.
all: $(PROG)

# compiling other source files.
$(OUT)/%.o: %.c $(DEPS)
	@mkdir -p $(OUT)
	$(CC) $(CFLAGS) $(CXXFLAGS) -c -o $@ $<

# cleaning everything that can be automatically recreated with "make".
clean:
	$(RM) -rf $(OUT) $(PROG)

#CXXFLAGS += `./install/bin/sdl2-config --cflags`
CXXFLAGS += `sdl2-config --cflags`
CXXFLAGS += -Wall -Wempty-body -Werror -Wstrict-prototypes -Werror=maybe-uninitialized -Warray-bounds
CXXFLAGS += -g -lefence -I./src

#LDFLAGS += `./install/bin/sdl2-config --libs` -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lm
# use for local installation
LDFLAGS += `sdl2-config --libs` -lSDL2_mixer -lSDL2_image -lSDL2_ttf -lm


# linking the program.
$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

all:
	g++ -I src/include -L src/lib io main main.cpp -lmingw32 -lsdl2main -lSDL2