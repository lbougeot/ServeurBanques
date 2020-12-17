#ifndef SERVEURWIDGET_H
#define SERVEURWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
#include <QProcess>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class ServeurWidget; }
QT_END_NAMESPACE

class ServeurWidget : public QWidget
{
    Q_OBJECT

public:
    ServeurWidget(QWidget *parent = nullptr);
    ~ServeurWidget();




private slots:
    void on_pushButtonLancecementServeur_clicked();
    void onQTcpServer_newConnection();
    void onQTcpSocket_readyRead();
    void onQTcpSocket_disconnected();
    void onQProcess_readyReadStandardOutput();
    void Timeout();

private:
    Ui::ServeurWidget *ui;
    QTcpServer *socketEcouteServeur;
    QTcpSocket *socketDialogueClient;
    QProcess *process;



};
#endif // SERVEURWIDGET_H
