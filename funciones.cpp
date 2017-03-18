#include "funciones.h"

Funciones::Funciones()
{
    raiz = new Folder("Raiz","Raiz");
}


Funciones::~Funciones()
{
    //dtor
}


File * Funciones::CrearArchivo(Folder * donde, string nombre,string tipo)
{
    File *nuevo;
    string direccion;

    if(tipo == "Archivo"){
        direccion = donde->getDireccion() + "/" + nombre + ".txt";
        nuevo = new TextFile(nombre,direccion,"Hola Mundo");
    }

    else if(tipo == "Carpeta"){
        direccion = donde->getDireccion() + "/" + nombre;
        nuevo = new Folder(nombre,direccion);
    }

    agregar(nuevo,donde);
    return nuevo;
}

void Funciones::agregar(File * nuevo,Folder *donde)
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

string * Funciones::ListarArchivos(Folder *donde)
{
    string *lista = new string[donde->cant];
    File *temp = donde->lista->inicio;
    for(int x = 0;x<donde->cant;x++)
    {
        lista[x] = temp->getNombre();
        temp = temp->siguiente;
    }
    return lista;
}

int Funciones::eliminarArchivo(string direccion,Folder *donde)
{
    File *temp = buscar(direccion,donde);
    if(temp == NULL)
        return -1;
    if(donde->lista->inicio == temp){
        donde->lista->inicio = temp->siguiente;
        donde->cant--;
        return 0;
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

File * Funciones::CargarArchivo2(int pos,Folder * donde)
{
    File *temp = donde->lista->inicio;
    for(int x = 0;x < pos; x++)
    {
        temp = temp->siguiente;
    }
    return temp;
}

File * Funciones::CargarArchivo(string direccion,Folder * donde)
{
    File *valor = buscar(direccion,donde);
    if(valor != NULL)
    {
        if(valor->getTipo()==0)
        {
            TextFile *temp = dynamic_cast<TextFile*>(valor);
            cout<<temp->getTexto();
            return temp;
        }
        else
        {
            Folder *temp = dynamic_cast<Folder*>(valor);
            return temp;
        }
    }
    return NULL;
}


File * Funciones::buscar(string direccion, Folder *donde)
{
    File * temp = donde->lista->inicio;
    for(int x = 0;x<donde->cant;x++)
    {
        if(temp->getDireccion()==direccion)
            return temp;
        temp = temp->siguiente;
    }
    return NULL;
}

/*File * Funciones::buscarAux(string direccion, Folder * subraiz)
{

    if(subraiz == NULL)
        return NULL;
    else if(subraiz->getDireccion() == direccion)
        return subraiz;
    else if(subraiz->lista->inicio != NULL){
        File *temp = subraiz->lista->inicio;
        Folder *folderTemp = dynamic_cast<Folder*>(temp);
        return buscarAux(direccion,folderTemp);
    }
    else{
        File *temp = subraiz->siguiente;
        Folder *folderTemp = dynamic_cast<Folder*>(temp);
        return buscarAux(direccion,folderTemp);
    }
}*/
