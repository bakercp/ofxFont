meta:
	ADDON_NAME = ofxFont
	ADDON_DESCRIPTION = A collection utilties for working with text and typography.
	ADDON_AUTHOR = bakercp
	ADDON_TAGS = "font" "typography" "text"
	ADDON_URL = http://github.com/bakercp/ofxFont

common:
	# None

osx:
	# None

linux:
	ADDON_PKG_CONFIG_LIBRARIES = harfbuzz fribidi libunibreak

linux64:
	ADDON_PKG_CONFIG_LIBRARIES = harfbuzz fribidi libunibreak
