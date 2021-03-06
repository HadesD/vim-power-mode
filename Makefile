all:
	cd build && \
		cmake .. && \
		make -j $(shell nproc) gen_compile_commands ; \
		make -j $(shell nproc)
	./bin/Particle.exe

clean:
	git clean -xdf build bin

x11.test:
	g++ -Wall -o tests/x11.exe \
		tests/x11.cpp \
		$(shell pkg-config --cflags --libs x11)
	./tests/x11.exe

