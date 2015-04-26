/**
 * \file dialogueintervalletemps.h
 * \brief Classe pour afficher la fenetre d'affichage de données dans un intervalle de temps.
 *
 * Fenetre permettant d'afficher toutes les valeurs d'un couple sélectionnée dans un intervalle de
 * temps donnée par l'utilisateur. Les données sont triées à l'affichage par date et par heure.
 * L'utilisateur peut ensuite les trier différemment grâce aux header de la QTableView mais perd
 * alors le tri double date et heure.
 *
 */


#ifndef DIALOGUEINTERVALLETEMPS_H
#define DIALOGUEINTERVALLETEMPS_H

#include "principal.h"
#include <QDialog>

class QSqlQueryModel ;
class QTableView ;
class QComboBox ;
class QLineEdit ;
class QDateEdit ;


class DialogueIntervalleTemps : public QDialog
{
    Q_OBJECT

public:
    DialogueIntervalleTemps();
    ~DialogueIntervalleTemps();

private slots:
    /** Génére la requete a la base de donnée en fonction des choix de l'utilisateur.
     *  concernant le couple et les dates d'intervalle. Le QTableView se met alors a jour.
     */
    void selectionChange();

private:
    QSqlQueryModel* modeleIT ;
    QTableView * tableView ;
    QComboBox* selection ;
    QDateEdit* dateDebut ;
    QDateEdit* dateFin ;
};

#endif // DIALOGUEINTERVALLETEMPS_H
