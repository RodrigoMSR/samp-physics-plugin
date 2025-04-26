windows:
	C:\mingw32\bin\g++ \
	-m32 -shared -std=c++11 -Wall -static -Wl,--kill-at \
	-DHAVE_STDINT_H -DWIN32 -DSAMPGDK_AMALGAMATION -DSAMPGDK_CPP_WRAPPERS \
	-ISDK -ISDK/amx \
	-o physics.dll \
	src/*.cpp SDK/amxplugin.cpp SDK/sampgdk.c

linux:
	g++ \
	-m32 -shared -std=c++11 -Wall \
	-DLINUX -DSAMPGDK_AMALGAMATION -DSAMPGDK_CPP_WRAPPERS \
	-ISDK -ISDK/amx \
	-o physics.so  \
	src/*.cpp SDK/amxplugin.cpp SDK/sampgdk.c

clean:
	$(RM) main
