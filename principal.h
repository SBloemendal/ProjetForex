#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QtWidgets>
#include <QWidget>
#include <QMainWindow>
#include <QSqlDatabase>
#include <QDebug>

class QSettings ;
class QWebView ;
class QSqlQueryModel ;
class QTableView ;
class QGraphicsScene ;

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
    void setUrlChoixDevises(QString url) { urlChoixDevises = url ;}
    void setUrlFiltreDevises(QString url) { urlFiltreDevises = url ; }

private slots:
    void connexionHttp() ;
    void choixCoupleDevises() ;
    void intervalleTemps() ;
    void simulationTransaction() ;
    void options() ;

private:
    QWebView* webView ;
    QSqlDatabase db ;
    QSqlQueryModel* modeleQ ;
    QTableView* tableView ;
    QGraphicsScene* scene ;
    QGraphicsView* graphicsView ;
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

bool readXmlFile( QIODevice& device, QSettings::SettingsMap& map );
bool writeXmlFile( QIODevice& device, const QSettings::SettingsMap& map );
#endif // PRINCIPAL_H

