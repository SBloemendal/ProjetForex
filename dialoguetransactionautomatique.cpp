#include "dialoguetransactionautomatique.h"
#include <QWebView>

/** Affiche une fenetre permettant de calculer automatiquement
 * les profits possibles en temps reel
 */
DialogueTransactionAutomatique::DialogueTransactionAutomatique()
{
    setWindowTitle("Calculateur de profit");
    setWindowIcon(QIcon(":/images/glyphicons-228-usd.png"));
    setFixedHeight(430);
    setFixedWidth(440);
    graph = new QWebView (this);
    graph->load(QUrl("http://tools.investing.com/profit-calculator/index.php"));

}



DialogueTransactionAutomatique::~DialogueTransactionAutomatique()
{

}

