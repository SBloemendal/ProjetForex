#include <QApplication>
#include <QGraphicsScene>
#include "principal.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    principal b ;
    b.show();
    return a.exec();
}
