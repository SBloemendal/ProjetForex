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
    void selectionChange();

private:
    QComboBox* selection;
    QLineEdit* valeur ;
    QLabel* achat ;
    QLabel* vente ;

};

#endif // DIALOGUESIMULATIONTRANSACTIONS_H