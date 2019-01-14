TARGET := libmean_std.so
MPIC++ ?= mpic++
SOURCES = ${wildcard src/*.cpp}
OBJECTS = ${patsubst %.cpp,%.o, ${SOURCES}}
CPPFLAGS := -fPIC -std=c++11
INCLUDEFLAG = -I include -I ${PRAC_SOURCE_PATH}/sample/include
SHARED_LIB = -lsample
SHARED_PATH = -L ${PRAC_SOURCE_PATH}/sample/lib
.PHONY: clean

%.o: %.cpp
	${MPIC++} -c $< -o $@ ${CPPFLAGS} ${INCLUDEFLAG}

libmean_std.so: ${OBJECTS}
	${MPIC++} ${OBJECTS} -shared -o lib/$@ ${SHARED_PATH} ${SHARED_LIB}

clean:
	test -e ${CURDIR}/${OBJECTS} && rm ${OBJECTS} || echo "${OBJECTS} not existed"
	test -e ${CURDIR}/lib/${TARGET} && rm lib/${TARGET} || echo  "lib/${TARGET} not existed"
