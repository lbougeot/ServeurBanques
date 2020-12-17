#include "widgetbasededonnees.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetBaseDeDonnees w;
    w.show();
    return a.exec();
}
