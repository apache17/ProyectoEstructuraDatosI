#ifndef TEXTFILE_H
#define TEXTFILE_H
#include "File.h"

#include <QTreeWidget>

class TextFile : public File
{
    public:
        TextFile(string nombre, string direccion,string texto);
        string getDireccion();
        string getNombre();
        string getTexto();
        void setNombre(string nombre);
        void setTexto(string valor);
        QTreeWidgetItem * item;
        void setDireccion(string d);
        int getTipo();
        virtual ~TextFile();

    protected:

    private:
        string texto;

};

#endif // TEXTFILE_H
