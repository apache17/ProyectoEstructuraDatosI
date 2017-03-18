#ifndef LISTA_H
#define LISTA_H
#include "File.h"
#include <string>
#include <iostream>

class Lista
{
    public:
        Lista();
        virtual ~Lista();
        File *inicio;
};

#endif // LISTA_H
