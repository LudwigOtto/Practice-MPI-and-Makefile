TARGET := libsample.so
MPIC++ ?= mpic++
SOURCES = ${wildcard src/*.cpp}
OBJECTS = ${patsubst %.cpp,%.o, ${SOURCES}}
CPPFLAGS := -fPIC -std=c++11
INCLUDEFLAG = -I include
SHAREDFLAGS := -shared
.PHONY: clean

%.o: %.cpp
	${MPIC++} -c $< -o $@ ${CPPFLAGS} ${INCLUDEFLAG}

libsample.so: ${OBJECTS}
	${MPIC++} ${OBJECTS} ${SHAREDFLAGS} -o lib/$@

clean:
	test -e ${CURDIR}/${OBJECTS} && rm ${OBJECTS} || echo "${OBJECTS} not existed"
	test -e ${CURDIR}/lib/${TARGET} && rm lib/${TARGET} || echo  "lib/${TARGET} not existed"
