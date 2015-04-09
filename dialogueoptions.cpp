#include "dialogueoptions.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QSettings>
#include <QLineEdit>
#include "principal.h"

DialogueOptions::DialogueOptions()
{
    QSettings settings (QSettings::IniFormat, QSettings::UserScope, "CCI Colmar", "ProjetForex_SB") ;
    settings.beginGroup("afficherDevises");

    setWindowTitle("Options");
    QVBoxLayout* layoutPrincipal = new QVBoxLayout;

    QGroupBox *groupBoxBdd = new QGroupBox("Base de données", this) ;
    QVBoxLayout* layoutBdd = new QVBoxLayout ;
    QLineEdit* serveur = new QLineEdit("Serveur") ;
    QLineEdit* nomBdd = new QLineEdit("Nom de la base de donnée");
    QLineEdit* loginBdd = new QLineEdit("Identifiant");
    QLineEdit* passwordBdd = new QLineEdit("Mot de passe");
    QLineEdit* urlForex = new QLineEdit("Site Forex");
    layoutBdd->addWidget(serveur);
    layoutBdd->addWidget(nomBdd);
    layoutBdd->addWidget(loginBdd);
    layoutBdd->addWidget(passwordBdd);
    layoutBdd->addWidget(urlForex);
    groupBoxBdd->setLayout(layoutBdd);

    QGroupBox *groupBoxDevises = new QGroupBox("Afficher ces couples de devises", this) ;
    QHBoxLayout* layoutgroupBoxDevises = new QHBoxLayout ;

    QVBoxLayout* layoutGauche = new QVBoxLayout ;
    cb1 = new QCheckBox("EUR/USD", this) ;
    cb1->setChecked(settings.value("cb1").toBool());
    cb2 = new QCheckBox("GBP/USD", this) ;
    cb2->setChecked(settings.value("cb2").toBool());
    cb3 = new QCheckBox("USD/JPY", this) ;
    cb3->setChecked(settings.value("cb3").toBool());
    cb4 = new QCheckBox("USD/CHF", this) ;
    cb4->setChecked(settings.value("cb4").toBool());
    cb5 = new QCheckBox("EUR/GBP", this) ;
    cb5->setChecked(settings.value("cb5").toBool());
    layoutGauche->addWidget(cb1);
    layoutGauche->addWidget(cb2);
    layoutGauche->addWidget(cb3);
    layoutGauche->addWidget(cb4);
    layoutGauche->addWidget(cb5);

    QVBoxLayout* layoutDroit = new QVBoxLayout ;
    cb6 = new QCheckBox("EUR/JPY", this) ;
    cb6->setChecked(settings.value("cb6").toBool());
    cb7 = new QCheckBox("EUR/CHF", this) ;
    cb7->setChecked(settings.value("cb7").toBool());
    cb8 = new QCheckBox("GBP/JPY", this) ;
    cb8->setChecked(settings.value("cb8").toBool());
    cb9 = new QCheckBox("CHF/JPY", this) ;
    cb9->setChecked(settings.value("cb9").toBool());
    cb10= new QCheckBox("GBP/CHF", this) ;
    cb10->setChecked(settings.value("cb10").toBool());
    layoutDroit->addWidget(cb6);
    layoutDroit->addWidget(cb7);
    layoutDroit->addWidget(cb8);
    layoutDroit->addWidget(cb9);
    layoutDroit->addWidget(cb10);

    layoutgroupBoxDevises->addLayout(layoutGauche);
    layoutgroupBoxDevises->addLayout(layoutDroit);
    groupBoxDevises->setLayout(layoutgroupBoxDevises);
    //groupBoxDevises->move(5,5);






    QLabel* info = new QLabel(this);
    info->setText("Options");

    QHBoxLayout* layoutBoutons = new QHBoxLayout;
    QPushButton* annuler = new QPushButton(tr("&Annuler"));
    connect(annuler, SIGNAL(clicked()), this, SLOT(close()));
    annuler->setDefault(true);
    QPushButton* valider = new QPushButton(tr("&Valider"));
    connect(valider, SIGNAL(clicked()), this, SLOT(construitURL()));
    layoutBoutons->addWidget(annuler);
    layoutBoutons->addWidget(valider);

    layoutPrincipal->addWidget(groupBoxBdd);
    layoutPrincipal->addWidget(groupBoxDevises);
    layoutPrincipal->addWidget(info);
    layoutPrincipal->addLayout(layoutBoutons);
    setLayout(layoutPrincipal);
    settings.endGroup();
}

DialogueOptions::~DialogueOptions()
{

}

void DialogueOptions::construitURL()
{
    QSettings settings (QSettings::IniFormat, QSettings::UserScope, "CCI Colmar", "ProjetForex_SB") ;

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
        urlChoixCouples = "WHERE nom IN (" + urlChoixCouples + ")" ;
    }

    settings.beginGroup("afficherDevises");
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

    emit dialogueFinis(urlChoixCouples) ;
    this->close();
}
