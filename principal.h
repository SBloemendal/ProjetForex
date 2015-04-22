/**
 * \file principal.h
 * \author Simon
 * \version 1.0
 * \date 2015-04-27
 * \brief Fenetre principale de l'application.
 */


#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QApplication>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QSettings>
#include <QModelIndex>


class QWebView ;
class QSqlQueryModel ;
class QTableView ;


class principal : public QMainWindow
{
    Q_OBJECT

public:
    principal();
    bool creerBdd() ;
    void rafraichitSQLQueryModel() ;

public slots:
    void recupereDonnees() ;

private slots:
    void setUrlChoixDevises(QString url) { urlChoixDevises = url ; }
    void setUrlFiltreDevises(QString url) { urlFiltreDevises = url ; }
    void connexionHttp() ;
    void choixCoupleDevises() ;
    void intervalleTemps() ;
    void simulationTransaction() ;
    void requeteGraph(QModelIndex index) ;
    void transactionAuto() ;
    void options() ;
    void afficheGraphique();

private:
    QWebView* webView ;
    QWebView* graph ;
    QSqlQueryModel* modeleQ ;
    QTableView* tableView ;
    QSqlDatabase db ;
    QString urlPourModele ;
    QString urlChoixDevises ;
    QString urlFiltreDevises ;
    QString serveur ;
    QString nomBdd ;
    QString loginBdd ;
    QString passwordBdd ;
    QString urlForex ;
    int delaiTimer ;
};

bool readXmlFile( QIODevice& device, QSettings::SettingsMap& map );
bool writeXmlFile( QIODevice& device, const QSettings::SettingsMap& map );

#endif // PRINCIPAL_H

