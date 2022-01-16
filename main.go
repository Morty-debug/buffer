package main
/* 
#cgo  CFLAGS:  -I./include 
#cgo  LDFLAGS:  -L./lib  -lbufftofile -Wl,-rpath=./lib
#include "bufftofile.h" 
*/  
import "C" 
import (
    "os"
    "fmt"
    "unsafe"
)
func main() {
    //archivo a procesar
    file, err := os.Open("original.jpg")
    if err != nil {
        fmt.Println(err)
        return
    }
    defer file.Close()
    //archivo estructurado
    fileinfo, err := file.Stat()
    if err != nil {
        fmt.Println(err)
        return
    }
    //archivo estructurado a buffer
    filesize := fileinfo.Size()
    buffer := make([]byte, filesize)
    //leer buffer
    bytesread, err := file.Read(buffer)
    if err != nil {
        fmt.Println(err)
        return
    }
    //convertir buffer a buffer para C
    cbuffer := C.CBytes(buffer)
    csize := C.long(bytesread)
    //enviamos buffer a C
    error := C.bufftofile(cbuffer,csize)
    //mostramos resultado
    fmt.Println("Archivo: 'original.jpg' replicado en C")
    fmt.Println("Errores: ",error)
    //creamos el archivo
    f, err := os.Create("bufferGO")
    if err != nil {
        fmt.Println("ERROR - No se pudo crear el archivo 'bufferGO'\n")
        return
    }
    defer f.Close()
    //de cbuffer a gobuffer
    gobuffer := C.GoBytes(unsafe.Pointer(cbuffer), C.int(filesize)+1)
    _, err2 := f.Write(gobuffer)
    if err2 != nil {
        fmt.Println("ERROR - No se pudo escribir el archivo 'bufferGO'\n")
        return
    }
    //mostramos resultado
    fmt.Println("Archivo: 'original.jpg' replicado en GO")
    fmt.Println("Errores:  0")
}

