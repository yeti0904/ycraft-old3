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
CXXVER = c++17
CXXFLAGS = \
	-std=${CXXVER} \
	-Wall \
	-Wextra \
	-pedantic \
	-Wno-deprecated-declarations

ifeq (${releasemode}, on)
CXXFLAGS += -O3 -s
else
CXXFLAGS += -g
endif

ifeq (${platform}, windows)
CXXFLAGS += \
	-I./sdl2/x86_64-w64-mingw32/include -Dmain=SDL_main \
	-L./sdl2/x86_64-w64-mingw32/lib -lmingw32 \
	-lSDL2main ./sdl2/x86_64-w64-mingw32/lib/libSDL2.a \
	-mwindows -Wl,--dynamicbase -Wl,--nxcompat -Wl,--high-entropy-va -lm -ldinput8 \
	-ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 \
	-lsetupapi -lversion -luuid \
	-I./sdl2ttf/x86_64-w64-mingw32/include -L./sdl2ttf/x86_64-w64-mingw32/lib \
	-lSDL2_ttf \
	-I./sdl2image/x86_64-w64-mingw32/include -L./sdl2image/x86_64-w64-mingw32/lib \
	-lSDL2_image
else
CXXFLAGS += -I/usr/include/SDL2
endif

ifeq (${debug}, on)
CXXFLAGS += -DDEBUG_EXCEPTION
endif

CXXLIBS = -lSDL2 -lSDL2_ttf -lSDL2_image -lm -lcurl

# rules
compile: ./bin ${OBJ} ${SRC}
	${CXX} -o ${APP} ${OBJ} ${CXXLIBS}

./bin:
	mkdir -p bin

bin/%.o: src/%.cc ${DEPS}
	${CXX} -c $< ${CXXFLAGS} -o $@

clean:
	rm bin/*.o $(APP)

all:
	@echo compile
	@echo clean
