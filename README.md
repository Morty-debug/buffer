
### compilar codigo en GO y GCC dentro de Windows
```batch
set PATH=%PATH%;%CD%\lib
gcc -fPIC ./include/bufftofile.c -shared -o ./lib/libbufftofile.dll
go run main.go
```

### compilar codigo en GO y GCC dentro de Linux
```sh
export LD_LIBRARY_PATH=$PWD/lib
gcc -fPIC ./include/bufftofile.c -shared -o ./lib/libbufftofile.so
go run main.go
```

