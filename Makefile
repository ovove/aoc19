
ifeq "${VARIANT}" ""
BUILD_DIR_:=build
BUILD_TYPE_:=
else
VARIANT_ := $(shell echo ${VARIANT} | tr '[:upper:]' '[:lower:]')
ifeq "${VARIANT_}" "release"
BUILD_DIR_:=release
BUILD_TYPE_:=-DCMAKE_BUILD_TYPE=Release
else
ifeq "${VARIANT_}" "debug"
BUILD_DIR_:=debug
BUILD_TYPE_:=-DCMAKE_BUILD_TYPE=Debug
else
$(error unknown VARIANT "${VARIANT}")
endif
endif
endif

.PHONY: all config build test clean realclean help

all: config build

config:
	cmake -H. -B${BUILD_DIR_} ${BUILD_TYPE_}

build: config
	make -C${BUILD_DIR_}

test: build
	make -C${BUILD_DIR_} test

clean:
	make -C${BUILD_DIR_} clean

realclean:
	rm -rf ${BUILD_DIR_}

help: config
	make -C${BUILD_DIR_} help

