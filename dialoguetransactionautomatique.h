#ifndef DIALOGUETRANSACTIONAUTOMATIQUE_H
#define DIALOGUETRANSACTIONAUTOMATIQUE_H

#include <QDialog>

class QWebView ;

class DialogueTransactionAutomatique : public QDialog
{
public:
    DialogueTransactionAutomatique();
    ~DialogueTransactionAutomatique();

private:
    QWebView* graph ;
};

#endif // DIALOGUETRANSACTIONAUTOMATIQUE_H
