export LD_LIBRARY_PATH=$PWD/lib
gcc -fPIC ./include/bufftofile.c -shared -o ./lib/libbufftofile.so
go run main.go