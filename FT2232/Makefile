objects = FT2232_Test.o
################################ Default ################################
CC				:= gcc
CXX				:= g++
INCLUDE			:= 
CFLAGS			:= -Wall
CFLAGS_32		:= -m32
SHLIB_CFLAGS	:= -fPIC -shared
SHLIB_EXT		:= .so
############################ Library add-ons ############################
INCLUDE += -I/usr/local/include
LIBS += -L/usr/local/lib -lftd2xx
############################# Define targets ############################
#$(CC) -o hello_linux hello_linux.o 
FT2232_Test: $(objects) 
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) $< -o $@ 
$(objects): FT2232_Test.c 
	$(CC) $(CFLAGS) $(INCLUDE) $(LIBS) $< -c -o $@ 
################################# clean #################################
.PHONY: clean
clean:
	-rm FT2232_Test $(objects)
