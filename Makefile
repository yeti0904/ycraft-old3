# files
SRC   = ${wildcard src/*.cc}
DEPS  = ${wildcard headers/*}
DEPS += ${wildcard src/*.hh}
OBJ   = ${addsuffix .o,${subst src/,bin/,${basename ${SRC}}}}

APP = ./bin/ycraft

# compiler related
CXX = clang++
CXXVER = c++17
CXXFLAGS = \
	-O3 \
	-std=${CXXVER} \
	-Wall \
	-Wextra \
	-pedantic \
	-g \
	-Wno-deprecated-declarations

CXXLIBS = -lSDL2 -lSDL2_ttf -lSDL2_image

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
