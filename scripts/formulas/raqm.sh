#! /bin/bash
#
# Raqm
# A library for complex text layout
# https://github.com/HOST-Oman/libraqm
#
# array of build types supported by this formula
# you can delete this to implicitly support *all* types

FORMULA_TYPES=( "osx" "linux" "linux64" )

VER=0.3.0

# download the source code and unpack it into LIB_NAME
function download() {
	# local fileName=raqm-$VER
	#
	# curl -LO https://github.com/HOST-Oman/libraqm/releases/download/v$VER/$fileName.tar.gz
	#
	# tar -xf $fileName.tar.gz
	# mv $fileName raqm
	# rm $fileName.tar.gz

	# git clone -b linebreaking https://github.com/HOST-Oman/libraqm.git raqm
	git clone https://github.com/HOST-Oman/libraqm.git raqm
	cd raqm;
	git checkout v0.5.0
}

# prepare the build environment, executed inside the lib src dir
function prepare() {
	# generate the configure script if it's not there
	if [ ! -f configure ] ; then
		./autogen.sh
	fi
}


# executed inside the lib src dir
function build() {

	if [ "$TYPE" == "osx" ] ; then
		# Don't forget the CXXFLAGS for the c++ components.
		./configure PKG_CONFIG="$BUILD_ROOT_DIR/bin/pkg-config" \
					PKG_CONFIG_PATH="$BUILD_ROOT_DIR/lib/pkgconfig" \
					LDFLAGS="-arch i386 -stdlib=libstdc++ -arch x86_64 -Xarch_x86_64 -stdlib=libc++" \
					CFLAGS="-Os -arch i386 -stdlib=libstdc++ -arch x86_64 -Xarch_x86_64 -stdlib=libc++" \
					CXXFLAGS="-Os -arch i386 -stdlib=libstdc++ -arch x86_64 -Xarch_x86_64 -stdlib=libc++" \
					HARFBUZZ_CFLAGS="`$BUILD_ROOT_DIR/bin/./pkg-config --cflags harfbuzz`" \
					HARFBUZZ_LIBS="`$BUILD_ROOT_DIR/bin/./pkg-config --libs harfbuzz`" \
					FREETYPE_CFLAGS="`$BUILD_ROOT_DIR/bin/./pkg-config --cflags freetype2 libpng`" \
					FREETYPE_LIBS="`$BUILD_ROOT_DIR/bin/./pkg-config --libs freetype2 libpng`" \
					FRIBIDI_CFLAGS="`$BUILD_ROOT_DIR/bin/./pkg-config --cflags fribidi`" \
					FRIBIDI_LIBS="`$BUILD_ROOT_DIR/bin/./pkg-config --libs fribidi`" \
					--prefix=$BUILD_ROOT_DIR \
					--disable-dependency-tracking \
					--enable-introspection=yes \
					--enable-static=yes \
					--enable-shared=no \
					--disable-gtk-doc \
					--disable-gtk-doc-html \
					--with-glib=no \
					--with-gobject=no
  else
		./configure \
		--prefix=$BUILD_ROOT_DIR \
		--disable-dependency-tracking \
		--enable-introspection=yes \
		--enable-static=yes \
		--enable-shared=no \
		--disable-gtk-doc \
		--disable-gtk-doc-html
	fi

	make -j${PARALLEL_MAKE}
	make install

}

# executed inside the lib src dir, first arg $1 is the dest libs dir root
function copy() {
	mkdir -p $1/include/
	cp -Rv $BUILD_ROOT_DIR/include/raqm.h $1/include/

	mkdir -p $1/lib/$TYPE/
	cp -Rv $BUILD_ROOT_DIR/lib/libraqm.a $1/lib/$TYPE/

	# copy license file
	rm -rf $1/license # remove any older files if exists
	mkdir -p $1/license
	cp -v COPYING $1/license/

}

# executed inside the lib src dir
function clean() {
	# clean the project
	make clean
}
