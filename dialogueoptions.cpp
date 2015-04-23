#include "dialogueoptions.h"
#include "principal.h"
#include <QDir>
#include <QBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QComboBox>

/** Affiche une fenetre proposant de modifier les options de l'application.
 */
DialogueOptions::DialogueOptions()
{
    // On crée un QSettings qui permettra d'initialiser les attributs avec les options sauvegardées
    //
    QSettings::Format XmlFormat = QSettings::registerFormat("xml", readXmlFile, writeXmlFile);
    QSettings::setPath(XmlFormat, QSettings::UserScope,QDir::currentPath());
    QSettings settings(XmlFormat, QSettings::UserScope, "settings");
    settings.beginGroup("Options");


    // Parametres généraux de la fenetre
    //
    setWindowTitle("Options");
    setFixedHeight(500);
    setFixedWidth(400);
    QVBoxLayout* layoutPrincipal = new QVBoxLayout;


    //Bloc d'options 'Base de donnée'
    //
    QGroupBox *groupBoxBdd = new QGroupBox("Paramètres de la base de données", this) ;
    QFormLayout* groupBoxBddLayout = new QFormLayout();

    serveur = new QLineEdit(settings.value("serveur", "127.0.0.1").toString()) ;
    nomBdd = new QLineEdit(settings.value("nomBdd", "bddForex.db").toString());
    loginBdd = new QLineEdit(settings.value("loginBdd", "admin").toString());
    passwordBdd = new QLineEdit(settings.value("passwordBdd", "admin").toString());
    urlForex = new QLineEdit(settings.value("urlForex", "http://fxrates.investing.com").toString());
    repeteTimer = new QComboBox;
    repeteTimer->insertItem(0,"5 secondes");
    repeteTimer->insertItem(1,"10 secondes");
    repeteTimer->insertItem(2,"30 secondes");
    repeteTimer->insertItem(3,"60 secondes");
    repeteTimer->setCurrentIndex(settings.value("indexTimer", 1).toInt());
    QLabel* infoBdd = new QLabel(this);
    infoBdd->setText("Les modifications des paramètres de la base de donnée\nseront pris en compte à la prochaine execution de l'application.");

    groupBoxBddLayout->addRow("&Serveur :", serveur) ;
    groupBoxBddLayout->addRow("&Nom de la base de donnée :", nomBdd) ;
    groupBoxBddLayout->addRow("&Identifiant :", loginBdd) ;
    groupBoxBddLayout->addRow("&Mot de passe :", passwordBdd) ;
    groupBoxBddLayout->addRow("Site &Forex :", urlForex) ;
    groupBoxBddLayout->addRow("Timer", repeteTimer);
    groupBoxBddLayout->addRow(infoBdd);
    groupBoxBdd->setLayout(groupBoxBddLayout);


    // Bloc d'options 'Choix des couples à stocker'
    //
    QGroupBox *groupBoxDevises = new QGroupBox("Données stockées", this) ;
    QVBoxLayout* layoutgroupBoxDevises = new QVBoxLayout ;
    QHBoxLayout* layoutDevises = new QHBoxLayout ;

    // On divise les checkboxs en deux colonnes
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

    // Deuxieme colonne de checkboxs
    QVBoxLayout* layoutDroit = new QVBoxLayout ;
    cb6 = new QCheckBox("EUR/JPY", this) ;
    cb6->setChecked(settings.value("cb6", true).toBool());
    cb7 = new QCheckBox("EUR/CHF", this) ;
    cb7->setChecked(settings.value("cb7", true).toBool());
    cb8 = new QCheckBox("GBP/JPY", this) ;
    cb8->setChecked(settings.value("cb8", true).toBool());
    cb9 = new QCheckBox("GBP/CHF", this) ;
    cb9->setChecked(settings.value("cb9", true).toBool());
    cb10= new QCheckBox("CHF/JPY", this) ;
    cb10->setChecked(settings.value("cb10", true).toBool());
    layoutDroit->addWidget(cb6);
    layoutDroit->addWidget(cb7);
    layoutDroit->addWidget(cb8);
    layoutDroit->addWidget(cb9);
    layoutDroit->addWidget(cb10);

    // Label d'information
    QLabel* infoSelectionDevise = new QLabel(this);
    infoSelectionDevise->setText("Selectionner les couples de devises qui seront stockés dans la base de données.\nCeci n'affecte pas l'affichage de la fenêtre principale.\nPour modifier l'affichade de la fenêtre principale, utilisez le menu 'Affichage'");

    layoutDevises->addLayout(layoutGauche);
    layoutDevises->addLayout(layoutDroit);
    layoutgroupBoxDevises->addLayout(layoutDevises);
    layoutgroupBoxDevises->addWidget(infoSelectionDevise);
    groupBoxDevises->setLayout(layoutgroupBoxDevises);


    // Bloc des boutons Valider et Annuler
    //
    QHBoxLayout* layoutBoutons = new QHBoxLayout;
    QPushButton* annuler = new QPushButton(tr("&Annuler"));
    connect(annuler, SIGNAL(clicked()), this, SLOT(close()));
    annuler->setDefault(true);
    QPushButton* valider = new QPushButton(tr("&Valider"));
    connect(valider, SIGNAL(clicked()), this, SLOT(enregistreValeurs()));
    layoutBoutons->addWidget(annuler);
    layoutBoutons->addWidget(valider);

    // On met tout dans le layout principal
    layoutPrincipal->addWidget(groupBoxBdd);
    layoutPrincipal->addWidget(groupBoxDevises);
    layoutPrincipal->addLayout(layoutBoutons);
    setLayout(layoutPrincipal);
    settings.endGroup();
}


DialogueOptions::~DialogueOptions()
{

}



/** Permet de stocker les options choisies
 * par l'utilisateur dans le QSettings.
 */
void DialogueOptions::enregistreValeurs()
{
    // Création d'un QSettings
    const QSettings::Format XmlFormat = QSettings::registerFormat("xml", readXmlFile, writeXmlFile);
    QSettings::setPath(XmlFormat, QSettings::UserScope,QDir::currentPath());
    QSettings settings(XmlFormat, QSettings::UserScope, "settings");

    // Création de la partie de l'url permettant la sélection des couples à demander dans la requete HTTP
    if (cb1->isChecked())
        urlChoixCouples += "1;";
    if (cb2->isChecked())
        urlChoixCouples += "2;";
    if (cb3->isChecked())
        urlChoixCouples += "3;";
    if (cb4->isChecked())
        urlChoixCouples += "4;";
    if (cb5->isChecked())
        urlChoixCouples += "6;";
    if (cb6->isChecked())
        urlChoixCouples += "9;";
    if (cb7->isChecked())
        urlChoixCouples += "10;";
    if (cb8->isChecked())
        urlChoixCouples += "11;";
    if (cb9->isChecked())
        urlChoixCouples += "12;";
    if (cb10->isChecked())
        urlChoixCouples += "13;";

    //Stockage du choix du timer
    // Il faut stocker la valeur souhaitée
    // et l'index du combobox pour pouvoir
    // le réinitialiser la prochaine fois.
    int timer;
    switch (repeteTimer->currentIndex())
    {
    case 0:
        timer = 5000;
        break;
    case 1:
        timer = 10000;
        break;
    case 2:
        timer = 30000;
        break;
    case 3:
    default:
        timer = 60000;
        break;
    }

    // On enregistre l'etat de chaque parametre pour
    // pouvoir les reinitialiser dans le meme etat
    // la prochaine fois.
    settings.beginGroup("Options");
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
    settings.setValue("urlChoixCouples", urlChoixCouples);
    settings.setValue("serveur", serveur->text());
    settings.setValue("nomBdd", nomBdd->text());
    settings.setValue("loginBdd", loginBdd->text());
    settings.setValue("passwordBdd", passwordBdd->text());
    settings.setValue("urlForex", urlForex->text());
    settings.setValue("indexTimer", repeteTimer->currentIndex());
    settings.setValue("timer", timer);
    settings.endGroup();

    // On envoie un signal attendue par la classe 'principal'.
    emit dialogueFinis(urlChoixCouples) ;
    this->close();
}
