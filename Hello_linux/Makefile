objects = hello_linux.o
################################ Default ################################
CC				:= gcc
CXX				:= g++
INCLUDE			:= 
CFLAGS			:= -Wall
CFLAGS_32		:= -m32
SHLIB_CFLAGS	:= -fPIC -shared
SHLIB_EXT		:= .so
############################ Library add-ons ############################
INCLUDE += -I/usr/local/hdf5/include -I/usr/include/gsl
LIBS += -L/usr/lib64 -lgsl -lgslcblas -lm
############################# Define targets ############################
#$(CC) -o hello_linux hello_linux.o 
hello_linux: $(objects) 
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) $< -o $@ 
$(objects): hello_linux.c 
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) $< -c -o $@ 
################################# clean #################################
.PHONY: clean
clean:
	-rm hello_linux $(objects)
