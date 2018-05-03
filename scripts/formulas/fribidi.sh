#! /bin/bash
#
# fribidi
# bidirectional text layout
# http://fribidi.org
#
# notes on build system, reference links, etc

# array of build types supported by this formula
# you can delete this to implicitly support *all* types
FORMULA_TYPES=( "osx" )

VER=0.19.7

# download the source code and unpack it into LIB_NAME
function download() {
	local fileName=fribidi-$VER

	curl -LO https://github.com/fribidi/fribidi/releases/download/$VER/$fileName.tar.bz2

	tar -xf $fileName.tar.bz2
	mv $fileName fribidi
	rm $fileName.tar.bz2
}

# executed inside the lib src dir
function build() {

	if [ "$TYPE" == "osx" ] ; then
		# set flags for osx 32 & 64 bit fat lib
		./configure LDFLAGS="-arch i386 -stdlib=libstdc++ -arch x86_64 -Xarch_x86_64 -stdlib=libc++" \
					CFLAGS="-Os -arch i386 -stdlib=libstdc++ -arch x86_64 -Xarch_x86_64 -stdlib=libc++" \
					--prefix=$BUILD_ROOT_DIR \
					--with-glib=no \
					--disable-shared

		make -j${PARALLEL_MAKE}
		make install
	fi
}

# executed inside the lib src dir, first arg $1 is the dest libs dir root
function copy() {

	if [ "$TYPE" == "osx" ] ; then
		mkdir -p $1/include/fribidi
		cp -Rv $BUILD_ROOT_DIR/include/fribidi/* $1/include/fribidi/

		mkdir -p $1/lib/$TYPE/
		cp -Rv $BUILD_ROOT_DIR/lib/libfribidi.a $1/lib/$TYPE/
	fi

	# copy license file
	rm -rf $1/license # remove any older files if exists
	mkdir -p $1/license
	cp -v COPYING $1/license/

}

# executed inside the lib src dir
function clean() {
	make clean;
}
