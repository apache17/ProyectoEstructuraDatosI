#include "file.h"

File::File(string nombre, string direccion,int tipo)
{
    this->nombre = nombre;
    this->direccion = direccion;
    this->tipo = tipo;
    siguiente = NULL;
    anterior = NULL;

}

File::~File()
{
    //dtor
}

string File::getNombre()
{
    return nombre;
}

void File::setNombre(string nombre)
{
    this->nombre = nombre;
}

string File::getDireccion()
{
    return direccion;
}

int File::getTipo()
{
    return tipo;
}

void File::setDireccion(string d)
{
    direccion = d;
}
