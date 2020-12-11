#include "widgettableau.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetTableau w;
    w.show();
    return a.exec();
}
