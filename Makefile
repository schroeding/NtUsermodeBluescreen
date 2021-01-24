ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

all: 
	x86_64-w64-mingw32-gcc main.c -o NtUsermodeBluescreen.exe

clean:
	rm NtUsermodeBluescreen.exe