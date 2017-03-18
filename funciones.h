#ifndef FUNCIONES_H
#define FUNCIONES_H
#include "File.h"
#include "Folder.h"
#include "TextFile.h"
#include "lista.h"

class Funciones
{
public:
        Funciones();

        Folder *raiz;

        File * CrearArchivo(Folder * donde,string nombre,string tipo);
        string * ListarArchivos(Folder *donde);
        File * CargarArchivo(string direccion,Folder *donde);
        File * CargarArchivo2(int pos,Folder *donde);
        int eliminarArchivo(string direccion,Folder *donde);
        void Copiar(string origen, string archivo,string destino);

        File * buscar(string nombre,Folder * donde);

        virtual ~Funciones();

    protected:

    private:

        void agregar(File * nuevo, Folder * donde);
        //File * buscarAux(string nombre, Folder * subraiz);
};

#endif // FUNCIONES_H
