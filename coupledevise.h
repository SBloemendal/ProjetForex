#ifndef COUPLEDEVISE_H
#define COUPLEDEVISE_H

#include <QObject>
#include <QString>
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
    void dessineCourbe(QGraphicsScene* scene) ;

private:
    QString coupleDevise ;
    QString valeurAchat ;
    QString valeurVente ;
    QString variation ;
    QString heure ;
};

#endif // COUPLEDEVISE_H
