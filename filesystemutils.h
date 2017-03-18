#ifndef FILESYSTEMUTILS_H
#define FILESYSTEMUTILS_H


#include "File.h"
#include "Folder.h"
#include "TextFile.h"
#include "lista.h"
#include <qlist.h>


class FileSystemUtils
{
public:
        FileSystemUtils();
        Folder *raiz;
        File * fsCrearArchivo(Folder * donde,string nombre,string tipo);
        QList<File*> fsListarArchivos(Folder *donde);
        File * fsCargarArchivo(string nombre,Folder *donde);
        void fsPegar(File * nuevo, Folder *donde);
        int fsEliminarArchivo(string nombre,Folder *donde);
        File * fsCopiar(string nombre,Folder *donde);
        string fsDuplicados(string nombre, Folder * donde);
        File * copiarCarpeta(Folder *carpeta, Folder *copiar);


    protected:

    private:
        File * buscar(int pos,Folder * donde);
        void agregar(File * nuevo, Folder * donde);
        string duplicadosAux(string nombre, Folder * donde,int cant,int tamanoPalabra);
        string toLowerCase(string palabra);
};

#endif // FILESYSTEMUTILS_H
