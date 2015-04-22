/**
 * \file coupledevise.h
 * \author Simon
 * \version 1.0
 * \date 2015-04-27
 * \brief Classe pour manipuler et enregistrer les valeurs récupérées depuis la requete HTTP.
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

    /** Permet de sauver les attributs dans la base de données */
    bool save(QSqlDatabase* db) ;

private:
    QString coupleDevise ;
    QString valeurAchat ;
    QString valeurVente ;
    QString variation ;
};

#endif // COUPLEDEVISE_H
