#include "widgettableau.h"
#include "ui_widgettableau.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

WidgetTableau::WidgetTableau(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetTableau)
{
    ui->setupUi(this);
}

WidgetTableau::~WidgetTableau()
{
    delete ui;
}





void WidgetTableau::on_pushButtonConnexionBaseDeDonnees_clicked()
{
    bd=QSqlDatabase::addDatabase("QMYSQL");
    bd.setHostName("172.18.58.14");
    bd.setDatabaseName("banque");
    bd.setUserName("snir");
    bd.setPassword("snir");
    if (!bd.open())
    {
        QMessageBox erreur;
        erreur.setText("pb d'ouverture");
        qDebug()<< "pb ouverture" << bd.lastError();
    }
    else
    {
         qDebug()<< "ouverture bdd ok";
         ui->groupBoxConnexion->setEnabled(false);
         ui->groupBoxInfosComptes->setEnabled(true);
         ui->tableWidgetInfos->setEnabled(true);
         ui->pushButtonAfficherInformations->setEnabled(true);
    }
}


void WidgetTableau::on_pushButtonAfficherInformations_clicked()
{

    QSqlQuery requete("select nom, prenom , idCompte, solde from comptes;");
    if (!requete.exec()){
            qDebug()<<"pb requete "<<requete.lastError();
        }
    QString nom;
    QString prenom;
    QString idCompte;
    QString solde;
    int ligne=0;    // numero de la ligne
    int col=0;      // numero de la colonne

    while(requete.next())
    {
        nom=requete.value("nom").toString();
        prenom=requete.value("prenom").toString();
        idCompte=requete.value("idCompte").toString();
        solde=requete.value("solde").toString();

        // ajouter une ligne au tableau
          ui->tableWidgetInfos->insertRow(ui->tableWidgetInfos->rowCount());
          col = 0;
          // ajouter un nom
          QTableWidgetItem *nomItem = new QTableWidgetItem(nom);
          ui->tableWidgetInfos->setItem(ligne,col,nomItem);
          col++;
          // ajouter un prenom
          QTableWidgetItem *prenomItem = new QTableWidgetItem(prenom);
          ui->tableWidgetInfos->setItem(ligne,col,prenomItem);
          col++;
          // ajouter le numero de compte
          QTableWidgetItem *idCompteItem = new QTableWidgetItem(idCompte);
          ui->tableWidgetInfos->setItem(ligne,col,idCompteItem);
          col++;
          // ajouter le solde
          QTableWidgetItem *soldeItem = new QTableWidgetItem(solde);
          ui->tableWidgetInfos->setItem(ligne,col,soldeItem);
          ligne++;
    }



}
