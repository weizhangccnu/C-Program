#!/usr/bin/python 
import os
import sys
import time
import subprocess
#---------------------------------------------------------------------#
## Main function
# @param no parameters
def main():
	#subprocess.call("./dpo5054 169.254.4.173 4000 outfile.h5 0x0f 10 100", shell = True)
	subprocess.call("make clean", shell = True)
	time.sleep(0.1)
	subprocess.call("make", shell = True)

#---------------------------------------------------------------------#
##If condition
if __name__ == "__main__":
	print "OK!"
	sys.exit(main())	#invoke main function

