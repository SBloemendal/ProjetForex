/**
 * \file dialogchoixdevises.h
 * \author Simon
 * \version 1.0
 * \date 2015-04-27
 * \brief Classe pour afficher la fenetre de choix d'affichage des couples de devises.
 */


#ifndef DIALOGUECHOIXDEVISES_H
#define DIALOGUECHOIXDEVISES_H

#include "principal.h"
#include <QDialog>

class QLineEdit ;
class QCheckBox ;


class DialogueChoixDevises : public QDialog
{
    Q_OBJECT

public:
    DialogueChoixDevises();
    ~DialogueChoixDevises();

signals:
    QString dialogueFinis(QString);

private slots:
    /** Enregistre les valeurs choisies par l'utilisateur */
    void enregistreValeurs();

private:
    QString urlChoixCouples ;
    QLineEdit* serveur ;
    QLineEdit* nomBdd ;
    QLineEdit* loginBdd ;
    QLineEdit* passwordBdd ;
    QLineEdit* urlForex ;
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

#endif // DIALOGUECHOIXDEVISES_H
