/**
 * \file dialoguetransactionautomatique.h
 * \brief Classe pour afficher la fenetre de transactions automatiques
 *
 * Affiche une fenetre permettant de calculer automatiquement
 * les profits possibles en temps reel. Se connecte a un web service
 * du site FOREX et l'affiche dans une fenetre de dialogue.
 *
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
