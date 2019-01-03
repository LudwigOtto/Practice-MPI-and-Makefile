EXECS = random_walker
MPIC++ ?= mpic++
SOURCES = ${wildcard src/*.cpp}
OBJECTS = ${patsubst %.cpp, %.o, ${SOURCES}}
HEADERS = ${PWD}/include
CPPFLAGS = -std=c++11 -I ${HEADERS}
.PHONY: all clean

all: ${EXECS}

%.o: %.cpp
	${MPIC++} -c $< -o $@ ${CPPFLAGS}

random_walker: ${OBJECTS}
	${MPIC++} -o random_walker ${OBJECTS} ${CPPFLAGS}

clean:
	rm ${OBJECTS}
	rm ${EXECS}
