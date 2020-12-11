#ifndef SERVEURBANQUE_H
#define SERVEURBANQUE_H

#include <QObject>
#include <QTcpSocket>
#include <QTcpServer>
#include <QMessageBox>
#include "compteclient.h"
#include <QBuffer>
class ServeurBanque : public QTcpServer
{
    Q_OBJECT
public:
    ServeurBanque(QObject *parent = nullptr);
    void Start();
    void Stop();
    void EnvoyerMessage(QString msg,CompteClient *client);

private slots:
    void onServeurBanque_newConnection();
    void onCompteClient_disconnected();
    void onCompteClient_readyRead();

private:

    QList<CompteClient*> lesConnexionsClients;


};

#endif // SERVEURBANQUE_H
