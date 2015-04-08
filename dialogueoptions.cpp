#include "dialogueoptions.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QCheckBox>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include "principal.h"


DialogueOptions::DialogueOptions()
{
    setWindowTitle("Options");
    QVBoxLayout* layoutPrincipal = new QVBoxLayout;

    QGroupBox *groupBox = new QGroupBox("Choix des couples de devises", this) ;
    groupBox->move(5,5);

    QHBoxLayout* layoutBoutons = new QHBoxLayout;
    QPushButton* annuler = new QPushButton(tr("&Annuler"));
    connect(annuler, SIGNAL(clicked()), this, SLOT(close()));
    annuler->setDefault(true);
    QPushButton* valider = new QPushButton(tr("&Valider"));
    connect(annuler, SIGNAL(clicked()), this, SLOT(close()));
    layoutBoutons->addWidget(annuler);
    layoutBoutons->addWidget(valider);

    QLabel* info = new QLabel(this);
    info->setText("Options");
    //info->show();

    layoutPrincipal->addWidget(groupBox);
    layoutPrincipal->addWidget(info);
    layoutPrincipal->addLayout(layoutBoutons);
    setLayout(layoutPrincipal);
}

DialogueOptions::~DialogueOptions()
{

}

