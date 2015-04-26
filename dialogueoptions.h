/**
 * \file dialogueoptions.h
 * \brief Classe pour afficher la fenetre d'options générales.
 *
 * Affiche une fenetre proposant de modifier les options de l'application, et
 * les stocke grace a un QSettings pour les rappeler lors de la prochaine
 * execution de l'application. Les paramètres de la base de donnée sont stocké immédiatement
 * mais les changements ne sont pris en compte qu'au redémarrage de l'application.
 * Les paramètres de choix du stockage des couples de devises sont pris en compte immédiatement.
 *
 */


#ifndef DIALOGUEOPTIONS_H
#define DIALOGUEOPTIONS_H

#include "principal.h"
#include <QDialog>

class QLineEdit ;
class QCheckBox ;
class QComboBox ;

class DialogueOptions : public QDialog
{
    Q_OBJECT

public:
    DialogueOptions();
    ~DialogueOptions();

signals:
    /** Signal émis lorsque l'utilisateur clique sur le bouton 'Valider'.
     *  Le signal est reçu par la fenetre principale qui met alors a jour
     *  l'URL de requete HTTP en fonction des choix de l'utilisateur.
     */
    QString dialogueFinis(QString);

private slots:
    /** Lorsque l'utlisateur clique sur 'Valider', une nouvelle URL est généré reflétant les choix de l'utilisateur concernant
     *  le stockage des couples de devises. Puis la valeur de chaque parametre est enregistré dans un fichier XML. Le signal
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
    QComboBox* delaiTimer ;
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
