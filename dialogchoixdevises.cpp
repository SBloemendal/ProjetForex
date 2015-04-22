#include "dialogchoixdevises.h"
#include "principal.h"
#include <QDir>
#include <QBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>

/** Fenetre permettant à l'utilisateur de selectionner
 * les couples de devises qu'il veut voir afficher dans
 * la fenetre principale
 */
DialogueChoixDevises::DialogueChoixDevises() : urlChoixCouples("")
{
    // On crée un QSettings qui permettra d'initialiser les attributs avec les options sauvegardées
    //
    QSettings::Format XmlFormat = QSettings::registerFormat("xml", readXmlFile, writeXmlFile);
    QSettings::setPath(XmlFormat, QSettings::UserScope,QDir::currentPath());
    QSettings settings(XmlFormat, QSettings::UserScope, "CCI Colmar", "ProjetForex_SB");
    settings.beginGroup("afficherDevises");


    // Parametres généraux
    //
    setWindowTitle("Afficher ces couples de devises");
    setFixedHeight(200);
    setFixedWidth(200);
    QVBoxLayout* layoutPrincipal = new QVBoxLayout;


    // Groupe des checkboxs pour la selection des couples
    //
    QGroupBox *groupBox = new QGroupBox("Choix des couples de devises", this) ;
    QHBoxLayout* layoutGroupBox = new QHBoxLayout ;

    // On divise les checkboxs en deux colonnes pour un meilleur affichage
    // On initialise chaque checkbox avec la valeur enregistrée dans le QSettings
    QVBoxLayout* layoutGauche = new QVBoxLayout ;
    cb1 = new QCheckBox("EUR/USD", this) ;
    cb1->setChecked(settings.value("cb1", true).toBool());
    cb2 = new QCheckBox("GBP/USD", this) ;
    cb2->setChecked(settings.value("cb2", true).toBool());
    cb3 = new QCheckBox("USD/JPY", this) ;
    cb3->setChecked(settings.value("cb3", true).toBool());
    cb4 = new QCheckBox("USD/CHF", this) ;
    cb4->setChecked(settings.value("cb4", true).toBool());
    cb5 = new QCheckBox("EUR/GBP", this) ;
    cb5->setChecked(settings.value("cb5", true).toBool());
    layoutGauche->addWidget(cb1);
    layoutGauche->addWidget(cb2);
    layoutGauche->addWidget(cb3);
    layoutGauche->addWidget(cb4);
    layoutGauche->addWidget(cb5);

    // Deuxieme colonne
    QVBoxLayout* layoutDroit = new QVBoxLayout ;
    cb6 = new QCheckBox("EUR/JPY", this) ;
    cb6->setChecked(settings.value("cb6", true).toBool());
    cb7 = new QCheckBox("EUR/CHF", this) ;
    cb7->setChecked(settings.value("cb7", true).toBool());
    cb8 = new QCheckBox("GBP/JPY", this) ;
    cb8->setChecked(settings.value("cb8", true).toBool());
    cb9 = new QCheckBox("CHF/JPY", this) ;
    cb9->setChecked(settings.value("cb9", true).toBool());
    cb10= new QCheckBox("GBP/CHF", this) ;
    cb10->setChecked(settings.value("cb10", true).toBool());
    layoutDroit->addWidget(cb6);
    layoutDroit->addWidget(cb7);
    layoutDroit->addWidget(cb8);
    layoutDroit->addWidget(cb9);
    layoutDroit->addWidget(cb10);

    layoutGroupBox->addLayout(layoutGauche);
    layoutGroupBox->addLayout(layoutDroit);
    groupBox->setLayout(layoutGroupBox);
    groupBox->move(5,5);


    // Bloc des boutons et information
    //
    QHBoxLayout* layoutBoutons = new QHBoxLayout;
    QPushButton* annuler = new QPushButton(tr("&Annuler"));
    connect(annuler, SIGNAL(clicked()), this, SLOT(close()));
    annuler->setDefault(true);
    QPushButton* valider = new QPushButton(tr("&Valider"));
    connect(valider, SIGNAL(clicked()), this, SLOT(enregistreValeurs()));
    layoutBoutons->addWidget(annuler);
    layoutBoutons->addWidget(valider);

    QLabel* info = new QLabel(this);
    info->setText("Selectionner les couples de devises\nà afficher dans l'écran principal.");


    // On met tout dans le layout principal
    //
    layoutPrincipal->addWidget(groupBox);
    layoutPrincipal->addWidget(info);
    layoutPrincipal->addLayout(layoutBoutons);
    setLayout(layoutPrincipal);
    settings.endGroup();
}

DialogueChoixDevises::~DialogueChoixDevises()
{

}
/** Methode permettant d'enregistrer les choix de l'utilisateur et de
 * modifier l'affichage de la fenetre principale en fonction
 */
void DialogueChoixDevises::enregistreValeurs()
{
    // On crée un QSettings pour stocker les valeurs
    const QSettings::Format XmlFormat = QSettings::registerFormat("xml", readXmlFile, writeXmlFile);
    QSettings::setPath(XmlFormat, QSettings::UserScope,QDir::currentPath());
    QSettings settings(XmlFormat, QSettings::UserScope, "CCI Colmar", "ProjetForex_SB");
    settings.beginGroup("afficherDevises");

    // Création d'un string contenant la partie de la requete permettant la sélection des couples à afficher dans la fenetre principale
    // Cette string sera ensuite passer a la fenetre principale pour modifier la requete d'affichage
    if (cb1->isChecked())
        urlChoixCouples += "'EUR/USD',";
    if (cb2->isChecked())
        urlChoixCouples += "'GBP/USD',";
    if (cb3->isChecked())
        urlChoixCouples += "'USD/JPY',";
    if (cb4->isChecked())
        urlChoixCouples += "'USD/CHF',";
    if (cb5->isChecked())
        urlChoixCouples += "'EUR/GBP',";
    if (cb6->isChecked())
        urlChoixCouples += "'EUR/JPY',";
    if (cb7->isChecked())
        urlChoixCouples += "'EUR/CHF',";
    if (cb8->isChecked())
        urlChoixCouples += "'GBP/JPY',";
    if (cb9->isChecked())
        urlChoixCouples += "'CHF/JPY',";
    if (cb10->isChecked())
        urlChoixCouples += "'GBP/CHF',";

    if (urlChoixCouples != "")
    {
        urlChoixCouples.chop(1);
        urlChoixCouples = "WHERE jour=date('now') AND nom IN (" + urlChoixCouples + ")" ;
    } else
        urlChoixCouples =  "WHERE jour=date('now') AND nom IN ''" ;

    // On enregistre l'etat de chaque checkbox pour
    // pouvoir les reinitialiser dans le meme etat
    // la prochaine fois.
    settings.setValue("cb1", cb1->isChecked());
    settings.setValue("cb2", cb2->isChecked());
    settings.setValue("cb3", cb3->isChecked());
    settings.setValue("cb4", cb4->isChecked());
    settings.setValue("cb5", cb5->isChecked());
    settings.setValue("cb6", cb6->isChecked());
    settings.setValue("cb7", cb7->isChecked());
    settings.setValue("cb8", cb8->isChecked());
    settings.setValue("cb9", cb9->isChecked());
    settings.setValue("cb10", cb10->isChecked());
    settings.setValue("urlchoixCouples", urlChoixCouples);
    settings.endGroup();

    // On envoie un signal attendue par la classe 'principal'.
    emit dialogueFinis(urlChoixCouples) ;
    this->close();
}
