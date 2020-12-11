#include "compteclient.h"


CompteClient::CompteClient(QObject *parent) : QTcpSocket(parent)
{

}

bool CompteClient::Retirer(float montant)
{
  bool reponse;
  if( montant < solde )
  {
      solde = solde - montant;
      reponse = true;
  }
  else
  {
      reponse = false;
  }
  return reponse;
}

void CompteClient::Deposer(float montant)
{
  solde = montant + solde;
}

float CompteClient::ObtenirSolde()
{
    return solde;
}

int CompteClient::DefinirNumCompte(int nc)
{
    numCompte = nc;
    solde = 200;
}

int CompteClient::ObtenirNumCompte()
{
    return numCompte;
}


