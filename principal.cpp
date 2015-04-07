#include "principal.h"
#include "coupledevise.h"
#include "dialogchoixdevises.h"
#include <iostream>
#include <QDialog>
#include <QUrl>
#include <QtWidgets>
#include <QDebug>
#include <QWebElement>
#include <QWebPage>
#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QSqlQueryModel>
#include <QTableView>
#include <QTimer>
#include <QWebView>
#include <QWebFrame>

principal::principal() : nombreCouplesSelectionnes(0), urlChoixDevises("1;")
{
    // On crée la base de donnée et le modèle qui y sera attaché, et on initialise un webview
    creerBdd();
    modeleQ = new QSqlQueryModel ;
    modeleQ->setQuery("SELECT nom, achat, vente, variation, max(heure), jour FROM COTATION GROUP BY nom ORDER BY nom") ;

    // On lance la requete http et on lance le timer pour répéter la requete à intervalle régulier
    connexionHttp();
    QTimer* timerRequete = new QTimer();
    connect (timerRequete, SIGNAL(timeout()), this, SLOT(connexionHttp())) ;
    timerRequete->start(10000);


    // Design de la fenêtre principale
    setGeometry(400, 200, 800, 600);
    QMenuBar* barreDeMenu = menuBar() ;
    QMenu* menuFichier = barreDeMenu->addMenu("Fichier") ;
    QMenu* menuDevises = barreDeMenu->addMenu("Devises") ;
    menuFichier->addAction("Options", this, SLOT(options())) ;
    menuFichier->addAction("Quitter", qApp, SLOT(quit())) ;
    menuDevises->addAction("Choix des devises", this, SLOT(choixCoupleDevises())) ;
    menuDevises->addAction("Intervalle de temps", this, SLOT(intervalleTemps())) ;

    QVBoxLayout* layout = new QVBoxLayout() ;
    tableView = new QTableView(this) ;
    tableView->setModel(modeleQ);
    tableView->setGeometry(40,50,720,500);
    tableView->verticalHeader()->hide();
    tableView->setAlternatingRowColors(true);
    tableView->setShowGrid(false);
    tableView->verticalHeader()->setDefaultSectionSize(20);
    tableView->horizontalHeader()->setDefaultSectionSize(90);
    tableView->horizontalHeader()->setStretchLastSection(true);

    layout->addWidget(tableView);
}

void principal::options()
{


//            serveur
//            nom bdd
//            login
//            password
//            URL
//            list couples telecharge
}

void principal::choixCoupleDevises()
{
    dialogChoixDevises* choix = new dialogChoixDevises();
    connect(choix, SIGNAL(dialogueFinis(QString)), this, SLOT(setUrlChoixDevises(QString)));
    choix->exec();
    qDebug() << urlChoixDevises;
}

void principal::intervalleTemps()
{

}

void principal::connexionHttp()
{
    // Initialisation du webview avec la requete http
    webView = new QWebView(this);
    webView->hide();
    QString url = "http://fxrates.fr.forexprostools.com/index.php?force_lang=5&pairs_ids=" ;
    url += urlChoixDevises;
            //"1;3;2;4;9;6;10;11;13;12;" ;
    url += "&header-text-color=%23FFFFFF&curr-name-color=%230059b0&inner-text-color=%23000000&green-text-color=%232A8215&green-background=%23B7F4C2&red-text-color=%23DC0001&red-background=%23FFE2E2&inner-border-color=%23CBCBCB&border-color=%23cbcbcb&bg1=%23F6F6F6&bg2=%23ffffff&bid=show&ask=show&last=hide&open=hide&high=hide&low=hide&change=hide&last_update=show" ;
    webView->load(QUrl(url));
    connect (webView, SIGNAL(loadFinished(bool)), this, SLOT(recupereDonnees())) ;
    webView->close();
}

void principal::recupereDonnees()
{
    // Pour chaque couple de devises, on crée un objet 'CoupleDevise' et on y stocke les valeurs récupéré du web service
    // On accède aux valeurs par le biais des CSSselector grace à un QWebElement
    QWebElement element ;
    for (int i = 1 ; i < 14 ; i++){
        CoupleDevise couple ;
        element = webView->page()->mainFrame()->findFirstElement("tr#pair_" + QString::number(i) + " span.ftqa11bb") ; // CSSselector pour le nom du couple de devises
        couple.coupleDevise = element.toPlainText() ;
        element = webView->page()->mainFrame()->findFirstElement("tr#pair_" + QString::number(i) + ">td[class*=bid]") ; // CSSselector pour la valeur d'achat
        couple.valeurAchat = element.toPlainText() ;
        element = webView->page()->mainFrame()->findFirstElement("tr#pair_" + QString::number(i) + ">td[class*=ask]") ; // CSSselector pour la valeur de vente
        couple.valeurVente = element.toPlainText() ;
        element = webView->page()->mainFrame()->findFirstElement("tr#pair_" + QString::number(i) + ">td[class*=pcp]") ; // CSSselector pour le pourcentage de variation de la cotation
        couple.variation = element.toPlainText() ;
        element = webView->page()->mainFrame()->findFirstElement("tr#pair_" + QString::number(i) + ">td[class*=time]") ; // CSSselector pour l'heure de la cotation
        couple.heure = element.toPlainText() ;

        // Puis on demande a l'objet 'CoupleDevise' de se sauvegarder dans la bdd
        couple.save(&db) ;
    }
    // et on rafraichit le QSqlQuery et le QTableView
    modeleQ->query().exec();
    tableView->reset();
}

bool principal::creerBdd()
{
    db = QSqlDatabase::addDatabase( "QSQLITE") ;
    db.setDatabaseName("./bddForex.db");

    if (db.open()){                                         // Test si on a pu se connecter à la BDD
        qDebug() << "Connecté à la base de donnée" ;
        if (!db.tables().contains("COTATION")){             // Si la table COTATION n'existe pas, on la crée
            QString requeteSQL ;
            requeteSQL = "create table COTATION (id INTEGER PRIMARY KEY AUTOINCREMENT, nom varchar(10), achat double, vente double, variation double, heure time, jour date)";
            db.exec(requeteSQL) ;
            return true ;
        } else return true ;
    } else {
        qDebug() << "Pas de connexion à la base de donnée" ;
        return false ;
    }
}


//Pour ecrire la réponse dans un fichier
//    QFile fichier("bloat.txt") ;
//    fichier.write(repli->readAll()) ;
//    fichier.close();
//    fichier.open(QIODevice::ReadOnly) ;
//    QString htm = fichier.readAll() ;
//    fichier.close() ;
//    htm.remove(0,1) ;



