## Name and function ##
1. Hello_linux.c file: this is my first C program to learn writing Makefile and to test gsl library.
## .so file compile command ##
1. gcc hello_linux.c -fPIC -shared -l hello_linux -L/usr/lib64 -lgsl
## Execute command ##
1. ./hello_linux 5 0 100 10 
2. Learn how to write own Makefile from zero. link:<http://blog.csdn.net/ruglcc/article/details/7814546/>