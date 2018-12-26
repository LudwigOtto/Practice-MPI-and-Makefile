EXECS = send_recv
MPIC++ ?= mpic++
SOURCES = ${wildcard *.cpp}
OBJECTS = ${patsubst %.cpp, %.o, ${SOURCES}}
CPPFLAGS = -std=c++11
.PHONY: all clean

all: ${EXECS}

%.o: %.cpp
	${MPIC++} -c $< -o $@ ${CPPFLAGS}

send_recv: ${OBJECTS}
	${MPIC++} -o send_recv ${OBJECTS} ${CPPFLAGS}

clean:
	rm ${OBJECTS}
	rm ${EXECS}
