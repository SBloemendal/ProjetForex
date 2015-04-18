/**
 * \file dialoguetransactionautomatique.h
 * \author Simon
 * \version 1.0
 * \date 2015-04-27
 * \brief Classe pour afficher la fenetre de transactions automatiques
 */


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
