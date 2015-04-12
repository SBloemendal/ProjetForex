#include "dialogueintervalletemps.h"
#include <QVBoxLayout>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QTableView>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCalendarWidget>
#include <QDateEdit>

DialogueIntervalleTemps::DialogueIntervalleTemps()
{
    setWindowTitle("Affichage par intervalle de temps");
    QGridLayout* layout = new QGridLayout(this) ;

    QSqlQueryModel* modeleCombo = new QSqlQueryModel;
    modeleCombo->setQuery("SELECT nom FROM COTATION GROUP BY nom ORDER BY nom") ;
    selection = new QComboBox(this);
    selection->setModel(modeleCombo);
    connect (selection, SIGNAL(currentIndexChanged(int)), this, SLOT(selectionChange()));
    QLabel* selectionLabel = new QLabel ("&Devises :") ;
    selectionLabel->setBuddy(selection);

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

    QPushButton* valider = new QPushButton("Valider") ;
    valider->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding) ;
    connect(valider, SIGNAL(clicked()), this, SLOT(selectionChange()));
    QLabel* info = new QLabel("Sélectionner le couple de devises\n et les dates de début et de fin\n de la période souhaitée.");

    modeleIT = new QSqlQueryModel ;
    selectionChange();

    tableView = new QTableView ;
    tableView->setModel(modeleIT);
    tableView->setMinimumHeight(500);
    tableView->setFixedWidth(550);
    tableView->setAlternatingRowColors(true);
    tableView->hideColumn(0);
    tableView->verticalHeader()->hide();
    tableView->setShowGrid(false);
    tableView->verticalHeader()->setDefaultSectionSize(20);
    tableView->horizontalHeader()->setDefaultSectionSize(90);
    tableView->horizontalHeader()->setStretchLastSection(true);

    layout->addWidget(selectionLabel,0,0,1,2);
    layout->addWidget(selection,0,2,1,1);
    layout->addWidget(dateDebutLabel,1,0,1,2);
    layout->addWidget(dateDebut,1,2,1,1);
    layout->addWidget(dateFinLabel,2,0,1,2);
    layout->addWidget(dateFin,2,2,1,1);
    layout->addWidget(valider,0,3,3,1);
    layout->addWidget(info,0,4,3,2);
    layout->setColumnStretch(4,1);
    layout->addWidget(tableView,3,0,1,6);
    setLayout(layout);
}

DialogueIntervalleTemps::~DialogueIntervalleTemps()
{

}

void DialogueIntervalleTemps::selectionChange()
{
    modeleIT->setQuery("SELECT * FROM COTATION WHERE nom='" + selection->currentText() + "' AND jour BETWEEN '" + dateDebut->date().toString("yyyy-MM-dd") + "' AND '" + dateFin->date().toString("yyyy-MM-dd") + "' ORDER BY jour DESC, heure DESC");
}
