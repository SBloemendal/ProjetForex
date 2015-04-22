#include "principal.h"
#include "coupledevise.h"
#include "dialogchoixdevises.h"
#include "dialogueoptions.h"
#include "dialogueintervalletemps.h"
#include "dialoguesimulationtransactions.h"
#include "dialoguetransactionautomatique.h"
#include <QWebElement>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>
#include <QTableView>
#include <QTimer>
#include <QWebView>
#include <QWebFrame>
#include <QDir>
#include <QMenuBar>
#include <QBoxLayout>
#include <QHeaderView>
#include <QXmlStreamReader>
#include <QGraphicsEffect>
#include <QPushButton>
#include <QSortFilterProxyModel>


/** Affiche une vue des valeurs les plus récentes des couples de devises sélectionnés,
 * et un graphique de l'évolution d'un couple de devises sélectionné.
 * A l'initialisation, crée une base de donnée SQLite, envoie une requète HTTP au site du Forex,
 * récupère les infos dans la réponse du Forex et les stocke dans la base de donnée pour les afficher
 * dans l'affichage principale.
 */
principal::principal()
{
    // On crée un QSettings
    QSettings::Format XmlFormat = QSettings::registerFormat("xml", readXmlFile, writeXmlFile);
    QSettings::setPath(XmlFormat, QSettings::UserScope,QDir::currentPath());
    QSettings settings(XmlFormat, QSettings::UserScope, "CCI Colmar", "ProjetForex_SB");
    //settings.clear(); // Remet tous les paramètres à leur valeur par défaut

    // Initialisation des attributs avec le QSettings
    //
    urlFiltreDevises = settings.value("afficherDevises/urlchoixCouples", "WHERE jour=date('now')").toString() ;
    urlChoixDevises = settings.value("Options/urlChoixCouples", "1; 2; 3; 4; 6; 9; 10; 11; 12; 13;").toString() ;
    serveur = settings.value("Options/serveur", "127.0.0.1").toString();
    nomBdd = settings.value("Options/nomBdd", "bddForex.db").toString() ;
    loginBdd = settings.value("Options/loginBdd", "admin").toString() ;
    passwordBdd = settings.value("Options/passwordBdd", "admin").toString() ;
    urlForex = settings.value("Options/urlForex", "http://fxrates.investing.com").toString() ; //http://fxrates.fr.forexprostools.com pour le site francais
    delaiTimer = settings.value("Options/timer", 10000).toInt() ;

    // On crée la base de donnée et le modèle qui la lira,
    // on crée aussi un modele de filtre qui sera placé entre le modele
    // et la vue.
    // Et on initialise un webview qui enverra la requete HTTP
    //
    creerBdd() ;
    modeleQ = new QSqlQueryModel ;
    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel;
    proxyModel->setSourceModel( modeleQ );
    rafraichitSQLQueryModel();

    webView = new QWebView(this);
    webView->hide();
    connect (webView, SIGNAL(loadFinished(bool)), this, SLOT(recupereDonnees())) ;

    // On lance la requete http et on lance le timer
    // pour répéter la requete à intervalle régulier
    //
    connexionHttp();
    QTimer* timerRequete = new QTimer();
    connect (timerRequete, SIGNAL(timeout()), this, SLOT(connexionHttp())) ;
    timerRequete->start(delaiTimer);


    // Design de la fenêtre principale
    //
    zoneCentrale = new QWidget;

    // Barre de menu
    QMenuBar* barreDeMenu = menuBar() ;
    QMenu* menuFichier = barreDeMenu->addMenu("Système") ;
    QMenu* menuDevises = barreDeMenu->addMenu("Affichage") ;
    menuFichier->addAction("Options", this, SLOT(options())) ;
    menuFichier->addAction("Quitter", qApp, SLOT(quit())) ;
    menuDevises->addAction("Choix d'affichage", this, SLOT(choixCoupleDevises())) ;
    menuDevises->addAction("Affichage des courbes", this, SLOT(afficheGraphique())) ;
    menuDevises->addAction("Par intervalle de temps", this, SLOT(intervalleTemps())) ;
    menuDevises->addAction("Simulation de transactions", this, SLOT(simulationTransaction())) ;
    menuDevises->addAction("Transactions automatiques", this, SLOT(transactionAuto())) ;

    // Le tableview qui affichera les cotations en temps réel
    tableView = new QTableView(this);
    tableView->setModel(proxyModel);
    tableView->verticalHeader()->hide();
    tableView->setShowGrid(false);
    tableView->setSortingEnabled(true);
    tableView->sortByColumn(0, Qt::AscendingOrder);
    tableView->verticalHeader()->setDefaultSectionSize(20);
    tableView->horizontalHeader()->setDefaultSectionSize(80);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setMinimumSize(500,400);
    connect (tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(requeteGraph(QModelIndex))) ;

    // Le graphique de courbes qui affichera les valeurs du couple de devises sélectionné.
    graph = new QWebView ;
    graph->hide();
    graph->load(QUrl("http://charts.investing.com/index.php?pair_ID=1&timescale=300&candles=50&style=line"));
    graph->setMinimumSize(500,400);

    // Les boutons permettant d'accéder aux différentes fonctions de l'application
    QPushButton* boutonGraph = new QPushButton("Graphique");
    connect (boutonGraph, SIGNAL(clicked()), this, SLOT(afficheGraphique()));
    QPushButton* boutonInterval = new QPushButton("Intervalle");
    connect (boutonInterval, SIGNAL(clicked()), this, SLOT(intervalleTemps()));
    QPushButton* boutonSimulation = new QPushButton("Simulation");
    connect (boutonSimulation, SIGNAL(clicked()), this, SLOT(simulationTransaction()));
    QPushButton* boutonTransaction = new QPushButton("Transaction");
    connect (boutonTransaction, SIGNAL(clicked()), this, SLOT(transactionAuto()));

    // On place le tout dans des layouts
    QHBoxLayout* layoutBoutons = new QHBoxLayout;
    layoutBoutons->addWidget(boutonGraph);
    layoutBoutons->addWidget(boutonInterval);
    layoutBoutons->addWidget(boutonSimulation);
    layoutBoutons->addWidget(boutonTransaction);
    QVBoxLayout* layoutGauche = new QVBoxLayout;
    layoutGauche->addWidget(tableView);
    layoutGauche->addLayout(layoutBoutons);
    layoutGauche->addStretch();
    QVBoxLayout* layoutDroit = new QVBoxLayout;
    layoutDroit->addWidget(graph);
    layoutDroit->addStretch();
    QHBoxLayout* layout = new QHBoxLayout;
    layout->addLayout(layoutGauche);
    layout->addLayout(layoutDroit);
    layout->addStretch(1);
    zoneCentrale->setLayout(layout);
    setCentralWidget(zoneCentrale);

    // Et on rajoute quelques effets graphiques
    QGraphicsOpacityEffect* effetTransparent = new QGraphicsOpacityEffect;
    effetTransparent->setOpacity(0.85);
    QGraphicsDropShadowEffect * dse = new QGraphicsDropShadowEffect();
    dse->setBlurRadius(10);
    dse->setOffset(4);
    qApp->setStyleSheet("QMainWindow { background-image: url(Uk-Forex1.png); }");
    tableView->setStyleSheet("background-color: transparent");
    tableView->setGraphicsEffect(dse);
    graph->setStyleSheet("background-color: transparent");
    graph->setGraphicsEffect(effetTransparent);
}



/** Permet d'afficher ou de masquer
 * le graphique de courbes
 * dans la fenêtre principale
 */
void principal::afficheGraphique()
{
    if (graph->isVisible())
    {
        graph->hide();
        zoneCentrale->resize(500,400);
        this->adjustSize();
    } else graph->show();
}



/** Selection du couple de devises a afficher
 * dans le graphique de la fenetre principale.
 * On récupère l'index de la ligne cliquée par
 * l'utilisateur pour savoir quel couple afficher.
 */
void principal::requeteGraph(QModelIndex index)
{
    int choix ;
    int row = index.row();

    // On récupère la valeur de la 1ere case de la ligne cliquée
    // pour savoir quelle couple de devises il faut afficher
    // dans le graphique de courbes.
    if (index.sibling(row,0).data(Qt::DisplayRole).toString() == "EUR/USD")
            choix = 1 ;
    if (index.sibling(row,0).data(Qt::DisplayRole).toString() == "GBP/USD")
            choix = 2 ;
    if (index.sibling(row,0).data(Qt::DisplayRole).toString() == "USD/JPY")
            choix = 3 ;
    if (index.sibling(row,0).data(Qt::DisplayRole).toString() == "USD/CHF")
            choix = 4 ;
    if (index.sibling(row,0).data(Qt::DisplayRole).toString() == "EUR/GBP")
            choix = 6 ;
    if (index.sibling(row,0).data(Qt::DisplayRole).toString() == "EUR/JPY")
            choix = 9 ;
    if (index.sibling(row,0).data(Qt::DisplayRole).toString() == "EUR/CHF")
            choix = 10 ;
    if (index.sibling(row,0).data(Qt::DisplayRole).toString() == "GBP/JPY")
            choix = 11 ;
    if (index.sibling(row,0).data(Qt::DisplayRole).toString() == "CHF/JPY")
            choix = 12 ;
    if (index.sibling(row,0).data(Qt::DisplayRole).toString() == "GBP/CHF")
            choix = 13 ;

    graph->load(QUrl("http://charts.investing.com/index.php?pair_ID=" + QString::number(choix) + "&timescale=300&candles=50&style=line")) ;
}



/** Ouvre une fenetre 'Transaction automatique'
 */
void principal::transactionAuto()
{
    DialogueTransactionAutomatique* transaction = new DialogueTransactionAutomatique ;
    transaction->exec();
}



/** Ouvre une fenetre 'Options systeme'
 */
void principal::options()
{
    DialogueOptions* options = new DialogueOptions ;
    // Lorsque la fenetre emet ce signal, on stocke les choix utilisateurs dans la variable urlChoixDevise
    connect(options, SIGNAL(dialogueFinis(QString)), this, SLOT(setUrlChoixDevises(QString)));
    options->exec();
}



/** Ouvre la fenetre d'option 'Choix d'affichage des couples de devises'
 */
void principal::choixCoupleDevises()
{
    dialogChoixDevises* choix = new dialogChoixDevises;
    // Lorsque la fenetre emet ce signal, on stocke les choix utilisateurs dans la variable urlFiltreDevise
    connect(choix, SIGNAL(dialogueFinis(QString)), this, SLOT(setUrlFiltreDevises(QString)));
    choix->exec();
    // Et on reactualise le modele avec les nouveaux choix
    rafraichitSQLQueryModel();
}



/** Ouvre une fenetre de dialogue 'simulation de transaction'
 */
void principal::simulationTransaction()
{
    DialogueSimulationTransactions* simulation = new DialogueSimulationTransactions;
    simulation->exec();
}



/** Ouvre une fenetre de dialogue 'Choix d'intervalle de temps'
 */
void principal::intervalleTemps()
{
    DialogueIntervalleTemps* fenetreIntervalTemps = new DialogueIntervalleTemps ;
    fenetreIntervalTemps->exec();
}



/** Envoi de la requette HTTP par l'intermédiaire du QWebView.
 * La variable 'urlForex' contient l'adresse du site saisie par l'utilisateur,
 * définie dans 'DialogueOptions'.
 * La variable 'urlChoixDevises' contient les couples de devises selectionnées dans les options,
 * définie dans 'DialogueOptions'.
 */
void principal::connexionHttp()
{
    QString url = urlForex + "/index.php?force_lang=5&pairs_ids=" ;
    url += urlChoixDevises;
    url += "&header-text-color=%23FFFFFF&curr-name-color=%230059b0&inner-text-color=%23000000&green-text-color=%232A8215&green-background=%23B7F4C2&red-text-color=%23DC0001&red-background=%23FFE2E2&inner-border-color=%23CBCBCB&border-color=%23cbcbcb&bg1=%23F6F6F6&bg2=%23ffffff&bid=show&ask=show&last=hide&open=hide&high=hide&low=hide&change=hide&last_update=show" ;
    webView->load(QUrl(url));
    webView->close();
}


/** Fonction pour recuperer les données de la requete HTTP
 * Pour chaque couple de devises, on crée un objet 'CoupleDevise'
 * et on y stocke les valeurs récupéré du web service.
 * On accède aux valeurs par le biais des CSSselector grace à un QWebElement
 */
void principal::recupereDonnees()
{
    QWebElement element ;

    // On parse 'urlChoixDevises' pour savoir sur quel couple de devises il faut boucler
    QStringList listeCouples ;
    listeCouples = urlChoixDevises.split(";");
    listeCouples.removeLast();
    listeCouples.replaceInStrings(" ", "");

    // Boucle pour recuperer les valeurs pour chaque couple de devises
    foreach (QString index, listeCouples) {
        CoupleDevise couple ;
        element = webView->page()->mainFrame()->findFirstElement("tr#pair_" + index + " span.ftqa11bb") ; // CSSselector pour le nom du couple de devises
        couple.coupleDevise = element.toPlainText() ;
        element = webView->page()->mainFrame()->findFirstElement("tr#pair_" + index + ">td[class*=bid]") ; // CSSselector pour la valeur d'achat
        couple.valeurAchat = element.toPlainText() ;
        element = webView->page()->mainFrame()->findFirstElement("tr#pair_" + index + ">td[class*=ask]") ; // CSSselector pour la valeur de vente
        couple.valeurVente = element.toPlainText() ;
        element = webView->page()->mainFrame()->findFirstElement("tr#pair_" + index + ">td[class*=pcp]") ; // CSSselector pour le pourcentage de variation de la cotation
        couple.variation = element.toPlainText() ;

        // Puis on demande a l'objet 'CoupleDevise' de se sauvegarder dans la bdd
        couple.save(&db) ;
    }
    // On rafraichit le modele du TableView
    rafraichitSQLQueryModel();
}



/** Rafraichit le QSqlQuery pour appliquer les parametres
 * contenue dans 'urlFiltreDevises' définie dans 'DialogueChoixDevises'.
 */
void principal::rafraichitSQLQueryModel()
{
    urlPourModele = "SELECT nom, achat, vente, variation, max(heure) AS 'Heure', jour FROM COTATION " + urlFiltreDevises + " GROUP BY nom" ;
    modeleQ->setQuery(urlPourModele) ;
}


/** Création de la base de donnée
 */
bool principal::creerBdd()
{
    db = QSqlDatabase::addDatabase( "QSQLITE") ;
    //db.setHostName(serveur);          // initialisation du serveur : non utilisé avec SQLite
    db.setDatabaseName("./" + nomBdd);  // initialisation du nom de la base de donnée
    //db.setUserName(loginBdd);         // initialisation du login : non utilisé avec SQLite
    //db.setPassword(passwordBdd);      // initialisation du password : non utilisé avec SQLite

    if (db.open()){                                  // Test si on a pu se connecter à la BDD
        qDebug() << "Connecté à la base de donnée" ;
        if (!db.tables().contains("COTATION")){      // Si la table COTATION n'existe pas, on la crée
            QString requeteSQL ;
            requeteSQL = "create table COTATION (id INTEGER PRIMARY KEY AUTOINCREMENT, nom varchar(10), achat double, vente double, variation double, heure time, jour date)";
            db.exec(requeteSQL) ;
            return true ;
        } else return true ;
    } else {
        qWarning() << "Pas de connexion à la base de donnée" ;
        return false ;
    }
}


/** Permet a QSettings de lire un fichier XML
 */
bool readXmlFile(QIODevice &device, QSettings::SettingsMap &map) {
  QXmlStreamReader xmlReader(&device);
  QStringList elements;

  // Tant que la fin ne est pas atteint et aucune erreur ne se est produite
  while (!xmlReader.atEnd() && !xmlReader.hasError()) {
    // Lire le jeton suivant
    xmlReader.readNext();

    // Quand l'objet est un StartElement
    if (xmlReader.isStartElement() && xmlReader.name() != "Settings") {
      // Ajouter un article à la liste
      elements.append(xmlReader.name().toString());
    // Quand l'objet est un EndElement
    } else if (xmlReader.isEndElement()) {
      // Pour supprimer le dernier élément
      if(!elements.isEmpty()) elements.removeLast();
    // Si jeton contient une valeur
    } else if (xmlReader.isCharacters() && !xmlReader.isWhitespace()) {
      QString key;

      // Ajouter des éléments à string
      for(int i = 0; i < elements.size(); i++) {
        if(i != 0) key += "/";
        key += elements.at(i);
      }

      // Entrer la valeur map
      map[key] = xmlReader.text().toString();
    }
  }

  // Affiche un warning si erreur
  if (xmlReader.hasError()) {
    qWarning() << xmlReader.errorString();
    return false;
  }

  return true;
}


/** Permet a QSettings d'ecrire dans un fichier XML
 */
bool writeXmlFile(QIODevice &device, const QSettings::SettingsMap &map) {
  QXmlStreamWriter xmlWriter(&device);

  xmlWriter.setAutoFormatting(true);
  xmlWriter.writeStartDocument();
  xmlWriter.writeStartElement("Settings");

  QStringList prev_elements;
  QSettings::SettingsMap::ConstIterator map_i;

  // Grâce à tous les éléments de la carte
  for (map_i = map.begin(); map_i != map.end(); map_i++) {

    QStringList elements = map_i.key().split("/");

    int x = 0;
    // Pour déterminer les éléments de fermeture
    while(x < prev_elements.size() && elements.at(x) == prev_elements.at(x)) {
      x++;
    }

    // Fermer Articles
    for(int i = prev_elements.size() - 1; i >= x; i--) {
      xmlWriter.writeEndElement();
    }

    // Ouvrir Tous les documents
    for (int i = x; i < elements.size(); i++) {
      xmlWriter.writeStartElement(elements.at(i));
    }

    // entrer la valeur
    xmlWriter.writeCharacters(map_i.value().toString());

    prev_elements = elements;
  }

  // Fermer éléments exceptionnels
  for(int i = 0; i < prev_elements.size(); i++) {
    xmlWriter.writeEndElement();
  }

  xmlWriter.writeEndElement();
  xmlWriter.writeEndDocument();

  return true;
}
