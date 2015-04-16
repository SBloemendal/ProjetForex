#include "principal.h"
#include "coupledevise.h"
#include "dialogchoixdevises.h"
#include "dialogueoptions.h"
#include "dialogueintervalletemps.h"
#include "dialoguesimulationtransactions.h"
#include "dialoguetransactionautomatique.h"

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

/**
 * \file principal.cpp
 * \author Simon
 * \version 1.6
 * \date 2015-04-13
 * \brief Classe principale qui affiche la fenetre principale dans laquelle est affichee la liste des valeurs en temps reel.
 * \todo ameliorer la boucle de recuperation des donnes html, utiliser un tableau[i]
 */

principal::principal() : nombreCouplesSelectionnes(0)
{
    QSettings::Format XmlFormat = QSettings::registerFormat("xml", readXmlFile, writeXmlFile);
    QSettings::setPath(XmlFormat, QSettings::UserScope,QDir::currentPath());
    QSettings settings(XmlFormat, QSettings::UserScope, "CCI Colmar", "ProjetForex_SB");
    //settings.clear();

    urlFiltreDevises = settings.value("afficherDevises/urlchoixCouples", "WHERE jour=date('now')").toString() ;
    urlChoixDevises = settings.value("choixDevises/urlChoixCouples", "1; 2; 3; 4; 6; 9; 10; 11; 12; 13;").toString() ;
    serveur = settings.value("choixDevises/serveur", "127.0.0.1").toString();
    nomBdd = settings.value("choixDevises/nomBdd", "bddForex.db").toString() ;
    loginBdd = settings.value("choixDevises/loginBdd", "admin").toString() ;
    passwordBdd = settings.value("choixDevises/passwordBdd", "admin").toString() ;
    urlForex = settings.value("choixDevises/urlForex", "http://fxrates.investing.com").toString() ; //http://fxrates.fr.forexprostools.com

    // On crée la base de donnée et le modèle qui y sera attaché, le modèle graphique, et on initialise un webview
    creerBdd() ;
    modeleQ = new QSqlQueryModel ;
    modeleQ->setQuery("SELECT nom, achat, vente, variation, max(heure) AS 'Heure', jour FROM COTATION " + urlFiltreDevises + " GROUP BY nom ORDER BY nom") ;

    webView = new QWebView(this);
    webView->hide();
    connect (webView, SIGNAL(loadFinished(bool)), this, SLOT(recupereDonnees())) ;

    // On lance la requete http et on lance le timer pour répéter la requete à intervalle régulier
    connexionHttp();
//    QTimer* timerRequete = new QTimer();
//    connect (timerRequete, SIGNAL(timeout()), this, SLOT(connexionHttp())) ;
//    timerRequete->start(10000);


    // Design de la fenêtre principale
    QWidget *zoneCentrale = new QWidget;

    setGeometry(400, 200, 1400, 580);

    QMenuBar* barreDeMenu = menuBar() ;
    QMenu* menuFichier = barreDeMenu->addMenu("Système") ;
    QMenu* menuDevises = barreDeMenu->addMenu("Affichage") ;
    menuFichier->addAction("Options", this, SLOT(options())) ;
    menuFichier->addAction("Quitter", qApp, SLOT(quit())) ;
    menuDevises->addAction("Choix d'affichage", this, SLOT(choixCoupleDevises())) ;
    menuDevises->addAction("Par intervalle de temps", this, SLOT(intervalleTemps())) ;
    menuDevises->addAction("Simulation de transactions", this, SLOT(simulationTransaction())) ;
    menuDevises->addAction("Transactions automatiques", this, SLOT(transactionAuto())) ;

    QHBoxLayout* layout = new QHBoxLayout;

    tableView = new QTableView(this);
    tableView->setModel(modeleQ);
    tableView->setAlternatingRowColors(true);
    tableView->verticalHeader()->hide();
    tableView->setShowGrid(false);
    tableView->verticalHeader()->setDefaultSectionSize(20);
    tableView->horizontalHeader()->setDefaultSectionSize(90);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->setSortingEnabled(true);
    connect (tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(requeteGraph(QModelIndex))) ;

    graph = new QWebView ;
    graph->load(QUrl("http://charts.investing.com/index.php?pair_ID=1&timescale=300&candles=50&style=line"));


    layout->addWidget(tableView);
    layout->addWidget(graph);
    zoneCentrale->setLayout(layout);

    setCentralWidget(zoneCentrale);
}

void principal::requeteGraph(QModelIndex index)
{
    int choix ;
    qDebug() << index.data(Qt::DisplayRole).toString() ;
    if (index.data(Qt::DisplayRole).toString() == "EUR/USD")
            choix = 1 ;
    if (index.data(Qt::DisplayRole).toString() == "GBP/USD")
            choix = 2 ;
    if (index.data(Qt::DisplayRole).toString() == "USD/JPY")
            choix = 3 ;
    if (index.data(Qt::DisplayRole).toString() == "USD/CHF")
            choix = 4 ;
    if (index.data(Qt::DisplayRole).toString() == "EUR/GBP")
            choix = 6 ;
    if (index.data(Qt::DisplayRole).toString() == "EUR/JPY")
            choix = 9 ;
    if (index.data(Qt::DisplayRole).toString() == "EUR/CHF")
            choix = 10 ;
    if (index.data(Qt::DisplayRole).toString() == "GBP/JPY")
            choix = 11 ;
    if (index.data(Qt::DisplayRole).toString() == "CHF/JPY")
            choix = 12 ;
    if (index.data(Qt::DisplayRole).toString() == "GBP/CHF")
            choix = 13 ;

    graph->load(QUrl("http://charts.investing.com/index.php?pair_ID=" + QString::number(choix) + "&timescale=300&candles=50&style=line")) ;
}

void principal::transactionAuto()
{
    DialogueTransactionAutomatique* transaction = new DialogueTransactionAutomatique ;
    transaction->exec();
}

void principal::options()
{
    DialogueOptions* options = new DialogueOptions ;
    connect(options, SIGNAL(dialogueFinis(QString)), this, SLOT(setUrlChoixDevises(QString)));
    options->exec();
    recupereDonnees();
}

void principal::choixCoupleDevises()
{
    dialogChoixDevises* choix = new dialogChoixDevises;
    connect(choix, SIGNAL(dialogueFinis(QString)), this, SLOT(setUrlFiltreDevises(QString)));
    choix->exec();
    recupereDonnees();
}

void principal::simulationTransaction()
{
    DialogueSimulationTransactions* simulation = new DialogueSimulationTransactions;
    simulation->exec();
}

void principal::intervalleTemps()
{
    DialogueIntervalleTemps* fenetreIntervalTemps = new DialogueIntervalleTemps ;
    fenetreIntervalTemps->exec();
}

void principal::connexionHttp()
{
    // Initialisation du webview avec la requete http

    QString url = urlForex + "/index.php?force_lang=5&pairs_ids=" ;
    url += urlChoixDevises;
    url += "&header-text-color=%23FFFFFF&curr-name-color=%230059b0&inner-text-color=%23000000&green-text-color=%232A8215&green-background=%23B7F4C2&red-text-color=%23DC0001&red-background=%23FFE2E2&inner-border-color=%23CBCBCB&border-color=%23cbcbcb&bg1=%23F6F6F6&bg2=%23ffffff&bid=show&ask=show&last=hide&open=hide&high=hide&low=hide&change=hide&last_update=show" ;
    webView->load(QUrl(url));

    recupereDonnees();
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
    // et on rafraichit le QSqlQuery
    urlPourModele = "SELECT nom, achat, vente, variation, max(heure) AS 'Heure', jour FROM COTATION " + urlFiltreDevises + " GROUP BY nom ORDER BY nom" ;
    modeleQ->setQuery(urlPourModele) ;
}

bool principal::creerBdd()
{
    db = QSqlDatabase::addDatabase( "QSQLITE") ;
    //db.setHostName(serveur);
    db.setDatabaseName("./" + nomBdd);
    //db.setUserName(loginBdd);
    //db.setPassword(passwordBdd);

    if (db.open()){                                         // Test si on a pu se connecter à la BDD
        qDebug() << "Connecté à la base de donnée" ;
        if (!db.tables().contains("COTATION")){             // Si la table COTATION n'existe pas, on la crée
            QString requeteSQL ;
            requeteSQL = "create table COTATION (id INTEGER PRIMARY KEY AUTOINCREMENT, nom varchar(10), achat double, vente double, variation double, heure time, jour date, posX int)";
            db.exec(requeteSQL) ;
            return true ;
        } else return true ;
    } else {
        qDebug() << "Pas de connexion à la base de donnée" ;
        return false ;
    }
}


bool readXmlFile(QIODevice &device, QSettings::SettingsMap &map) {
  QXmlStreamReader xmlReader(&device);
  QStringList elements;

  // Solange Ende nicht erreicht und kein Fehler aufgetreten ist
  while (!xmlReader.atEnd() && !xmlReader.hasError()) {
    // Nächsten Token lesen
    xmlReader.readNext();

    // Wenn Token ein Startelement
    if (xmlReader.isStartElement() && xmlReader.name() != "Settings") {
      // Element zur Liste hinzufügen
      elements.append(xmlReader.name().toString());
    // Wenn Token ein Endelement
    } else if (xmlReader.isEndElement()) {
      // Letztes Element löschen
      if(!elements.isEmpty()) elements.removeLast();
    // Wenn Token einen Wert enthält
    } else if (xmlReader.isCharacters() && !xmlReader.isWhitespace()) {
      QString key;

      // Elemente zu String hinzufügen
      for(int i = 0; i < elements.size(); i++) {
        if(i != 0) key += "/";
        key += elements.at(i);
      }

      // Wert in Map eintragen
      map[key] = xmlReader.text().toString();
    }
  }

  // Bei Fehler Warnung ausgeben
  if (xmlReader.hasError()) {
    qWarning() << xmlReader.errorString();
    return false;
  }

  return true;
}

bool writeXmlFile(QIODevice &device, const QSettings::SettingsMap &map) {
  QXmlStreamWriter xmlWriter(&device);

  xmlWriter.setAutoFormatting(true);
  xmlWriter.writeStartDocument();
  xmlWriter.writeStartElement("Settings");

  QStringList prev_elements;
  QSettings::SettingsMap::ConstIterator map_i;

  // Alle Elemente der Map durchlaufen
  for (map_i = map.begin(); map_i != map.end(); map_i++) {

    QStringList elements = map_i.key().split("/");

    int x = 0;
    // Zu schließende Elemente ermitteln
    while(x < prev_elements.size() && elements.at(x) == prev_elements.at(x)) {
      x++;
    }

    // Elemente schließen
    for(int i = prev_elements.size() - 1; i >= x; i--) {
      xmlWriter.writeEndElement();
    }

    // Elemente öffnen
    for (int i = x; i < elements.size(); i++) {
      xmlWriter.writeStartElement(elements.at(i));
    }

    // Wert eintragen
    xmlWriter.writeCharacters(map_i.value().toString());

    prev_elements = elements;
  }

  // Noch offene Elemente schließen
  for(int i = 0; i < prev_elements.size(); i++) {
    xmlWriter.writeEndElement();
  }

  xmlWriter.writeEndElement();
  xmlWriter.writeEndDocument();

  return true;
}



//bool readXmlFile( QIODevice& device, QSettings::SettingsMap& map )
//{
//    QXmlStreamReader xmlReader( &device );

//    QString currentElementName;
//    while( !xmlReader.atEnd() )
//    {
//        xmlReader.readNext();
//        while( xmlReader.isStartElement() )
//        {
//            if( xmlReader.name() == "SettingsMap" )
//            {
//                                xmlReader.readNext();
//                continue;
//            }

//            if( !currentElementName.isEmpty() )
//            {
//                currentElementName += "/";
//            }
//            currentElementName += xmlReader.name().toString();
//            xmlReader.readNext();
//        }

//        if( xmlReader.isEndElement() )
//        {
//            continue;
//        }

//        if( xmlReader.isCharacters() && !xmlReader.isWhitespace() )
//        {
//            QString key = currentElementName;
//            QString value = xmlReader.text().toString();

//            map[ key ] = value;

//            currentElementName.clear();
//        }
//    }

//     if( xmlReader.hasError() )
//     {
//        return false;
//     }

//    return true;
//}

//bool writeXmlFile( QIODevice& device, const QSettings::SettingsMap& map )
//{
//    QXmlStreamWriter xmlWriter( &device );
//    xmlWriter.setAutoFormatting( true );

//    xmlWriter.writeStartDocument();
//        xmlWriter.writeStartElement( "SettingsMap" );

//    QSettings::SettingsMap::const_iterator mi = map.begin();
//    for( mi; mi != map.end(); ++mi )
//    {
//        QString string (mi.key().toStdString().c_str());
//        QStringList groups = string.split("/");

//        foreach( QString groupName, groups )
//        {
//            xmlWriter.writeStartElement( groupName );
//        }

//        xmlWriter.writeCharacters( mi.value().toString() );

//        foreach( QString groupName, groups )
//        {
//            xmlWriter.writeEndElement();
//        }
//    }

//    xmlWriter.writeEndElement();
//    xmlWriter.writeEndDocument();

//    return true;
//}

//bool writeXmlFile( QIODevice& device, const QSettings::SettingsMap& map )
//{
//    QXmlStreamWriter xmlWriter( &device );
//    xmlWriter.setAutoFormatting( true );

//    xmlWriter.writeStartDocument();
//    xmlWriter.writeStartElement( "SettingsMap" );

//    QString AncienGrp ("");

//    QSettings::SettingsMap::const_iterator mi = map.begin();
//    for( mi; mi != map.end(); ++mi )
//    {
//        QString string (mi.key().toStdString().c_str());
//        QStringList groups = string.split("/");
//        if (groups.at(0) != AncienGrp)
//        {
//            if (AncienGrp != "")
//                xmlWriter.writeEndElement();
//            foreach( QString groupName, groups )
//            {
//                    xmlWriter.writeStartElement( groupName );
//            }

//            xmlWriter.writeCharacters( mi.value().toString() );

//            xmlWriter.writeEndElement();
//            AncienGrp = groups.at(0) ;
//        }
//        else
//        {
//            xmlWriter.writeStartElement(groups.at(1));
//            xmlWriter.writeCharacters( mi.value().toString() );
//            xmlWriter.writeEndElement();
//        }
//    }
//    xmlWriter.writeEndElement();

//    xmlWriter.writeEndElement();
//    xmlWriter.writeEndDocument();

//    return true;
//}

