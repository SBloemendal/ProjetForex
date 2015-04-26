/**
 * \file dialoguesimulationtransactions.h
 * \brief Classe pour afficher la fenetre de simulation de transaction.
 *
 * Fenetre permettant de simuler une transaction en choisissant le couple de devises voulu.
 * La simulation prend en compte les valeurs d'achat et de vente en temps reel.
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
    /** Génére la requete a la base de donnée en fonction des choix de l'utilisateur.
     *  concernant le couple. Le résultat est alors immédiatement affiché.
     */
    void selectionChange();

private:
    QComboBox* selection;
    QLineEdit* valeur ;
    QLabel* achat ;
    QLabel* vente ;

};

#endif // DIALOGUESIMULATIONTRANSACTIONS_H
