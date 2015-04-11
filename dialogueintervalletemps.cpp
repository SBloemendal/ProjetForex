#include "dialogueintervalletemps.h"
#include <QVBoxLayout>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QTableView>
#include <QComboBox>

DialogueIntervalleTemps::DialogueIntervalleTemps()
{
    setWindowTitle("Affichage par intervalle de temps");
    QVBoxLayout* layout = new QVBoxLayout() ;

    QSqlQueryModel* modeleCombo = new QSqlQueryModel;
    modeleCombo->setQuery("SELECT nom FROM COTATION GROUP BY nom ORDER BY nom") ;
    selection = new QComboBox(this);
    selection->setModel(modeleCombo);
    connect (selection, SIGNAL(currentIndexChanged(int)), this, SLOT(selectionChange()));

    modeleIT = new QSqlTableModel ;
    modeleIT->setTable("COTATION");
    modeleIT->setFilter("nom='" + selection->currentText() + "'");
    modeleIT->select();



    tableView = new QTableView(this) ;
    tableView->setModel(modeleIT);
    tableView->setGeometry(40,50,720,500);
    tableView->setAlternatingRowColors(true);
    tableView->setShowGrid(false);

    layout->addWidget(selection);
    layout->addWidget(tableView);
    setLayout(layout);
}

DialogueIntervalleTemps::~DialogueIntervalleTemps()
{

}

void DialogueIntervalleTemps::selectionChange()
{

    modeleIT->setFilter("nom='" + selection->currentText() + "'");
    modeleIT->select();
}
