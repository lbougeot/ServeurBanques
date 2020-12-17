#include "clientwidget.h"
#include "ui_clientwidget.h"


ClientWidget::ClientWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    socketDeDialogueAvecServeur = new QTcpSocket;
    connect(socketDeDialogueAvecServeur,&QTcpSocket::close,this,&ClientWidget::onQTcpSocket_aboutToClose);
    connect(socketDeDialogueAvecServeur,&QTcpSocket::connected,this,&ClientWidget::onQTcpSocket_connected);
    connect(socketDeDialogueAvecServeur,&QTcpSocket::disconnected,this,&ClientWidget::onQTcpSocket_disconnected);
    connect(socketDeDialogueAvecServeur,&QTcpSocket::hostFound,this,&ClientWidget::onQTcpSocket_hostFound);
    connect(socketDeDialogueAvecServeur,&QTcpSocket::disconnected,this,&ClientWidget::onQTcpSocket_disconnected);
    connect(socketDeDialogueAvecServeur,&QTcpSocket::stateChanged,this,&ClientWidget::onQTcpSocket_stateChanged);
    connect(socketDeDialogueAvecServeur,&QTcpSocket::bytesWritten,this,&ClientWidget::onQTcpSocket_bytesWritten);
    connect(socketDeDialogueAvecServeur,&QTcpSocket::readChannelFinished,this,&ClientWidget::onQTcpSocket_readChannelFinished);
    connect(socketDeDialogueAvecServeur,&QTcpSocket::readyRead,this,&ClientWidget::onQTcpSocket_readyRead);


    connect(socketDeDialogueAvecServeur,
    QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
    this,
    &ClientWidget::onQTcpSocket_error);

}

ClientWidget::~ClientWidget()
{
    delete ui;
    delete socketDeDialogueAvecServeur;
}




void ClientWidget::on_pushButtonConnexion_clicked()
{
    if(ui->pushButtonConnexion->text()=="Connexion"){
        QHostAddress adresse(ui->lineEditAdresseIp->text());
        socketDeDialogueAvecServeur->connectToHost(adresse,ui->lineEditNumeroPort->text().toUInt());
        ui->pushButtonConnexion->setText("Deconnection");
    }else{
        socketDeDialogueAvecServeur->disconnectFromHost();
        ui->pushButtonConnexion->setText("Connexion");
    }


}

void ClientWidget::on_pushButtonNomOrdinateur_clicked()
{
    typeDeDemande="c";
    socketDeDialogueAvecServeur->write(typeDeDemande.toLatin1());
}

void ClientWidget::on_pushButtonNomUtilisateur_clicked()
{
    typeDeDemande="u";
    socketDeDialogueAvecServeur->write(typeDeDemande.toLatin1());
}

void ClientWidget::on_pushButtonArchitecture_clicked()
{
    typeDeDemande="a";
    socketDeDialogueAvecServeur->write(typeDeDemande.toLatin1());
}

void ClientWidget::on_pushButtonOS_clicked()
{
    typeDeDemande="o";
    socketDeDialogueAvecServeur->write(typeDeDemande.toLatin1());
}

void ClientWidget::onQTcpSocket_connected()
{
     ui->textEditEtatConnexion->append("connected");
     ui->groupBox_2->show();
     ui->lineEditAdresseIp->setEnabled(false);
     ui->lineEditNumeroPort->setEnabled(false);
}

void ClientWidget::onQTcpSocket_disconnected()
{
     ui->textEditEtatConnexion->append("disconnected");
     ui->groupBox_2->hide();
     ui->lineEditAdresseIp->setEnabled(true);
     ui->lineEditNumeroPort->setEnabled(true);
}

void ClientWidget::onQTcpSocket_error(QAbstractSocket::SocketError socketError)
{
    ui->textEditEtatConnexion->append(socketDeDialogueAvecServeur->errorString());
}

void ClientWidget::onQTcpSocket_hostFound()
{
    ui->textEditEtatConnexion->append("hostFound");
}

void ClientWidget::onQTcpSocket_stateChanged(QAbstractSocket::SocketState socketState)
{
    QString message;
    switch (socketState)
    {
       case QAbstractSocket::UnconnectedState:
          message = "etat déconnecté";
          break;

       case QAbstractSocket::HostLookupState:
          message = "socket recherche un nom d'hote";
          break;

    case QAbstractSocket::ConnectingState:
       message = "etat connecté";
       break;

    case QAbstractSocket::ConnectedState:
       message = "etat connecté";
       break;

    case QAbstractSocket::BoundState:
       message = "la socket est liée avec le port et l'ip";
       break;

    case QAbstractSocket::ClosingState:
       message = "etat fermé";
       break;

    case QAbstractSocket::ListeningState:
       message = "etat d'écoute";
       break;

    }
     ui->textEditEtatConnexion->append(message);

}

void ClientWidget::onQTcpSocket_aboutToClose()
{
    ui->textEditEtatConnexion->append("about to close");
}

void ClientWidget::onQTcpSocket_bytesWritten(qint64 bytes)
{
     ui->textEditEtatConnexion->append(" ");
}

void ClientWidget::onQTcpSocket_readChannelFinished()
{
     ui->textEditEtatConnexion->append("read Channel Finished");
}

void ClientWidget::onQTcpSocket_readyRead()
{
    ui->textEditEtatConnexion->append("Ready Read");
    QByteArray data= socketDeDialogueAvecServeur->readAll();
    qDebug()<<typeDeDemande.at(0).toLatin1();
    switch (typeDeDemande.at(0).toLatin1()) {
    case 'u':
        ui->lineEditNomUtilisateur->setText(data);
        break;
    case 'c':
        ui->lineEditNomOrdinateur->setText(data);
        break;
    case 'o':
        ui->lineEditOS->setText(data);
        break;
    case 'a':
        ui->lineEditArchitecture->setText(data);
        break;
    default:
        break;
    }

}
