set PATH=%PATH%;%CD%\lib
gcc -fPIC ./include/bufftofile.c -shared -o ./lib/libbufftofile.dll
go run main.go