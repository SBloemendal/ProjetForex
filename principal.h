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


/** \brief fichier h de la classe principal
 * \author Simon
 */

class principal : public QMainWindow
{
    Q_OBJECT

public:
    principal();
    bool creerBdd() ;

public slots:
    void recupereDonnees() ;

private slots:
    void setUrlChoixDevises(QString url) { urlChoixDevises = url ;}
    void setUrlFiltreDevises(QString url) { urlFiltreDevises = url ; }
    void connexionHttp() ;
    void choixCoupleDevises() ;
    void intervalleTemps() ;
    void simulationTransaction() ;
    void requeteGraph(QModelIndex index) ;
    void transactionAuto() ;
    void options() ;

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
};

bool readXmlFile( QIODevice& device, QSettings::SettingsMap& map );
bool writeXmlFile( QIODevice& device, const QSettings::SettingsMap& map );

#endif // PRINCIPAL_H

