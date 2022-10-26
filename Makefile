# files
SRC   = ${wildcard src/*.cc}
DEPS  = ${wildcard headers/*}
DEPS += ${wildcard src/*.hh}
OBJ   = ${addsuffix .o,${subst src/,bin/,${basename ${SRC}}}}

APP = ./bin/ycraft

# compiler related
ifeq (${platform}, windows)
CXX = x86_64-w64-mingw32-g++
else
CXX = clang++
endif

CCACHE = ccache

CXXVER = c++17
CXXFLAGS = \
	-std=${CXXVER} \
	-Wall \
	-Wextra \
	-pedantic \
	-Wno-deprecated-declarations -Wno-missing-field-initializers

ifeq (${releasemode}, on)
CXXFLAGS += -O3 -s
else
CXXFLAGS += -O0 -g
endif

ifeq (${platform}, windows)
	CXXFLAGS += -I./sdl2/x86_64-w64-mingw32/include/ -Dmain=SDL_main \
				-I./curl/include/curl
else
	CXXFLAGS += -I/usr/include/curl
endif

ifeq (${debug}, on)
	CXXFLAGS += -DDEBUG_EXCEPTION
endif

ifeq (${platform}, windows)
	CXXLIBS += -L./sdl2/x86_64-w64-mingw32/lib -mwindows \
				-L./sdl2image/x86_64-w64-mingw32/lib \
				-L./sdl2ttf/x86_64-w64-mingw32/lib \
				-L./curl/lib -lmingw32 -static-libgcc -static-libstdc++
endif

ifeq (${triangles}, off)
	CXXFLAGS += -DDISABLE_TRIANGLES
endif

CXXLIBS += -lSDL2main -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer -lm -lcurl

# rules
compile: ./bin ${OBJ} ${SRC}
	${CCACHE} ${CXX} -o ${APP} ${OBJ} ${CXXLIBS}

./bin:
	mkdir -p bin

bin/%.o: src/%.cc ${DEPS}
	${CCACHE} ${CXX} -c $< ${CXXFLAGS} -o $@

clean:
	rm bin/*.o $(APP)

all:
	@echo compile
	@echo clean
