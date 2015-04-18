/** \brief Classe pour manipuler et enregistrer les valeurs récupérées depuis la requete HTTP.
 *
 * Cette classe permet de stocker les valeurs récupérés par la méthode 'principal::recupereDonnees()'
 * en proposant un attribut pour chaque valeur récupérée, et une méthode 'save' pour les
 * sauvegarder dans la base de donnée.
 */


#ifndef COUPLEDEVISE_H
#define COUPLEDEVISE_H

#include <QObject>
#include "principal.h"

class QSqlDatabase ;


class CoupleDevise : public QObject
{
    Q_OBJECT

public:
    CoupleDevise();
    ~CoupleDevise();

    friend void principal::recupereDonnees() ;
    bool save(QSqlDatabase* db) ;

private:
    QString coupleDevise ;
    QString valeurAchat ;
    QString valeurVente ;
    QString variation ;
    QString heure ;
};

#endif // COUPLEDEVISE_H
