#include "filesystemutils.h"

FileSystemUtils::FileSystemUtils()
{
    raiz = new Folder("Raiz","Raiz");
}



File * FileSystemUtils::fsCrearArchivo(Folder * donde, string nombre,string tipo)
{
    File *nuevo;
    string direccion;


    if(tipo == "Archivo"){
        direccion = donde->getDireccion() + nombre + ".txt"+"/";
        nuevo = new TextFile(nombre,direccion,"");
    }

    else if(tipo == "Carpeta"){
        direccion = donde->getDireccion() + nombre + "/";
        nuevo = new Folder(nombre,direccion);
    }

    agregar(nuevo,donde);
    return nuevo;
}

void FileSystemUtils::agregar(File * nuevo,Folder *donde)
{
    if(donde->lista->inicio == NULL){
        donde->lista->inicio = nuevo;
        donde->cant++;
    }
    else
    {
        File * temp = donde->lista->inicio;
        while(temp->siguiente != NULL)
            temp = temp->siguiente;
        temp->siguiente = nuevo;
        nuevo->anterior = temp;
        donde->cant++;
    }
}

void FileSystemUtils::fsPegar(File * nuevo,Folder *donde)
{
    agregar(nuevo,donde);
}

 QList<File*> FileSystemUtils::fsListarArchivos(Folder *donde)
{
    QList<File*> lista;
    File *temp = donde->lista->inicio;
    for(int x = 0;x<donde->cant;x++)
    {
        lista.append(temp);
        temp = temp->siguiente;
    }
    return lista;
}

int FileSystemUtils::fsEliminarArchivo(string nombre,Folder *donde)
{
    File *temp = fsCargarArchivo(nombre,donde);
    if(temp == NULL)
        return -1;
    if(donde->lista->inicio == temp){
        donde->lista->inicio = temp->siguiente;
        donde->cant--;
    }
    else if(temp->siguiente == NULL){
        File * temp2 = temp->anterior;
        temp2->siguiente =NULL;
        donde->cant--;
    }
    else{
        File *t1 = temp->siguiente;
        File *t2 = temp->anterior;
        t2->siguiente = t1;
        t1->anterior = t2;
        donde->cant--;
    }
    return 0;
}

File * FileSystemUtils::fsCargarArchivo(string nombre,Folder * donde)
{
    File *temp = donde->lista->inicio;
    for(int x = 0;x<donde->cant;x++)
    {
        if(temp->getNombre() == nombre)
            return temp;
        temp = temp->siguiente;
    }
    return temp;
}

File * FileSystemUtils::buscar(int pos, Folder *donde)
{
    File * temp = donde->lista->inicio;
    for(int x = 0;x<pos;x++)
    {
        temp = temp->siguiente;
    }
    return temp;
}


string FileSystemUtils::duplicadosAux(string nombre, Folder * donde, int cant,int tamanoPalabra)
{
    string a = nombre;
    File * temp = donde->lista->inicio;
    for(int x = 0;x<donde->cant;x++)
    {
        if(toLowerCase(temp->getNombre()) == toLowerCase(nombre)){
            string z = to_string(cant);
            if(nombre.size() > tamanoPalabra)
                a = a.substr(0,nombre.size()-2);
            return duplicadosAux(a+"_"+z,donde,cant+1,tamanoPalabra);
        }
        temp = temp->siguiente;
    }
    return nombre;
}

string FileSystemUtils::fsDuplicados(string nombre, Folder * donde)
{
    return duplicadosAux(nombre,donde,1,nombre.size());
}

string FileSystemUtils::toLowerCase(string palabra)
{
    locale loc;
    string palabraNueva;
    for (string::size_type i=0; i<palabra.length(); ++i)
        palabraNueva = palabraNueva+tolower(palabra[i],loc);
    return palabraNueva;
}

File * FileSystemUtils::fsCopiar(string nombre,Folder *donde)
{
    File * temp = fsCargarArchivo(nombre,donde);
    if(temp->getTipo() == 0)
    {
        TextFile * archivo = dynamic_cast<TextFile*>(temp);
        TextFile * copiar = new TextFile(archivo->getNombre(),archivo->getDireccion(),archivo->getTexto());
        return copiar;
    }
    else
    {
         Folder * carpeta = dynamic_cast<Folder*>(temp);
         Folder * copiar = new Folder(carpeta->getNombre(),carpeta->getDireccion());
         copiarCarpeta(carpeta,copiar);
         return copiar;
    }
}

File * FileSystemUtils::copiarCarpeta(Folder *carpeta,Folder * copiar)
{
    if(carpeta->lista->inicio == NULL)
        return copiar;
    else
    {
        File * temp = carpeta->lista->inicio;
        for(int x = 0;carpeta->cant > x;x++)
        {
            if(temp->getTipo() == 0)
                fsCrearArchivo(copiar,temp->getNombre(),"Archivo");
            else
            {
                File *tempNuevo = fsCrearArchivo(copiar,temp->getNombre(),"Carpeta");
                Folder * sigCopiar = dynamic_cast<Folder*>(tempNuevo);
                Folder * sigCarpeta = dynamic_cast<Folder*>(temp);
                copiarCarpeta(sigCarpeta,sigCopiar);
            }
            temp = temp->siguiente;
        }
    }
}
