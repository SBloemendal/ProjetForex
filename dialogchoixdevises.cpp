#include "dialogchoixdevises.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include "principal.h"

dialogChoixDevises::dialogChoixDevises() : urlChoixCouples("")
{
    setWindowTitle("Choix des couples de devises");
    QVBoxLayout* layoutPrincipal = new QVBoxLayout;

    QGroupBox *groupBox = new QGroupBox("Choix des couples de devises", this) ;
    QHBoxLayout* layoutGroupBox = new QHBoxLayout ;

    QVBoxLayout* layoutGauche = new QVBoxLayout ;
    cb1 = new QCheckBox("EUR/USD", this) ;
    cb1->setChecked(true);
    cb2 = new QCheckBox("GBP/USD", this) ;
    cb2->setChecked(true);
    cb3 = new QCheckBox("USD/JPY", this) ;
    cb3->setChecked(true);
    cb4 = new QCheckBox("USD/CHF", this) ;
    cb4->setChecked(true);
    cb5 = new QCheckBox("EUR/GBP", this) ;
    cb5->setChecked(true);
    layoutGauche->addWidget(cb1);
    layoutGauche->addWidget(cb2);
    layoutGauche->addWidget(cb3);
    layoutGauche->addWidget(cb4);
    layoutGauche->addWidget(cb5);

    QVBoxLayout* layoutDroit = new QVBoxLayout ;
    cb6 = new QCheckBox("EUR/JPY", this) ;
    cb6->setChecked(true);
    cb7 = new QCheckBox("EUR/CHF", this) ;
    cb7->setChecked(true);
    cb8 = new QCheckBox("GPB/JPY", this) ;
    cb8->setChecked(true);
    cb9 = new QCheckBox("CHF/JPY", this) ;
    cb9->setChecked(true);
    cb10= new QCheckBox("GBP/CHF", this) ;
    cb10->setChecked(true);
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
    info->setText("Selectionner les couples de devises qui seront stockés dans la base de données.\n Ceci n'affecte pas la vue de la fenêtre principale.\n Pour modifier la vue, utilisez Options ");
    info->show();

    layoutPrincipal->addWidget(groupBox);
    layoutPrincipal->addWidget(info);
    layoutPrincipal->addLayout(layoutBoutons);
    setLayout(layoutPrincipal);
}

dialogChoixDevises::~dialogChoixDevises()
{

}

void dialogChoixDevises::construitURL()
{
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
    qDebug() << urlChoixCouples;
    emit dialogueFinis(urlChoixCouples) ;
    this->close();
}
