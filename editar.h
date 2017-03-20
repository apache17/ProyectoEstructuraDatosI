#ifndef EDITAR_H
#define EDITAR_H

#include <QDialog>
#include <QString>
namespace Ui {
class Editar;
}

class Editar : public QDialog
{
    Q_OBJECT

public:
    explicit Editar(QString titulo,QString descripcion,QString valor);
    QString getValor();
    ~Editar();

private slots:
    void on_pushButton_clicked();


private:
    Ui::Editar *ui;
    QString texto;
};

#endif // EDITAR_H
