#ifndef FOLDER_H
#define FOLDER_H
#include "File.h"
#include "lista.h"

#include <qtreewidget.h>

class Folder : public File
{
    public:
        Folder(string nombre, string direccion);
        string getNombre();
        void setNombre(string nombre);
        string getDireccion();
        void setDireccion(string d);
        int getTipo();
        Lista *lista;
        QTreeWidgetItem * item;
        int cant;
        virtual ~Folder();


        Folder * anterior;
        Folder * siguiente;
};

#endif // FOLDER_H
