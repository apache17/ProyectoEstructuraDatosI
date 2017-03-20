#include "editar.h"
#include "ui_editar.h"

Editar::Editar(QString titulo,QString descripcion,QString valor) :

    ui(new Ui::Editar)
{
    ui->setupUi(this);
    this->setWindowTitle(titulo);
    ui->lblDescripcion->setText(descripcion);
    ui->textEdit->setText(valor);
    ui->pushButton->setStyleSheet("border-image: url(:/Imagenes/save-128.png);");


}

Editar::~Editar()
{
    delete ui;
}

QString Editar::getValor()
{
    return texto;
}

void Editar::on_pushButton_clicked()
{
    texto = ui->textEdit->toPlainText();
    this->close();
}

