/**
 * \file coupledevise.h
 * \brief Classe pour manipuler et enregistrer les valeurs récupérées depuis la requete HTTP.
 *
 * Les attributs de cette classe correspondent aux valeurs récupérées depuis le site FOREX.
 * Cela permet une manipulation plus aisée et permet notamment de comparer les valeurs récupérées
 * avec les dernières valeurs stockées dans la base de donnée (voir la méthode 'save').
 *
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

    /** Déclare la méthode 'recupereDonnees' de la classe 'Principal' comme amie
     * pour lui permettre d'acceder directement à tous les attributs de la classe 'CoupleDevise'.
     */
    friend void Principal::recupereDonnees() ;

    /** Permet de sauver les attributs dans la base de données.
     * Insere les valeurs de tous les attributs dans la base de donnée créée dans la classe 'principal'.
     * La méthode vérifie si les valeurs 'achat' et 'vente' récupérées ont changé depuis le dernier enregistrement
     * de la base de donnée, et crée un nouvel enregistrement uniquement si il y a eu changement.
     */
    bool save(QSqlDatabase* db) ;

private:
    QString coupleDevise ;
    QString valeurAchat ;
    QString valeurVente ;
    QString variation ;
};

#endif // COUPLEDEVISE_H
