#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMessageBox>
#include "filesystemutils.h"
#include <QMainWindow>
#include <QMenu>
#include <QMouseEvent>
#include <QTreeView>
#include <qlabel.h>
#include <qpushbutton.h>
#include "treemodel.h"
#include <QTreeWidget>
#include <QtCore>
#include <QtGui>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

private slots:
    void eliminar_archivo();
    void abrir_archivo();
    void leer_archivo();
    void editar_archivo();
    void refrescar();
    void eventoArchivos();
    void eventoCarpetas();
    string obtenerNodo();
    void copiar();
    void mouseDoubleClickEvent ( QMouseEvent * event );

    void agregarLabel(string nombre);
    void insertarCarpeta(string texto);
    void insertarArchivo(string texto);

    void on_btnNuevo_clicked();
    void on_btnAtras_clicked();
    void on_btnAdelante_clicked();
    void on_btnPegar_clicked();

private:
    Ui::MainWindow *ui;
    QTreeView * arbol;
    int cantBotones,cantLabel,posY, posX;
    string ruta;
    File * fileCopiar;
    QList<QPushButton*> listaBotones;
    QList<QLabel*> listaEtiquetas;

    QMessageBox msgBox;

    FileSystemUtils *fs;
    Folder * folderActual;
    Folder * raiz;
    QTreeWidgetItem * actual;

    QTreeWidgetItem * AddRoot(QTreeWidgetItem * parent,QString nombre);
    int AgregarItemCopy(Folder *raiz);



};

#endif // MAINWINDOW_H
