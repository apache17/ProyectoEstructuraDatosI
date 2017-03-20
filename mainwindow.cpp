#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "editar.h"
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fs = new FileSystemUtils();
    raiz = new Folder("Raiz","Raiz/");
    raiz->item = NULL;
    folderActual = raiz;
    fileCopiar = NULL;
    ui->btnAtras->setStyleSheet("border-image: url(:/Imagenes/901 (1) - copia.png);");
    ui->btnAdelante->setStyleSheet("border-image: url(:/Imagenes/901 (1).png);");
    ui->btnPegar->hide();

    actual = NULL;
    refrescar();
}

QTreeWidgetItem * MainWindow::AddRoot(QTreeWidgetItem * parent,QString nombre)
{
    if(parent == NULL){
        QTreeWidgetItem * itm = new QTreeWidgetItem((ui->treeWidget));
        itm->setText(0,nombre);
        return itm;
    }
    else{
        QTreeWidgetItem * itm = new QTreeWidgetItem();
        itm->setText(0,nombre);
        parent->addChild(itm);
        return itm;
    }
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
    QMenu *menuMode = new QMenu(this);
    menuMode->addAction("Abrir",this, SLOT(abrir_archivo()));
    menuMode->addAction("Eliminar",this, SLOT(eliminar_archivo()));
    menuMode->addAction("Copiar",this, SLOT(copiar()));
    agregarLabel(texto);
    listaBotones.append(new QPushButton(this));
    listaBotones.at(cantBotones)->setObjectName(QString::fromStdString(texto));
    listaBotones.at(cantBotones)->setGeometry(QRect(QPoint(posX, posY),QSize(50, 50)));
    listaBotones.at(cantBotones)->setStyleSheet("border-image: url(:/Imagenes/Folders-PNG-File.png);");
    listaBotones.at(cantBotones)->show();
   //listaBotones.at(cantBotones)->setMenu(menuMode);
    connect(listaBotones.at(cantBotones), SIGNAL (released()),this, SLOT (eventoCarpetas()));
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
    File * temp = fs->fsCargarArchivo(obtenerNodo(),folderActual);
    if(temp->getTipo() == 0){
        TextFile* file = dynamic_cast<TextFile*>(temp);
        file->item->setHidden(true);
    }
    else{
        Folder* file = dynamic_cast<Folder*>(temp);
        file->item->setHidden(true);
    }
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

    actual = folderActual->item;
    refrescar();
}

void MainWindow::editar_archivo()
{

    File * temp = fs->fsCargarArchivo(obtenerNodo(),folderActual);
    TextFile* file = dynamic_cast<TextFile*>(temp);
    Editar * inp = new Editar("Editar Archivo","Ingrese el Texto",QString::fromStdString(file->getTexto()));
    inp->exec();


    file->setTexto(inp->getValor().toStdString());
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
    fileCopiar->setNombre(fs->fsDuplicados(fileCopiar->getNombre(),folderActual));
    fileCopiar->setDireccion(folderActual->getDireccion()+fileCopiar->getNombre()+"/");
    if(fileCopiar->getTipo() == 1)
    {
        Folder* folder = dynamic_cast<Folder*>(fileCopiar);
        folder->item = AddRoot(actual,QString::fromStdString(folder->getNombre()));
        fs->fsPegar(folder,folderActual);
        AgregarItemCopy(folder);
    }
    else
    {
        TextFile* txt = dynamic_cast<TextFile*>(fileCopiar);
        txt->item = AddRoot(actual,QString::fromStdString(txt->getNombre()));
        fs->fsPegar(txt,folderActual);
    }
    fileCopiar = NULL;
    ui->btnPegar->hide();
    refrescar();
}

int MainWindow::AgregarItemCopy(Folder *raiz)
{
    if(raiz->lista->inicio == NULL)
        return 0;
    else
    {
        File * temp = raiz->lista->inicio;
        for(int x = 0;raiz->cant > x;x++)
        {
            if(temp->getTipo() == 0){
                TextFile* file = dynamic_cast<TextFile*>(temp);
                file->item = AddRoot(raiz->item,QString::fromStdString(file->getNombre()));
            }
            else
            {
                Folder* folder = dynamic_cast<Folder*>(temp);
                folder->item = AddRoot(raiz->item,QString::fromStdString(folder->getNombre()));
                AgregarItemCopy(folder);
            }
            temp = temp->siguiente;
        }
    }
    return -1;
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
    QPixmap pixmap(":/Imagenes/Folders-PNG-File.png");
    QIcon buttonicon(pixmap);
    pButtonCarpeta->setIcon(buttonicon);

    QAbstractButton * pButtonArchivo = msgBoxNuevo.addButton(tr("Archivo"), QMessageBox::YesRole);
    QPixmap pixmap1(":/Imagenes/Docs-icon-iloveimg-resized.png");
    QIcon buttonicon1(pixmap1);
    pButtonArchivo->setIcon(buttonicon1);

    QAbstractButton * pButtonCancelar = msgBoxNuevo.addButton(tr("Cancelar"), QMessageBox::NoRole);
    QPixmap pixmap2(":/Imagenes/Cancel_Icon-128.png");
    QIcon buttonicon2(pixmap2);
    pButtonCancelar->setIcon(buttonicon2);

    msgBoxNuevo.exec();
    if(msgBoxNuevo.clickedButton()==pButtonCarpeta)
        nuevaCarpeta();
    else if(msgBoxNuevo.clickedButton()==pButtonArchivo)
        nuevoArchivo();

}

void MainWindow::nuevaCarpeta()
{
    QString x = QInputDialog::getText(this,"Nueva Carpeta","Ingrese el Nombre de la Carpeta:");
    string nombre = x.toStdString();
    nombre = fs->fsDuplicados(nombre,folderActual);
    if(x != "")
    {
        File * x = fs->fsCrearArchivo(folderActual,nombre,"Carpeta");
        Folder* folder = dynamic_cast<Folder*>(x);
        folder->item = AddRoot(actual,QString::fromStdString(nombre));
        insertarCarpeta(nombre);
    }
}

void MainWindow::nuevoArchivo()
{
    QString x = QInputDialog::getText(this,"Nuevo Archivo","Ingrese el Nombre del Archivo:");
    string nombre = x.toStdString();
    nombre = fs->fsDuplicados(nombre,folderActual);
    if(x != "")
    {
        File * x = fs->fsCrearArchivo(folderActual,nombre,"Archivo");
        TextFile * file = dynamic_cast<TextFile*>(x);
        file->item = AddRoot(actual,QString::fromStdString(nombre+".txt"));
        insertarArchivo(nombre);
    }
}

void MainWindow::eventoArchivos()
{
    QMessageBox msgBoxArchivos;
    msgBoxArchivos.setWindowTitle("File System Utils");
    msgBoxArchivos.setText(tr("Que desea hacer?"));
    QAbstractButton * pButtonAbrir = msgBoxArchivos.addButton(tr("Leer"), QMessageBox::YesRole);
    QPixmap pixmap(":/Imagenes/oYPS__file_document_enlarge_magnifier_magnify_examine_read_paper_page_text-512.png");
    QIcon buttonicon(pixmap);
    pButtonAbrir->setIcon(buttonicon);

    QAbstractButton * pButtonEditar = msgBoxArchivos.addButton(tr("Editar"), QMessageBox::YesRole);
    QPixmap pixmap4(":/Imagenes/pencil_and_paper-512.png");
    QIcon buttonicon4(pixmap4);
    pButtonEditar->setIcon(buttonicon4);

    QAbstractButton * pButtonEliminar = msgBoxArchivos.addButton(tr("Eliminar"), QMessageBox::YesRole);
    QPixmap pixmap3(":/Imagenes/remove-icon-png-24.png");
    QIcon buttonicon3(pixmap3);
    pButtonEliminar->setIcon(buttonicon3);

    QAbstractButton * pButtonCopiar = msgBoxArchivos.addButton(tr("Copiar"), QMessageBox::YesRole);
    QPixmap pixmap5(":/Imagenes/copying_copy_rip_backup_copy_duplication-512.png");
    QIcon buttonicon5(pixmap5);
    pButtonCopiar->setIcon(buttonicon5);

    QAbstractButton * pButtonCancelar = msgBoxArchivos.addButton(tr("Cancelar"), QMessageBox::NoRole);
    QPixmap pixmap2(":/Imagenes/Cancel_Icon-128.png");
    QIcon buttonicon2(pixmap2);
    pButtonCancelar->setIcon(buttonicon2);

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
    QPixmap pixmap(":/Imagenes/oYPS__file_document_enlarge_magnifier_magnify_examine_read_paper_page_text-512.png");
    QIcon buttonicon(pixmap);
    pButtonAbrir->setIcon(buttonicon);

    QAbstractButton * pButtonEliminar = msgBoxCarpetas.addButton(tr("Eliminar"), QMessageBox::YesRole);
    QPixmap pixmap3(":/Imagenes/remove-icon-png-24.png");
    QIcon buttonicon3(pixmap3);
    pButtonEliminar->setIcon(buttonicon3);

    QAbstractButton * pButtonCopiar = msgBoxCarpetas.addButton(tr("Copiar"), QMessageBox::YesRole);
    QPixmap pixmap5(":/Imagenes/copying_copy_rip_backup_copy_duplication-512.png");
    QIcon buttonicon5(pixmap5);
    pButtonCopiar->setIcon(buttonicon5);

    QAbstractButton * pButtonCancelar = msgBoxCarpetas.addButton(tr("Cancelar"), QMessageBox::NoRole);
    QPixmap pixmap2(":/Imagenes/Cancel_Icon-128.png");
    QIcon buttonicon2(pixmap2);
    pButtonCancelar->setIcon(buttonicon2);

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
        actual = folderActual->item;
        refrescar();
    }
}

void MainWindow::on_btnAdelante_clicked()
{
    if(folderActual->siguiente != NULL)
    {
        folderActual = folderActual->siguiente;
        actual = folderActual->item;
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
    posY = 80;

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
    if ( e->button() == Qt::RightButton)
    {

    }
}

void MainWindow::on_actionCarpeta_triggered()
{
    nuevaCarpeta();
}

void MainWindow::on_actionArchivo_triggered()
{
    nuevoArchivo();
}
