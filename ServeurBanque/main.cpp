#include "widgetbanque.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetBanque w;
    w.show();
    return a.exec();
}
