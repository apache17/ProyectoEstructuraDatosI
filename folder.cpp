#include "folder.h"

Folder::Folder(string nombre, string direccion) : File(nombre,direccion,1)
{
    this->item = item;
    lista = new Lista();
    cant = 0;
    anterior = NULL;
    siguiente = NULL;
}

Folder::~Folder()
{
    //dtor
}

string Folder::getDireccion()
{
    return File::getDireccion();
}

string Folder::getNombre()
{
    return File::getNombre();
}

int Folder::getTipo()
{
    return File::getTipo();
}

void Folder::setDireccion(string d)
{
    return File::setDireccion(d);
}

void Folder::setNombre(string nombre)
{
    return File::setNombre(nombre);
}

