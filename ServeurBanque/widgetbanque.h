#ifndef WIDGETBANQUE_H
#define WIDGETBANQUE_H

#include <QWidget>
#include <QDebug>
#include <QTcpServer>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class WidgetBanque; }
QT_END_NAMESPACE

class WidgetBanque : public QWidget
{
    Q_OBJECT

public:
    WidgetBanque(QWidget *parent = nullptr);
    ~WidgetBanque();

private slots:
    void on_pushButtonConnexionBaseDeDonnees_clicked();

    void on_pushButtonAfficherInformations_clicked();

private:
    Ui::WidgetBanque *ui;
    QSqlDatabase bd;
};
#endif // WIDGETBANQUE_H
