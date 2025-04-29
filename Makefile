CPP_COMPILER = g++

windows:
	$(CPP_COMPILER) \
	-m32 -shared -std=c++11 -Wall -O2 -static -Wl,--kill-at \
	-DHAVE_STDINT_H -DWIN32 -DSAMPGDK_AMALGAMATION -DSAMPGDK_CPP_WRAPPERS \
	-ISDK -ISDK/amx \
	-o physics.dll \
	src/*.cpp SDK/amxplugin.cpp SDK/sampgdk.c

linux:
	$(CPP_COMPILER) \
	-m32 -shared -std=c++11 -Wall -O2 \
	-DLINUX -DSAMPGDK_AMALGAMATION -DSAMPGDK_CPP_WRAPPERS \
	-ISDK -ISDK/amx \
	-o physics.so  \
	src/*.cpp SDK/amxplugin.cpp SDK/sampgdk.c
