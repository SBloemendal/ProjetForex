#include "dialogchoixdevises.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include <QSettings>
#include "principal.h"

dialogChoixDevises::dialogChoixDevises() : urlChoixCouples("")
{
    QSettings settings (QSettings::IniFormat, QSettings::UserScope, "CCI Colmar", "ProjetForex_SB") ;
    settings.beginGroup("choixDevises");

    setWindowTitle("Choix des couples de devises");
    QVBoxLayout* layoutPrincipal = new QVBoxLayout;

    QGroupBox *groupBox = new QGroupBox("Choix des couples de devises", this) ;
    QHBoxLayout* layoutGroupBox = new QHBoxLayout ;

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
    cb8 = new QCheckBox("GPB/JPY", this) ;
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

    layoutGroupBox->addLayout(layoutGauche);
    layoutGroupBox->addLayout(layoutDroit);
    groupBox->setLayout(layoutGroupBox);
    groupBox->move(5,5);

    QHBoxLayout* layoutBoutons = new QHBoxLayout;
    QPushButton* annuler = new QPushButton(tr("&Annuler"));
    connect(annuler, SIGNAL(clicked()), this, SLOT(close()));
    annuler->setDefault(true);
    QPushButton* valider = new QPushButton(tr("&Valider"));
    connect(valider, SIGNAL(clicked()), this, SLOT(construitURL()));
    layoutBoutons->addWidget(annuler);
    layoutBoutons->addWidget(valider);

    QLabel* info = new QLabel(this);
    info->setText("Selectionner les couples de devises qui seront stockés dans la base de données.\n Ceci n'affecte pas l'affichage de la fenêtre principale.\n Pour modifier l'affichade de la fenêtre principale, utilisez le menu Options ");

    layoutPrincipal->addWidget(groupBox);
    layoutPrincipal->addWidget(info);
    layoutPrincipal->addLayout(layoutBoutons);
    setLayout(layoutPrincipal);
    settings.endGroup();
}

dialogChoixDevises::~dialogChoixDevises()
{

}

void dialogChoixDevises::construitURL()
{
    QSettings settings (QSettings::IniFormat, QSettings::UserScope, "CCI Colmar", "ProjetForex_SB") ;
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

    settings.beginGroup("choixDevises");
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
    settings.endGroup();

    emit dialogueFinis(urlChoixCouples) ;
    this->close();
}
