/**
 * \file dialoguesimulationtransactions.h
 * \author Simon
 * \version 1.0
 * \date 2015-04-27
 * \brief Classe pour afficher la fenetre de simulation de transaction
 */


#ifndef DIALOGUESIMULATIONTRANSACTIONS_H
#define DIALOGUESIMULATIONTRANSACTIONS_H

#include <QDialog>

class QComboBox ;
class QLabel ;
class QLineEdit;


class DialogueSimulationTransactions : public QDialog
{
    Q_OBJECT

public:
    DialogueSimulationTransactions();
    ~DialogueSimulationTransactions();

private slots:
    /** Gere l'affichage des données en fonction du choix de l'utilisateur */
    void selectionChange();

private:
    QComboBox* selection;
    QLineEdit* valeur ;
    QLabel* achat ;
    QLabel* vente ;

};

#endif // DIALOGUESIMULATIONTRANSACTIONS_H
