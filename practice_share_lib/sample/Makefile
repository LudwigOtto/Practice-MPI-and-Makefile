TARGET := libsample.so
MPIC++ ?= mpic++
SOURCES = ${wildcard *.cpp}
OBJECTS = ${patsubst %.cpp,%.o, ${SOURCES}}
CPPFLAGS := -fPIC -std=c++11
SHAREDFLAGS := -shared
.PHONY: clean

%.o: %.cpp
	${MPIC++} -c $< -o $@ ${CPPFLAGS}

libsample.so: ${OBJECTS}
	${MPIC++} ${OBJECTS} ${SHAREDFLAGS} -o $@

clean:
	test -e ${CURDIR}/${OBJECTS} && rm ${OBJECTS} || echo "${OBJECTS} not existed"
	test -e ${CURDIR}/${TARGET} && rm ${TARGET} || echo  "${TARGET} not existed"
