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
#include "xmlstream.h"

class QWebView ;
class QSqlQueryModel ;
class QTableView ;
class QHBoxLayout ;
class QVBoxLayout ;

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal();

    /** Crée une base de donnée si inexistente et s'y connecte */
    bool creerBdd() ;

    void rafraichitSQLQueryModel() ;

public slots:
    /** Récupère les valeurs des couples de cotations depuis la source HTML */
    void recupereDonnees() ;

private slots:
    inline void setUrlChoixDevises(QString url) { urlChoixDevises = url ; }
    inline void setUrlFiltreDevises(QString url) { urlFiltreDevises = url ; }
    void connexionHttp() ;
    void choixCoupleDevises() ;
    void intervalleTemps() ;
    void simulationTransaction() ;
    void requeteGraph(QModelIndex index) ;
    void transactionAuto() ;
    void options() ;
    void afficheGraphique();

private:
    QWidget *zoneCentrale ;
    QHBoxLayout* layout ;
    QVBoxLayout* layoutGauche ;
    QVBoxLayout* layoutDroit ;
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

#endif // PRINCIPAL_H

