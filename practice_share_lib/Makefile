EXECS = send_recv
C++ ?= mpic++
SOURCES = ${wildcard *.cpp}
OBJECTS = ${patsubst %.cpp,%.o, ${SOURCES}}
CPPFLAGS = -std=c++11
INCLUDE_PATH = -I ${CURDIR}/sample
SHARED_LIB = -lsample
SHARED_PATH = -L ${CURDIR}/sample
SHARED_FILE = ${patsubst -l%,lib%.so, ${SHARED_LIB}}
.PHONY: all clean

all:
	for file in ${SHARED_FILE} ; do \
		$(MAKE) $$file ; \
	done
	$(MAKE) ${EXECS}

lib%.so: %
	test -e ${CURDIR}/$</$@ || $(MAKE) -C ${CURDIR}/$< $@

%.o: %.cpp
	${C++} -c $< -o $@ ${INCLUDE_PATH} ${CPPFLAGS}

send_recv: ${OBJECTS}
	${C++} -o $@ ${OBJECTS} ${CPPFLAGS} ${SHARED_PATH} ${SHARED_LIB}

clean:
	for file in ${SHARED_FILE} ; do \
		$(MAKE) sub_clean_$$file ; \
	done
	test -e ${CURDIR}/${OBJECTS} && rm ${OBJECTS} || echo "${OBJECTS} not existed"
	test -e ${CURDIR}/${EXECS} && rm ${EXECS} || echo "${EXECS} not existed"

sub_clean_lib%.so: %
	$(MAKE) -C ${CURDIR}/$< clean
