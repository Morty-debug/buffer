package main

/* 
#cgo  CFLAGS:  -I./include 
#cgo  LDFLAGS:  -L./lib  -lbufftofile 
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
    file, err1 := os.Open("original.jpg")
    if err1 != nil {
        fmt.Println("ERROR - No se pudo abrir el archivo 'original.jpg'\n")
        return
    }
    defer file.Close()
    //archivo estructurado
    fileinfo, err2 := file.Stat()
    if err2 != nil {
        fmt.Println("ERROR - No se pudo obtener informacion del archivo 'original.jpg'\n")
        return
    }
    //archivo estructurado a buffer
    filesize := fileinfo.Size()
    buffer := make([]byte, filesize)
    //leer buffer
    bytesread, err3 := file.Read(buffer)
    if err3 != nil {
        fmt.Println("ERROR - No se pudo leer el archivo 'original.jpg'\n")
        return
    }
    //convertir buffer a buffer para C
    cbuffer := C.CBytes(buffer)
    csize := C.long(bytesread)
    //enviamos buffer a C
    error := C.bufftofile(cbuffer,csize)
    //mostramos resultado
    fmt.Println("Archivo: 'original.jpg' replicado en C")
    fmt.Println("Errores: ",error,"\n")
    //creamos el archivo
    f, err4 := os.Create("bufferGO")
    if err4 != nil {
        fmt.Println("ERROR - No se pudo crear el archivo 'bufferGO'\n")
        return
    }
    defer f.Close()
    //de cbuffer a gobuffer
    gobuffer := C.GoBytes(unsafe.Pointer(cbuffer), C.int(filesize)+1)
    _, err5 := f.Write(gobuffer)
    if err5 != nil {
        fmt.Println("ERROR - No se pudo escribir el archivo 'bufferGO'\n")
        return
    }
    //mostramos resultado
    fmt.Println("Archivo: 'original.jpg' replicado en GO")
    fmt.Println("Errores:  0\n")
}

