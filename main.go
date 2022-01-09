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
)

func main() {

    //archivo a procesar
    file, err := os.Open("cara.jpg")
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
    cbuffer := C.CString(string(buffer))
    csize := C.long(bytesread)

    //enviamos buffer a C
    error := C.bufftofile(cbuffer,csize)

    //mostramos resultado
    fmt.Println("\nArchivo: OUT")
    fmt.Println("Errores: ",error)
    
    
    //foo := C.CString("")
    //defer C.free(unsafe.Pointer(foo))
    //C.test(foo)
    //fmt.Println("Output is: "+C.GoString(foo)*/
    asciiBytes := []byte(C.GoString(cbuffer))
    
    
}
