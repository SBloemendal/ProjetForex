#include "dialogchoixdevises.h"
#include "principal.h"

#include <QDir>
#include <QBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>


dialogChoixDevises::dialogChoixDevises() : urlChoixCouples("")
{
    QSettings::Format XmlFormat = QSettings::registerFormat("xml", readXmlFile, writeXmlFile);
    QSettings::setPath(XmlFormat, QSettings::UserScope,QDir::currentPath());
    QSettings settings(XmlFormat, QSettings::UserScope, "CCI Colmar", "ProjetForex_SB");
    settings.beginGroup("afficherDevises");

    setWindowTitle("Afficher ces couples de devises");
    QVBoxLayout* layoutPrincipal = new QVBoxLayout;

    QGroupBox *groupBox = new QGroupBox("Choix des couples de devises", this) ;
    QHBoxLayout* layoutGroupBox = new QHBoxLayout ;

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

    QHBoxLayout* layoutBoutons = new QHBoxLayout;
    QPushButton* annuler = new QPushButton(tr("&Annuler"));
    connect(annuler, SIGNAL(clicked()), this, SLOT(close()));
    annuler->setDefault(true);
    QPushButton* valider = new QPushButton(tr("&Valider"));
    connect(valider, SIGNAL(clicked()), this, SLOT(construitURL()));
    layoutBoutons->addWidget(annuler);
    layoutBoutons->addWidget(valider);

    QLabel* info = new QLabel(this);
    info->setText("Selectionner les couples de devises\nà afficher dans l'écran principal.");

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
    const QSettings::Format XmlFormat = QSettings::registerFormat("xml", readXmlFile, writeXmlFile);
    QSettings::setPath(XmlFormat, QSettings::UserScope,QDir::currentPath());
    QSettings settings(XmlFormat, QSettings::UserScope, "CCI Colmar", "ProjetForex_SB");


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
