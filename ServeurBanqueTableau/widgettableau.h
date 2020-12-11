#ifndef WIDGETTABLEAU_H
#define WIDGETTABLEAU_H

#include <QWidget>
#include <QDebug>
#include <QTcpServer>
#include <QSqlDatabase>


QT_BEGIN_NAMESPACE
namespace Ui { class WidgetTableau; }
QT_END_NAMESPACE

class WidgetTableau : public QWidget
{
    Q_OBJECT

public:
    WidgetTableau(QWidget *parent = nullptr);
    ~WidgetTableau();

private slots:
    void on_pushButtonAfficherInformations_clicked();

    void on_pushButtonConnexionBaseDeDonnees_clicked();

private:
    Ui::WidgetTableau *ui;
    QSqlDatabase bd;
};
#endif // WIDGETTABLEAU_H
