#ifndef DIALOGCHOIXDEVISES_H
#define DIALOGCHOIXDEVISES_H

#include "principal.h"
#include <QDialog>

class QCheckBox ;

class dialogChoixDevises : public QDialog
{
    Q_OBJECT

public:
    dialogChoixDevises();
    ~dialogChoixDevises();

signals:
    QString dialogueFinis(QString);

private slots:
    void construitURL();

private:
    QString urlChoixCouples ;
    QCheckBox* cb1;
    QCheckBox* cb2;
    QCheckBox* cb3;
    QCheckBox* cb4;
    QCheckBox* cb5;
    QCheckBox* cb6;
    QCheckBox* cb7;
    QCheckBox* cb8;
    QCheckBox* cb9;
    QCheckBox* cb10;
};

#endif // DIALOGCHOIXDEVISES_H
