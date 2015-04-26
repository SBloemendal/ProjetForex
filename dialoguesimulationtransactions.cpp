#include "dialoguesimulationtransactions.h"
#include <QSqlQueryModel>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>

/*  Fenetre permettant de simuler une transaction
    en choisissant le couple de devises voulu.
*/
DialogueSimulationTransactions::DialogueSimulationTransactions()
{
    setWindowTitle("Simulation de transactions");
    setWindowIcon(QIcon(":/images/glyphicons-81-retweet.png"));
    setFixedHeight(150);
    setFixedWidth(250);

    // On crée le modele qui interrogera la base de donnée
    QSqlQueryModel* modeleCombo = new QSqlQueryModel;
    modeleCombo->setQuery("SELECT nom FROM COTATION GROUP BY nom ORDER BY nom") ;

    // ComboBox permettant le choix du couple de devises
    selection = new QComboBox(this);
    selection->setModel(modeleCombo);
    connect (selection, SIGNAL(currentIndexChanged(int)), this, SLOT(selectionChange()));
    QLabel* selectionLabel = new QLabel ("&Devises :") ;
    selectionLabel->setBuddy(selection);

    // Champs pour que l'utilisateur saisisse sa valeur voulue
    valeur = new QLineEdit();
    // Les boutons "Valider" et "Quitter"
    QPushButton* valide = new QPushButton("Calculer");
    connect (valide, SIGNAL(clicked()), this, SLOT(selectionChange()));
    QPushButton* annuler = new QPushButton(tr("&Quitter"));
    connect(annuler, SIGNAL(clicked()), this, SLOT(close()));
    annuler->setDefault(true);
    // Deux labels pour afficher les resultats
    achat = new QLabel();
    vente = new QLabel();

    // Et on met tout dans un layout de formulaire
    QFormLayout* layout = new QFormLayout();
    layout->addRow("Valeur :", valeur);
    layout->addRow("Couple de devises", selection);
    layout->addRow("", valide);
    layout->addRow("Achat :", achat);
    layout->addRow("Vente :", vente);
    layout->addRow("", annuler);

    setLayout(layout);

}



DialogueSimulationTransactions::~DialogueSimulationTransactions()
{

}



//  change la requete du modele en fonction des choix de l'utilisateur.
void DialogueSimulationTransactions::selectionChange()
{
    // On crée une requete prenant en compte le couple de devises selectionné dans le combobox 'selection'
    QSqlQueryModel* modeleCalcul = new QSqlQueryModel;
    modeleCalcul->setQuery("SELECT achat, vente FROM COTATION WHERE nom='" + selection->currentText() + "'") ;

    // On récupère la valeur d'achat sous forme de string,
    // on remplace la virgule par un point, et on la convertit
    // en double pour pouvoir faire le calcul.
    QString temp = modeleCalcul->data(modeleCalcul->index(1,0)).toString() ;
    temp.replace(',','.');
    achat->setNum(valeur->text().toDouble() * temp.toDouble()) ;
    // Idem pour la valeur de vente
    temp = modeleCalcul->data(modeleCalcul->index(1,1)).toString() ;
    temp.replace(',','.');
    vente->setNum(valeur->text().toDouble() / temp.toDouble()) ;
}
