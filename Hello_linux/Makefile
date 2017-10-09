hello_linux: hello_linux.o
	gcc -o hello_linux hello_linux.o
hello_linux.o: hello_linux.c /usr/local/hdf5/include/hdf5.h
	gcc -c hello_linux.c
clean:
	rm hello_linux.o
