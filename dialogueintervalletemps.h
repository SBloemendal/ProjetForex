#ifndef DIALOGUEINTERVALLETEMPS_H
#define DIALOGUEINTERVALLETEMPS_H

#include "principal.h"
#include <QDialog>

class QSqlQueryModel ;
class QTableView ;
class QComboBox ;
class QLineEdit ;
class QDateEdit ;

class DialogueIntervalleTemps : public QDialog
{
    Q_OBJECT

public:
    DialogueIntervalleTemps();
    ~DialogueIntervalleTemps();

private slots:
    void selectionChange();

private:
    QSqlQueryModel* modeleIT ;
    QTableView * tableView ;
    QComboBox* selection ;
    QDateEdit* dateDebut ;
    QDateEdit* dateFin ;
};

#endif // DIALOGUEINTERVALLETEMPS_H
