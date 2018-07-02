.PHONY: all

all: particle.exe

default: particle.exe

particle.exe: particle.cpp
	g++ -Wall \
		-o particle.exe -mwindows \
		particle.cpp \
		-lgdi32

clean:
	rm particle.exe

x11.test:
	g++ -Wall -o tests/x11.exe \
		tests/x11.cpp \
		$(shell pkg-config --cflags --libs x11)
	./tests/x11.exe

