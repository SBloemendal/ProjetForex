#include "coupledevise.h"
#include <QtSql/QSqlQuery>
#include <QDebug>

/** On initialise tous les attributs à NULL à la création de l'objet.
 */
CoupleDevise::CoupleDevise() : coupleDevise(""), valeurAchat(""), valeurVente(""), variation("")
{

}


CoupleDevise::~CoupleDevise()
{

}


/** Insere les valeurs de tous les attributs dans la base de donnée créée dans la classe 'principal'.
 * La méthode vérifie si les valeurs 'achat' et 'vente' récupérées ont changé depuis le dernier enregistrement
 * de la base de donnée, et crée un nouvel enregistrement uniquement si il y a eu changement.
 */
bool CoupleDevise::save(QSqlDatabase* db)
{
    QSqlQuery query ;
    if(query.exec("select * from COTATION where nom='" + this->coupleDevise + "'"))
    {
        query.last(); // On compare les dernieres valeurs enregistrées dans la bdd avec celles de l'objet
        if (query.value(2).toString() == this->valeurAchat && query.value(3).toString() == this->valeurVente)
        {
            query.clear();
            return false ;
        } else {    // Si elles sont différentes, on enregistre les nouvelles valeurs
            if (db->tables().contains("COTATION"))
            {
                query.prepare("insert into COTATION (nom, achat, vente, variation, heure, jour) values (:nom, :achat, :vente, :variation, time('now','localtime'), date('now'))");
                query.bindValue(":nom", QVariant(this->coupleDevise));
                query.bindValue(":achat", QVariant(this->valeurAchat));
                query.bindValue(":vente", QVariant(this->valeurVente));
                query.bindValue(":variation", QVariant(this->variation));
                query.exec() ;
                query.clear();
                return true ;
            } else {
                query.clear();
                return false ;
            }
        }
    } else {
        query.clear();
        return false ;
    }
}
