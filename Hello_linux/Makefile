objects = hello_linux.o
VPATH = /usr/local/hdf5/include
#################################### parameter define ####################################
hello_linux: $(objects) 
	cc -o hello_linux hello_linux.o
$(objects): hello_linux.c hdf5.h
	cc -c hello_linux.c
#################################### clean ####################################
.PHONY : clean
clean:
	-rm hello_linux $(objects)
