#include "serveurbanque.h"


ServeurBanque::ServeurBanque(QObject *parent): QTcpServer(parent)
{


   if(!connect(this,&QTcpServer::newConnection,this,&ServeurBanque::onServeurBanque_newConnection))
   {
     QMessageBox message;
     message.setText("Erreur de liaison");
     message.exec();
   }


}

void ServeurBanque::Start()
{
    if (this->listen(QHostAddress::Any,8888))
       {
        connect(this,&QTcpServer::newConnection,this,&ServeurBanque::onServeurBanque_newConnection);
        qDebug() << "Le serveur est lancé";
       }
    else
    {
        QMessageBox message2;
        message2.setText("Erreur");
        message2.exec();
        this->close();
    }
}


void ServeurBanque::Stop()
{
    this->close();
}

void ServeurBanque::EnvoyerMessage(QString msg, CompteClient *client)
{              
    quint16 taille = 0;
    QBuffer tampon;
    tampon.open(QIODevice::WriteOnly);
    // association du tampon au flux de sortie
    QDataStream out (&tampon);
    // construction de la trame
    out << taille << msg;
    // calcul de la taille de la trame
    taille=tampon.size()-sizeof (taille);
    // placement sur la première position du flux pour pouvoir modifier la taille
    tampon.seek(0);
    // modification de la trame avec la taille reel sur la trame
    out<<taille;
    // envoi du QByteArray du tampon via la socket
    client->write(tampon.buffer());
}

void ServeurBanque::onServeurBanque_newConnection()
{
    CompteClient *client;
    while (hasPendingConnections())
    {
        client = static_cast<CompteClient*>(this->nextPendingConnection());
        connect(client,&QTcpSocket::disconnected,this,&ServeurBanque::onCompteClient_disconnected);
        connect(client,&QTcpSocket::readyRead,this,&ServeurBanque::onCompteClient_readyRead);
        lesConnexionsClients.append(client);
        EnvoyerMessage("Quel est ton numéro de compte",client);
    }

}

void ServeurBanque::onCompteClient_disconnected()
{
    CompteClient *client=(CompteClient*)sender();
    if(!client)
    {
        QMessageBox msg;
        msg.setText("erreur de connexion:"+client->errorString());
        msg.exec();
    }
    else
    {
        lesConnexionsClients.removeOne(client);
        client->deleteLater();
    }
}

void ServeurBanque::onCompteClient_readyRead()
{
    quint16 taille = 0;
    QChar commande;
    QString reponse;
    float montant;
    int numCompte;
    CompteClient *client = (CompteClient *)sender();

    if(!client)
    {
        QMessageBox message;
        message.setText("Erreur de lecture : "+client->errorString());
        message.exec();
    }
    else
    {
    if(client->bytesAvailable() > 0)
                    {
                        QDataStream in(client);
                        in>>taille;
                        in>>commande;
                        switch(commande.toLatin1())
                        {
                        case 'N' :
                            in >> numCompte;
                            break;
                        case 'R':
                            in >> montant;
                            break;
                        case 'D':
                            in >> montant;
                            break;
                        }
                    }


       switch (commande.toLatin1())
       {
         case 'N':
         client->DefinirNumCompte(numCompte);
         EnvoyerMessage("Bienvenue sur le compte " + QString::number(numCompte),client);
         break;

         case 'R':
         if(montant > 0)
         client->Retirer(montant);
         EnvoyerMessage("nouveau solde: " + QString::number(client->ObtenirSolde()),client);
         break;

         case 'D':
         client->Deposer(montant);
         EnvoyerMessage("nouveau solde: " + QString::number(client->ObtenirSolde()),client);
         break;

         case 'S':
         EnvoyerMessage("Solde: "+QString::number(client->ObtenirSolde()),client);
        break;
      }
  }
}
