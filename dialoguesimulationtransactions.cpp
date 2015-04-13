#include "dialoguesimulationtransactions.h"

#include <QComboBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlQueryModel>

DialogueSimulationTransactions::DialogueSimulationTransactions()
{
    setWindowTitle("Simulation de transactions");

    QSqlQueryModel* modeleCombo = new QSqlQueryModel;
    modeleCombo->setQuery("SELECT nom FROM COTATION GROUP BY nom ORDER BY nom") ;
    selection = new QComboBox(this);
    selection->setModel(modeleCombo);
    connect (selection, SIGNAL(currentIndexChanged(int)), this, SLOT(selectionChange()));
    QLabel* selectionLabel = new QLabel ("&Devises :") ;
    selectionLabel->setBuddy(selection);

    valeur = new QLineEdit();
    QPushButton* valide = new QPushButton("Calculer");
    achat = new QLabel();
    vente = new QLabel();

    QFormLayout* layout = new QFormLayout();
    layout->addRow("Valeur :", valeur);
    layout->addRow("Couple de devises", selection);
    layout->addRow("", valide);
    layout->addRow("Achat :", achat);
    layout->addRow("Vente :", vente);

    setLayout(layout);

}

DialogueSimulationTransactions::~DialogueSimulationTransactions()
{

}

void DialogueSimulationTransactions::selectionChange()
{
    QSqlQueryModel* modeleCalcul = new QSqlQueryModel;
    modeleCalcul->setQuery("SELECT achat, vente FROM COTATION WHERE nom ='" + selection->currentText() + "'") ;
    achat->text() = valeur * modeleCalcul->record(1).value("achat") ;
    vente->text() = valeur * modeleCalcul->record(1).value("vente") ;
}
