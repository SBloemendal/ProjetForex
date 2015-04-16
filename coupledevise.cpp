#include "coupledevise.h"

#include <QtSql/QSqlQuery>
#include <QDebug>


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

//void CoupleDevise::dessineCourbe(QGraphicsScene *scene)
//{
//    QSqlQuery query ("SELECT achat, heure, posX FROM COTATION WHERE nom='" + this->coupleDevise + "' AND jour=date('now') ORDER BY heure DESC LIMIT 2");
////    while (query.next())
////        qDebug() << query.value(1).toTime() ;

//    query.first() ;
//    int x (query.value(2).toInt()) ;
//    QTime heureDerniere = query.value(1).toTime() ;
//    query.next() ;
//    QTime heureAvantDerniere = query.value(1).toTime() ;

//    x += heureAvantDerniere.secsTo(heureDerniere) ;

//    query.first() ;
//    scene->addLine(x, 450-(query.value(0).toDouble())*100, x+(heureDerniere.secsTo(QTime::currentTime())), 450-valeurAchat.toDouble()*100) ;

//    x += heureDerniere.secsTo(QTime::currentTime()) ;

//    query.clear();

//    query.prepare("UPDATE COTATION SET posX=:posX WHERE id=last_insert_rowid() ") ;
//    query.bindValue(":posX", x);
//    query.exec() ;
//    query.clear();
//}
