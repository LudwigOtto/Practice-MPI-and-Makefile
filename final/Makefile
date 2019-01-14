TEST = mpi_prac
C++ ?= mpic++
SOURCES = ${wildcard test/*.cpp}
OBJECTS = ${patsubst %.cpp,%.o, ${SOURCES}}
CPPFLAGS = -std=c++11
INCLUDE_PATH := -I ${PRAC_SOURCE_PATH}/sample/include -I ${PRAC_SOURCE_PATH}/walker/include 
INCLUDE_PATH := $(INCLUDE_PATH) -I ${PRAC_SOURCE_PATH}/mean_std/include 
SHARED_LIB = -lsample -lwalker -lmean_std
SHARED_PATH := -L ${PRAC_SOURCE_PATH}/sample/lib -L ${PRAC_SOURCE_PATH}/walker/lib
SHARED_PATH := $(SHARED_PATH) -L ${PRAC_SOURCE_PATH}/mean_std/lib
SHARED_FILE = ${patsubst -l%,lib%.so, ${SHARED_LIB}}
.PHONY: all clean

all:
	for file in ${SHARED_FILE} ; do \
		$(MAKE) $$file ; \
	done
	$(MAKE) ${TEST}

lib%.so: %
	test -e ${PRAC_SOURCE_PATH}/$</lib/$@ || $(MAKE) -C ${PRAC_SOURCE_PATH}/$< $@

%.o: %.cpp
	${C++} -c $< -o $@ ${INCLUDE_PATH} ${CPPFLAGS}

mpi_prac: ${OBJECTS}
	${C++} -o test/$@ ${OBJECTS} ${CPPFLAGS} ${SHARED_PATH} ${SHARED_LIB}

clean:
	for file in ${SHARED_FILE} ; do \
		$(MAKE) sub_clean_$$file ; \
	done
	test -e ${OBJECTS} && rm ${OBJECTS} || echo "${OBJECTS} not existed"
	test -e test/${TEST} && rm test/${TEST} || echo "test/${TEST} not existed"

sub_clean_lib%.so: %
	$(MAKE) -C ${PRAC_SOURCE_PATH}/$< clean
