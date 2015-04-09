#ifndef DIALOGUEOPTIONS_H
#define DIALOGUEOPTIONS_H

#include "principal.h"
#include <QDialog>

class QCheckBox ;

class DialogueOptions : public QDialog
{
    Q_OBJECT

public:
    DialogueOptions();
    ~DialogueOptions();

signals:
    QString dialogueFinis(QString);

public slots:
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

#endif // DIALOGUEOPTIONS_H
