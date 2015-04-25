#include "dialogueintervalletemps.h"
#include <QVBoxLayout>
#include <QSqlQueryModel>
#include <QComboBox>
#include <QLabel>
#include <QDateEdit>
#include <QPushButton>
#include <QTableView>
#include <QHeaderView>
#include <QSortFilterProxyModel>

/** Fenetre permettant d'afficher toutes les valeurs
 * d'un couple sélectionnée dans un intervalle de
 * temps donnée par l'utilisateur.
 */
DialogueIntervalleTemps::DialogueIntervalleTemps()
{
    // Paramètres généraux
    //
    setWindowTitle("Affichage par intervalle de temps");
    setWindowIcon(QIcon(":/images/glyphicons-46-calendar.png"));
    setFixedWidth(570);
    QGridLayout* layout = new QGridLayout(this) ;

    // Création de la combobox de choix du couple de devises
    //
    QSqlQueryModel* modeleCombo = new QSqlQueryModel;
    modeleCombo->setQuery("SELECT nom FROM COTATION GROUP BY nom ORDER BY nom") ;
    selection = new QComboBox(this);
    selection->setModel(modeleCombo);
    connect (selection, SIGNAL(currentIndexChanged(int)), this, SLOT(selectionChange()));
    QLabel* selectionLabel = new QLabel ("&Devises :") ;
    selectionLabel->setBuddy(selection);

    // Création des champs de dates souhaitées
    //
    dateDebut = new QDateEdit(QDate::currentDate());
    dateDebut->setCalendarPopup(true);
    dateDebut->setMaximumDate(QDate::currentDate());
    QLabel* dateDebutLabel = new QLabel("Date de &départ :");
    dateDebutLabel->setBuddy(dateDebut);

    dateFin = new QDateEdit(QDate::currentDate());
    dateFin->setCalendarPopup(true);
    dateFin->setMaximumDate(QDate::currentDate());
    QLabel* dateFinLabel = new QLabel("Date de &fin :");
    dateFinLabel->setBuddy(dateFin);

    // Boutons et information
    //
    QPushButton* valider = new QPushButton("Valider") ;
    valider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding) ;
    connect(valider, SIGNAL(clicked()), this, SLOT(selectionChange()));
    QLabel* info = new QLabel("Sélectionner le couple de devises\n et les dates de début et de fin\n de la période souhaitée.");
    QPushButton* annuler = new QPushButton(tr("&Quitter"));
    connect(annuler, SIGNAL(clicked()), this, SLOT(close()));
    annuler->setDefault(true);

    // Modele et vue pour afficher les résultats
    //
    modeleIT = new QSqlQueryModel ;
    // On insere un proxymodel entre le modele et la vue pour permettre le tri par colonne
    QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel;
    proxyModel->setSourceModel( modeleIT );
    selectionChange();

    tableView = new QTableView ;
    tableView->setObjectName("view");
    tableView->setModel(proxyModel);
    tableView->setSortingEnabled(true);
    tableView->setMinimumHeight(500);
    tableView->setFixedWidth(550);
    tableView->setAlternatingRowColors(true);
    tableView->hideColumn(0);
    tableView->verticalHeader()->hide();
    tableView->setShowGrid(false);
    tableView->verticalHeader()->setDefaultSectionSize(20);
    tableView->horizontalHeader()->setDefaultSectionSize(90);
    tableView->horizontalHeader()->setStretchLastSection(true);

    // On place tout dans le layout principal
    //
    layout->addWidget(selectionLabel,0,0,1,2);
    layout->addWidget(selection,0,2,1,1);
    layout->addWidget(dateDebutLabel,1,0,1,2);
    layout->addWidget(dateDebut,1,2,1,1);
    layout->addWidget(dateFinLabel,2,0,1,2);
    layout->addWidget(dateFin,2,2,1,1);
    layout->addWidget(valider,0,3,3,1);
    layout->addWidget(info,1,4,2,2);
    layout->addWidget(annuler,0,5,1,1);
    layout->setColumnStretch(4,1);
    layout->addWidget(tableView,3,0,1,6);
    setLayout(layout);
}



DialogueIntervalleTemps::~DialogueIntervalleTemps()
{

}



/** Change la requete du modele en fonction des choix de l'utilisateur
 */
void DialogueIntervalleTemps::selectionChange()
{
    modeleIT->setQuery("SELECT * FROM COTATION WHERE nom='" + selection->currentText() + "' AND jour BETWEEN '" + dateDebut->date().toString("yyyy-MM-dd") + "' AND '" + dateFin->date().toString("yyyy-MM-dd") + "' ORDER BY jour DESC, heure DESC");
}
