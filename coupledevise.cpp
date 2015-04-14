#include "coupledevise.h"
#include <QSqlDatabase>
#include <QVariant>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlRecord>
#include <QDebug>
#include <QGraphicsScene>

CoupleDevise::CoupleDevise() : coupleDevise(""), valeurAchat(""), valeurVente(""), variation(""), heure("")
{

}

CoupleDevise::~CoupleDevise()
{

}

bool CoupleDevise::save(QSqlDatabase* db)
{
    QSqlQuery query ;
    if(query.exec("select * from COTATION where nom='" + this->coupleDevise + "'"))
    {
        query.last();
        if (query.value(2).toString() == this->valeurAchat && query.value(3).toString() == this->valeurVente)
        {
            qDebug() << "Les valeurs n'ont pas changées." ;
            query.clear();
            return false ;
        } else {
            if (db->tables().contains("COTATION"))
            {
                query.prepare("insert into COTATION (nom, achat, vente, variation, heure, jour) values (:nom, :achat, :vente, :variation, time('now','localtime'), date('now'))");
                query.bindValue(":nom", QVariant(this->coupleDevise));
                query.bindValue(":achat", QVariant(this->valeurAchat));
                query.bindValue(":vente", QVariant(this->valeurVente));
                query.bindValue(":variation", QVariant(this->variation));
                //query.bindValue(":heure", QVariant(this->heure));
                query.exec() ;
                query.clear();
                return true ;
            } else {
                query.clear();
                qDebug() << "La table n'existent pas" ;
                return false ;
            }
        }
    } else {
        query.clear();
        qDebug() << "La requête n'a pas pu être executée" ;
        return false ;
    }
}

void CoupleDevise::dessineCourbe(QGraphicsScene *scene)
{
    QSqlQuery query ("SELECT achat, heure FROM COTATION WHERE nom='" + this->coupleDevise + "' AND jour=date('now') ORDER BY heure LIMIT ");
    while (query.next())
        qDebug() << query.value(1).toTime() ;



    scene->addLine(QLineF(50, 450-(query.value(0).toDouble()), 60, 450-valeurAchat.toDouble())) ;
}
