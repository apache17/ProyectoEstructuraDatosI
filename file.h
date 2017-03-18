#ifndef FILE_H
#define FILE_H
#include <iostream>
#include <string>
using namespace std;
class File
{
    public:
        File(string nombre, string direccion, int tipo);
        virtual ~File();
        virtual string getNombre();
        virtual void setNombre(string nombre);
        virtual string getDireccion();
        virtual void setDireccion(string d);
        virtual int getTipo();
        File * siguiente;
        File * anterior;

    private:
        string nombre;
        string direccion;
        int tipo;
};

#endif // FILE_H
