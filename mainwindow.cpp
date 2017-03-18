#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fs = new FileSystemUtils();
    raiz = new Folder("Raiz","Raiz/");
    folderActual = raiz;
    fileCopiar = NULL;
    ui->btnAtras->setStyleSheet("border-image: url(:/Imagenes/901 (1) - copia.png);");
    ui->btnAdelante->setStyleSheet("border-image: url(:/Imagenes/901 (1).png);");
    ui->btnPegar->hide();
    arbol = ui->treeView;
    refrescar();
}

void MainWindow::agregarLabel(string nombre)
{
    listaEtiquetas.append(new QLabel(this));
    listaEtiquetas.at(cantLabel)->setText(nombre.c_str());
    listaEtiquetas.at(cantLabel)->setGeometry(QRect(QPoint(posX, posY+45),QSize(60, 40)));
    listaEtiquetas.at(cantLabel)->setAlignment(Qt::AlignCenter);
    listaEtiquetas.at(cantLabel)->show();
    cantLabel++;
}

void MainWindow::insertarCarpeta(string texto)
{
    agregarLabel(texto);
    listaBotones.append(new QPushButton(this));
    listaBotones.at(cantBotones)->setObjectName(QString::fromStdString(texto));
    listaBotones.at(cantBotones)->setGeometry(QRect(QPoint(posX, posY),QSize(50, 50)));
    listaBotones.at(cantBotones)->setStyleSheet("border-image: url(:/Imagenes/Folders-PNG-File.png);");
    listaBotones.at(cantBotones)->show();
    connect(listaBotones.at(cantBotones), SIGNAL (released()),this, SLOT (eventoCarpetas()));
    TreeModel * a = new TreeModel(QString::fromStdString(texto));
    arbol->setModel(a);
    arbol->show();
    cantBotones++;
    posX = posX + 80;
    if(posX >=600)
    {
        posX = 170;
        posY = posY+90;
    }
}

void MainWindow::insertarArchivo(string texto)
{
    agregarLabel(texto);
    listaBotones.append(new QPushButton(this));
    listaBotones.at(cantBotones)->setObjectName(QString::fromStdString(texto));
    listaBotones.at(cantBotones)->setGeometry(QRect(QPoint(posX, posY),QSize(60, 60)));
    listaBotones.at(cantBotones)->setStyleSheet("border-image: url(:/Imagenes/Docs-icon-iloveimg-resized.png);");
    listaBotones.at(cantBotones)->show();
    connect(listaBotones.at(cantBotones), SIGNAL (released()),this, SLOT (eventoArchivos()));
    TreeModel * a = new TreeModel(QString::fromStdString(texto));
    arbol->setModel(a);
    arbol->show();
    cantBotones++;
    posX = posX + 80;
    if(posX >=600)
    {
        posX = 170;
        posY = posY+90;
    }
}

void MainWindow::eliminar_archivo()
{
    fs->fsEliminarArchivo(obtenerNodo(),folderActual);
    refrescar();
}

void MainWindow::abrir_archivo()
{
    File * temp = fs->fsCargarArchivo(obtenerNodo(),folderActual);
    Folder* folder = dynamic_cast<Folder*>(temp);
    Folder *temp2 = folderActual;
    folderActual = folder;
    folderActual->anterior = temp2;
    refrescar();
}

void MainWindow::editar_archivo()
{
    File * temp = fs->fsCargarArchivo(obtenerNodo(),folderActual);
    TextFile* file = dynamic_cast<TextFile*>(temp);
    QString x = QInputDialog::getText(this,"Modificar Archivo","Ingrese el Texto:");
    file->setTexto(x.toStdString());
}

void MainWindow::leer_archivo()
{
    File * temp = fs->fsCargarArchivo(obtenerNodo(),folderActual);
    TextFile* file = dynamic_cast<TextFile*>(temp);
    string texto = file->getTexto();
    msgBox.setText(texto.c_str());
    msgBox.exec();
}

void MainWindow::on_btnPegar_clicked()
{
    File *temp = fileCopiar;
    temp->setNombre(fs->fsDuplicados(temp->getNombre(),folderActual));
    temp->setDireccion(folderActual->getDireccion()+temp->getNombre()+"/");
    fs->fsPegar(temp,folderActual);
    fileCopiar = NULL;
    ui->btnPegar->hide();
    refrescar();
}

void MainWindow::copiar()
{
    fileCopiar = fs->fsCopiar(obtenerNodo(),folderActual);
    ui->btnPegar->show();
}


string MainWindow::obtenerNodo()
{
    QPushButton* temp = qobject_cast<QPushButton *>(sender());
    if(temp!=NULL)
    {
        for(int x = 0;x<listaBotones.size();x++){
            if(listaBotones.at(x)->objectName() == temp->objectName())
                return temp->objectName().toStdString();
        }
    }

    return NULL;
}

void MainWindow::on_btnNuevo_clicked()
{
    QMessageBox msgBoxNuevo;
    msgBoxNuevo.setText(tr("Crear Nuevo"));
    QAbstractButton * pButtonCarpeta = msgBoxNuevo.addButton(tr("Carpeta"), QMessageBox::YesRole);
    QAbstractButton * pButtonArchivo = msgBoxNuevo.addButton(tr("Archivo"), QMessageBox::YesRole);
    msgBoxNuevo.addButton(tr("Cancelar"), QMessageBox::NoRole);
    msgBoxNuevo.exec();
    if(msgBoxNuevo.clickedButton()==pButtonCarpeta) {
        QString x = QInputDialog::getText(this,"Nueva Carpeta","Ingrese el Nombre de la Carpeta:");
        string nombre = x.toStdString();
        nombre = fs->fsDuplicados(nombre,folderActual);
        if(x != ""){
            fs->fsCrearArchivo(folderActual,nombre,"Carpeta");
            insertarCarpeta(nombre);
        }
    }
    else if(msgBoxNuevo.clickedButton()==pButtonArchivo)
    {
        QString x = QInputDialog::getText(this,"Nuevo Archivo","Ingrese el Nombre del Archivo:");
        string nombre = x.toStdString();
        nombre = fs->fsDuplicados(nombre,folderActual);
        if(x != ""){
            fs->fsCrearArchivo(folderActual,nombre,"Archivo");
            insertarArchivo(nombre);
        }
    }
}

void MainWindow::eventoArchivos()
{
    QMessageBox msgBoxArchivos;
    msgBoxArchivos.setWindowTitle("File System Utils");
    msgBoxArchivos.setText(tr("Que desea hacer?"));
    QAbstractButton * pButtonAbrir = msgBoxArchivos.addButton(tr("Leer"), QMessageBox::YesRole);
    QAbstractButton * pButtonEditar = msgBoxArchivos.addButton(tr("Editar"), QMessageBox::YesRole);
    QAbstractButton * pButtonEliminar = msgBoxArchivos.addButton(tr("Eliminar"), QMessageBox::YesRole);
    QAbstractButton * pButtonCopiar = msgBoxArchivos.addButton(tr("Copiar"), QMessageBox::YesRole);
    msgBoxArchivos.addButton(tr("Cancelar"), QMessageBox::NoRole);
    msgBoxArchivos.exec();

    if(msgBoxArchivos.clickedButton()==pButtonAbrir){
        leer_archivo();
        msgBoxArchivos.close();
    }
    else if(msgBoxArchivos.clickedButton()==pButtonEditar){
        editar_archivo();
        msgBoxArchivos.close();
    }
    else if(msgBoxArchivos.clickedButton()==pButtonEliminar){
        eliminar_archivo();
        msgBoxArchivos.close();
    }
    else if(msgBoxArchivos.clickedButton()==pButtonCopiar){
        copiar();
        msgBoxArchivos.close();
    }
    else
        msgBoxArchivos.close();
}

void MainWindow::eventoCarpetas()
{
    QMessageBox msgBoxCarpetas;
    msgBoxCarpetas.setWindowTitle("File System Utils");
    msgBoxCarpetas.setText(tr("Que desea hacer?"));
    QAbstractButton * pButtonAbrir = msgBoxCarpetas.addButton(tr("Abrir"), QMessageBox::YesRole);
    QAbstractButton * pButtonEliminar = msgBoxCarpetas.addButton(tr("Eliminar"), QMessageBox::YesRole);
    QAbstractButton * pButtonCopiar = msgBoxCarpetas.addButton(tr("Copiar"), QMessageBox::YesRole);
    msgBoxCarpetas.addButton(tr("Cancelar"), QMessageBox::NoRole);
    msgBoxCarpetas.exec();

    if(msgBoxCarpetas.clickedButton()==pButtonAbrir){
        abrir_archivo();
        msgBoxCarpetas.close();
    }
    else if(msgBoxCarpetas.clickedButton()==pButtonEliminar){
        eliminar_archivo();
        msgBoxCarpetas.close();
    }
    else if(msgBoxCarpetas.clickedButton()==pButtonCopiar){
        copiar();
        msgBoxCarpetas.close();
    }
    else
        msgBoxCarpetas.close();
}

void MainWindow::on_btnAtras_clicked()
{
    Folder * temp = folderActual;
    if(folderActual->anterior!=NULL)
    {
        folderActual = folderActual->anterior;
        folderActual->siguiente = temp;
        refrescar();
    }
}

void MainWindow::on_btnAdelante_clicked()
{
    if(folderActual->siguiente != NULL)
    {
        folderActual = folderActual->siguiente;
        refrescar();
    }
}

void MainWindow::refrescar()
{
    for(int x = 0;x<listaBotones.size();x++)
    {
        listaBotones.at(x)->close();
        listaEtiquetas.at(x)->close();
    }

    for(int x = 0;x<listaBotones.size();x++)
    {
        listaBotones.removeAt(x);
        listaEtiquetas.removeAt(x);
    }
    cantBotones = 0;
    cantLabel = 0;
    posX = 170;
    posY = 70;

    QList <File*> listaTemp;
    listaTemp = fs->fsListarArchivos(folderActual);
    for(int x = 0; x < folderActual->cant;x++){
        if(listaTemp.at(x)->getTipo()==0)
            insertarArchivo(listaTemp.at(x)->getNombre());
        else
            insertarCarpeta(listaTemp.at(x)->getNombre());
    }
    ruta = folderActual->getDireccion();
    ui->lblRuta->setText(ruta.c_str());
}

void MainWindow::mouseDoubleClickEvent ( QMouseEvent * e )
{
    if ( e->button() == Qt::LeftButton)
    {

    }
}