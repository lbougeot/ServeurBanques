#ifndef DAB_MAINWINDOW_H
#define DAB_MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QBuffer>

QT_BEGIN_NAMESPACE
namespace Ui { class DAB_MainWindow; }
QT_END_NAMESPACE

class DAB_MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    DAB_MainWindow(QWidget *parent = nullptr);
    ~DAB_MainWindow();

private:
    Ui::DAB_MainWindow *ui;
    QTcpSocket *socketClientBanque;

private slots:
    void on_pushButtonConnexion_clicked();
    void on_pushButtonEnvoi_clicked();
    void on_pushButtonNumeroCompte_clicked();
    void onQTcpSocket_connected();
    void onQTcpSocket_disconnected();
    void onQTcpSocket_error(QAbstractSocket::SocketError socketError);
    void onQTcpSocket_readyRead();

};
#endif // DAB_MAINWINDOW_H
