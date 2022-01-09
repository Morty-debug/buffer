# Go buffer a C buffer y biseversa

WINDOWS:
```batch
  set PATH=%PATH%;%CD%\lib
  gcc -fPIC ./include/bufftofile.c -shared -o ./lib/libbufftofile.dll
  go run main.go
```

LINUX:
```sh
  export LD_LIBRARY_PATH=$PWD/lib
  gcc -fPIC ./include/bufftofile.c -shared -o ./lib/libbufftofile.so
  go run main.go
```
