#ifndef COMPTECLIENT_H
#define COMPTECLIENT_H

#include <QObject>
#include <QTcpSocket>
#include "interfaceaccesbdbanque.h"

class CompteClient : public QTcpSocket
{
    Q_OBJECT
public:
    CompteClient(QObject *parent = nullptr);
    bool Retirer(float montant);
    void Deposer(float montant);
    float ObtenirSolde();
    int DefinirNumCompte(int nc);
    int ObtenirNumCompte();
  //  InterfaceAccesBDBanque bd;

private:
    int numCompte;
    float solde;


};

#endif // COMPTECLIENT_H
