#! /bin/bash
#
# libunibreak
# Breaks lines and words according to the unicode standard.
# https://github.com/adah1972/libunibreak
#
# notes on build system, reference links, etc

# array of build types supported by this formula
# you can delete this to implicitly support *all* types

FORMULA_TYPES=( "osx" )

VER=4_0

GIT_URL=https://github.com/adah1972/libunibreak.git
GIT_TAG=libunibreak_$VER

# download the source code and unpack it into LIB_NAME
function download() {
	curl -LO https://github.com/adah1972/libunibreak/archive/libunibreak_$VER.tar.gz
	tar -xf libunibreak_$VER.tar.gz
	mv libunibreak-libunibreak_$VER unibreak
	rm libunibreak_$VER.tar.gz
}

# prepare the build environment, executed inside the lib src dir
function prepare() {
	# initialize the repository

	# generate the configure script if it's not there
	if [ ! -f configure ] ; then
		./bootstrap
	fi
}


# executed inside the lib src dir
function build() {

	_LDFLAGS=
	_CFLAGS=

	if [ "$TYPE" == "osx" ] ; then
		# set flags for osx 32 & 64 bit fat lib
		_LDFLAGS="-arch i386 -stdlib=libstdc++ -arch x86_64 -Xarch_x86_64 -stdlib=libc++"
		_CFLAGS="-Os -arch i386 -stdlib=libstdc++ -arch x86_64 -Xarch_x86_64 -stdlib=libc++" 
	fi

	./configure LDFLAGS=${_LDFLAGS} CFLAGS=${_CFLAGS} --prefix=${BUILD_ROOT_DIR} --disable-shared

	make -j${PARALLEL_MAKE}
	make install

}

# executed inside the lib src dir, first arg $1 is the dest libs dir root
function copy() {
	mkdir -p $1/include/
	cp -v $BUILD_ROOT_DIR/include/graphemebreak.h $1/include/
	cp -v $BUILD_ROOT_DIR/include/linebreak.h $1/include/
	cp -v $BUILD_ROOT_DIR/include/linebreakdef.h $1/include/
	cp -v $BUILD_ROOT_DIR/include/unibreakbase.h $1/include/
	cp -v $BUILD_ROOT_DIR/include/unibreakdef.h $1/include/
	cp -v $BUILD_ROOT_DIR/include/wordbreak.h $1/include/

	mkdir -p $1/lib/$TYPE/
	cp -R $BUILD_ROOT_DIR/lib/libunibreak.a $1/lib/$TYPE/

	# copy license file
	rm -rf $1/license # remove any older files if exists
	mkdir -p $1/license
	# yes, they spelled it licence
	cp -v LICENCE $1/license/
}

# executed inside the lib src dir
function clean() {
	make clean
}
