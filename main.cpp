#include "Canvas.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Canvas c;
    c.show();
    return a.exec();
}
