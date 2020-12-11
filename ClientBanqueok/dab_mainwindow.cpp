#include "dab_mainwindow.h"
#include "ui_dab_mainwindow.h"

DAB_MainWindow::DAB_MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DAB_MainWindow)
{
    ui->setupUi(this);
    socketClientBanque = new QTcpSocket;

    connect(socketClientBanque, &QTcpSocket::connected, this, &DAB_MainWindow::onQTcpSocket_connected);
    connect(socketClientBanque, &QTcpSocket::disconnected, this, &DAB_MainWindow::onQTcpSocket_disconnected);
    connect(socketClientBanque, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &DAB_MainWindow::onQTcpSocket_error);
    connect(socketClientBanque, &QTcpSocket::readyRead, this, &DAB_MainWindow::onQTcpSocket_readyRead);
}

DAB_MainWindow::~DAB_MainWindow()
{
    delete ui;
    delete socketClientBanque;
}

void DAB_MainWindow::on_pushButtonConnexion_clicked()
{
    QString IP = ui->lineEditAdresse->text();
    quint16 port = ui->lineEditPort->text().toInt();

    socketClientBanque->connectToHost(IP, port, QIODevice::ReadWrite, QAbstractSocket::AnyIPProtocol);
}

void DAB_MainWindow::on_pushButtonEnvoi_clicked()
{
    quint16 taille=0;
    QChar commande;
    float montant = ui->lineEditMontant->text().toInt();

    if(ui->radioButtonSolde->isChecked()){
        commande = 'S';
        QBuffer tampon;
        tampon.open(QIODevice::WriteOnly);
        QDataStream out(&tampon);
        out<<taille<<commande;
        taille=tampon.size()-sizeof(taille);
        tampon.seek(0);
        out<<taille;
        socketClientBanque->write(tampon.buffer());
    }
    else if (ui->radioButtonRetrait->isChecked()) {
        commande = 'R';
        QBuffer tampon;
        tampon.open(QIODevice::WriteOnly);
        QDataStream out(&tampon);
        out<<taille<<commande<<montant;
        taille=tampon.size()-sizeof(taille);
        tampon.seek(0);
        out<<taille;
        socketClientBanque->write(tampon.buffer());
    }
    else if(ui->radioButtonDepot->isChecked()){
        commande = 'D';
        QBuffer tampon;
        tampon.open(QIODevice::WriteOnly);
        QDataStream out(&tampon);
        out<<taille<<commande<<montant;
        taille=tampon.size()-sizeof(taille);
        tampon.seek(0);
        out<<taille;
        socketClientBanque->write(tampon.buffer());
    }



}

void DAB_MainWindow::on_pushButtonNumeroCompte_clicked()
{
    quint16 taille=0;
    QChar commande='N';
    int compte=ui->lineEditNumeroCompte->text().toInt();
    QBuffer tampon;
    tampon.open(QIODevice::WriteOnly);
    QDataStream out(&tampon);
    out<<taille<<commande<<compte;
    taille=tampon.size()-sizeof(taille);
    tampon.seek(0);
    out<<taille;
    socketClientBanque->write(tampon.buffer());

}

void DAB_MainWindow::onQTcpSocket_connected()
{
    ui->textBrowserEtat->append("connected");

    ui->pushButtonEnvoi->setEnabled(true);
    ui->pushButtonNumeroCompte->setEnabled(true);
}

void DAB_MainWindow::onQTcpSocket_disconnected()
{
    ui->textBrowserEtat->append("disconnected");
}

void DAB_MainWindow::onQTcpSocket_error(QAbstractSocket::SocketError socketError)
{
    ui->textBrowserEtat->append(socketClientBanque->errorString());
}

void DAB_MainWindow::onQTcpSocket_readyRead()
{
    ui->textBrowserEtat->append("");

    quint16 taille=0;
    QString message;
    if(socketClientBanque->bytesAvailable() >= (qint64)taille)
    {
        QDataStream in(socketClientBanque);
        in >> taille;

        if(socketClientBanque->bytesAvailable() >= (qint64)taille)
        {
            in>>message;
        }
    }

    ui->lineEditMessage->setText(message);
}


