#include "textfile.h"


TextFile::TextFile(string nombre, string direccion,string texto) : File(nombre,direccion,0)
{
    this->texto = texto;
    this->item = item;
}

TextFile::~TextFile()
{
    //dtor
}

string TextFile::getDireccion()
{
    return File::getDireccion();
}

string TextFile::getTexto()
{
    return texto;
}

void TextFile::setTexto(string valor)
{
    texto = valor;
}


string TextFile::getNombre()
{
    return File::getNombre();
}

int TextFile::getTipo()
{
    return File::getTipo();
}

void TextFile::setDireccion(string d)
{
    return File::setDireccion(d);
}

void TextFile::setNombre(string nombre)
{
    return File::setNombre(nombre);
}
