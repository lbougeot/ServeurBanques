#include "widgetbanque.h"
#include "ui_widgetbanque.h"
#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

WidgetBanque::WidgetBanque(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetBanque)
{
    ui->setupUi(this);




}

WidgetBanque::~WidgetBanque()
{
    delete ui;

}


void WidgetBanque::on_pushButtonConnexionBaseDeDonnees_clicked()
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
         ui->textEditInformation->setEnabled(true);
         ui->pushButtonAfficherInformations->setEnabled(true);
    }
}

void WidgetBanque::on_pushButtonAfficherInformations_clicked()
{

    QSqlQuery requete("select nom, prenom , idCompte, solde from comptes;");
    if (!requete.exec()){
            qDebug()<<"pb requete "<<requete.lastError();
        }
    QString nom;
    QString prenom;
    QString idCompte;
    QString solde;

    while(requete.next())
    {
        nom=requete.value("nom").toString();
        prenom=requete.value("prenom").toString();
        idCompte=requete.value("idCompte").toString();
        solde=requete.value("solde").toString();
        ui->textEditInformation->append(nom);
        ui->textEditInformation->append(prenom);
        ui->textEditInformation->append(idCompte);
        ui->textEditInformation->append(solde);

    }

}
