#ifndef DIALOGUEINTERVALLETEMPS_H
#define DIALOGUEINTERVALLETEMPS_H

#include "principal.h"
#include <QDialog>

class QSqlTableModel ;
class QTableView ;
class QComboBox ;

class DialogueIntervalleTemps : public QDialog
{
    Q_OBJECT

public:
    DialogueIntervalleTemps();
    ~DialogueIntervalleTemps();

private slots:
    void selectionChange();

private:
    QSqlTableModel* modeleIT ;
    QTableView * tableView ;
    QComboBox* selection ;
};

#endif // DIALOGUEINTERVALLETEMPS_H
