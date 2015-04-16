#include "dialoguetransactionautomatique.h"
#include <QWebView>

DialogueTransactionAutomatique::DialogueTransactionAutomatique()
{
    setWindowTitle("Transactions automatiques");
    setFixedHeight(430);
    setFixedWidth(440);
    graph = new QWebView (this);
    graph->load(QUrl("http://tools.investing.com/profit-calculator/index.php"));

}

DialogueTransactionAutomatique::~DialogueTransactionAutomatique()
{
    delete graph ;
}

