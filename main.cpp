#include <QApplication>
#include "principal.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Principal b ;
    b.show();
    return a.exec();
}
