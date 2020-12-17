#include "serveurwidget.h"
#include "ui_serveurwidget.h"
#include <QHostInfo>
#include <QProcess>

ServeurWidget::ServeurWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ServeurWidget)
{
    ui->setupUi(this);
    socketEcouteServeur = new QTcpServer;
    socketDialogueClient = new QTcpSocket;
    process = new QProcess;
    connect(socketEcouteServeur,&QTcpServer::newConnection,this,&ServeurWidget::onQTcpServer_newConnection);
    connect(process,&QProcess::readyReadStandardOutput,this,&ServeurWidget::onQProcess_readyReadStandardOutput);

}

ServeurWidget::~ServeurWidget()
{
    delete  socketEcouteServeur;
    delete  socketDialogueClient;
    delete  process;
    delete  ui;
}

void ServeurWidget::onQTcpServer_newConnection()
{

    socketDialogueClient = socketEcouteServeur->nextPendingConnection();
    connect(socketDialogueClient,&QTcpSocket::readyRead,this,&ServeurWidget::onQTcpSocket_readyRead);
    connect(socketDialogueClient,&QTcpSocket::disconnected,this,&ServeurWidget::onQTcpSocket_disconnected);


}

void ServeurWidget::onQTcpSocket_readyRead()
{
    QString reponse;
    QByteArray data = socketDialogueClient->readAll();


    qDebug()<< data;
    switch (data[0])
    {
    case 'u':

        reponse = getenv("USER");
        socketDialogueClient->write(reponse.toLatin1());
        break;

    case 'c':
        reponse = QHostInfo::localHostName();
        socketDialogueClient->write(reponse.toLatin1());
        break;


    case 'o':

        process->start("uname",QStringList("-p"));
        break;

    case 'a':

        process->start("uname");
        break;

    }

}

void ServeurWidget::onQTcpSocket_disconnected()
{

}

void ServeurWidget::onQProcess_readyReadStandardOutput()
{
    QString reponse = process->readAllStandardOutput();

    if(!reponse.isEmpty())
    {
        QString message = "Réponse envoyée à " + socketDialogueClient->peerAddress().toString()+" : " + reponse;
        ui->textEditLogs->append(message);
        socketDialogueClient->write(reponse.toLatin1());
    }


}


void ServeurWidget::on_pushButtonLancecementServeur_clicked()
{
    if (socketEcouteServeur->listen(QHostAddress::Any,ui->spinBoxNumeroPort->text().toInt()))
       {
        qDebug() << "Le serveur est lancé";
       }

}
