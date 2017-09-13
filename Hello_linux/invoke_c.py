#!/usr/bin/env python
# -*- coding: utf-8 -*-
import ctypes
import sys
import os 
""" This python script used to test ctypes package.
    ctypes is a foreign function library for Python, It provides C compatible data types, and allows calling functions in DLLs or shared libraries.
"""
#-----------------------------------------------------------#
def main():
    print "OK!"
#-----------------------------------------------------------#
if __name__ == "__main__":
    pdll = ctypes.CDLL('./hello_linux.so')
    pdll.sum_ab(2,4)
    pdll.operate_struct(27)
    main()
