/**
 * \file dialogchoixdevises.h
 * \brief Classe pour afficher la fenetre de choix d'affichage des couples de devises.
 *
 * Fenetre permettant à l'utilisateur de selectionner les couples de devises qu'il veut voir afficher dans
 * la fenetre principale. Ses choix sont immédiatement appliqués lorsqu'il appuie sur le bouton "Valider".
 * Ces choix n'affecte pas le stockage des données, seule l'affichage est modifiée : les couples de devises
 * décoché n'apparaissent plus dans la fenetre principale, mais continue d'etre stocké en temps réel dans la
 * base de donnée. Cela permet par exemple à l'utilisateur de se concentrer sur certaines cotations bien précises
 * tout en étant assuré qu'il bénéficiera toujours des valeurs en temps réel des autres cotations lorsqu'il voudra
 * les réafficher.
 *
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
    /** Signal émis lorsque l'utilisateur clique sur le bouton 'Valider'.
     *  Le signal est reçu par la fenetre principale qui met alors a jour
     *  la requete à la base de donnée en fonction des choix de l'utilisateur.
     */
    QString dialogueFinis(QString);

private slots:
    /** Lorsque l'utlisateur clique sur 'Valider', un QString est généré reflétant les choix de l'utilisateur concernant
     *  l'affichage des couples de devises. Puis la valeur de chaque parametre est enregistré dans un fichier XML. Le signal
     *  'dialoguefinis' est alors émis à l'attention de la classe 'Principal'.
     */
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
