#include "dialoguesimulationtransactions.h"
#include <QSqlQueryModel>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>


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
    connect (valide, SIGNAL(clicked()), this, SLOT(selectionChange()));
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
    modeleCalcul->setQuery("SELECT achat, vente FROM COTATION WHERE nom='" + selection->currentText() + "'") ;

    QString temp = modeleCalcul->data(modeleCalcul->index(1,0)).toString() ;
    temp.replace(',','.');
    achat->setNum(valeur->text().toDouble() * temp.toDouble()) ;

    temp = modeleCalcul->data(modeleCalcul->index(1,1)).toString() ;
    temp.replace(',','.');
    vente->setNum(valeur->text().toDouble() / temp.toDouble()) ;
}
