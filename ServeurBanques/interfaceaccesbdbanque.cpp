#include "interfaceaccesbdbanque.h"


InterfaceAccesBDBanque::InterfaceAccesBDBanque(QString hote, QString bd, QString login, QString mdp)
{

}

float InterfaceAccesBDBanque::ObtenirSolde(int numCompte)
{
    QSqlQuery solde;
    bool existe = false;
    solde.prepare("select solde from comptes where idCompte=:id;");
    solde.bindValue(":id",numCompte);
    solde.exec();
    if (!solde.exec())
    {
       qDebug() << "pb requete" << solde.lastError();
    }
    // si le solde existe on passe existe a vrai
    if (solde.size()!=0)
    {
        existe=true;
    }
    return existe;
}

void InterfaceAccesBDBanque::MettreAJourLeSolde(int numCompte, float nouveauSolde)
{


}

void InterfaceAccesBDBanque::CreerCompte(int numCompte)
{
    QSqlQuery compte;
    bool existe = false;
    compte.prepare("select solde from comptes where idCompte=:id;");
    compte.bindValue(":id",numCompte);
    compte.exec();
    if (!compte.exec())
    {
       qDebug() << "pb requete" << compte.lastError();
    }
    // si le solde existe on passe existe a vrai
    if (compte.size()!=0)
    {
        existe=true;
    }


}

bool InterfaceAccesBDBanque::CompteExiste(int numCompte)
{
    QSqlQuery requete;
    bool existe=false;
    requete.prepare("select solde from comptes where idCompte=:id;");
    requete.bindValue(":id",numCompte);
    requete.exec();
    if (!requete.exec()){
        qDebug()<<"pb requete compte existe "<<requete.lastError();
    }
    // si le compte existe on passe existe a vrai
    if (requete.size()!=0)
    {
        existe=true;
    }
    return existe;
}
