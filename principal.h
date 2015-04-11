#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QWidget>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>

class QSettings ;
class QWebView ;
class QSqlQueryModel ;
class QTableView ;

class principal : public QMainWindow
{
    Q_OBJECT

public:
    principal();

    bool creerBdd() ;

public slots:
    void recupereDonnees() ;
    void setUrlChoixDevises(QString url) { urlChoixDevises = url ;}
    void setUrlFiltreDevises(QString url) { urlFiltreDevises = url ; }

private slots:
    void connexionHttp() ;
    void choixCoupleDevises() ;
    void intervalleTemps() ;
    void options() ;

private:
    QWebView* webView ;
    QSqlDatabase db ;
    QSqlQueryModel* modeleQ ;
    QTableView* tableView ;
    int nombreCouplesSelectionnes ;
    QString urlPourModele ;
    QString urlChoixDevises ;
    QString urlFiltreDevises ;
    QString serveur ;
    QString nomBdd ;
    QString loginBdd ;
    QString passwordBdd ;
    QString urlForex ;
};

#endif // PRINCIPAL_H


