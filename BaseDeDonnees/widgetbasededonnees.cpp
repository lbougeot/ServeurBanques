#include "widgetbasededonnees.h"
#include "ui_widgetbasededonnees.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

WidgetBaseDeDonnees::WidgetBaseDeDonnees(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WidgetBaseDeDonnees)
{
    ui->setupUi(this);
    bd=QSqlDatabase::addDatabase("QMYSQL");
    bd.setHostName("172.18.58.7");
    bd.setDatabaseName("france2018");
    bd.setUserName("snir");
    bd.setPassword("snir");
    if (!bd.open())
    {
        qDebug()<< "pb ouverture" << bd.lastError();
    }
    else
    {
         qDebug()<< "ouverture bdd ok";
    }

    QSqlQuery requete("select code, name from regions order by name;");
    if (!requete.exec()){
            qDebug()<<"pb requete "<<requete.lastError();
        }
        QString nom;
        QString id;

        while(requete.next())
        {
            nom=requete.value("name").toString();
            id=requete.value("code").toString();
            ui->comboBoxRegions->addItem(nom,id);
        }




        QSqlQuery requete2("select code, name from departments order by name;");
        if (!requete2.exec()){
                qDebug()<<"pb requete "<<requete2.lastError();
            }
            QString nom2;
            QString id2;

            while(requete2.next())
            {
                nom2=requete2.value("name").toString();
                id2=requete2.value("code").toString();
                ui->comboBoxDepartements->addItem(nom2,id2);
            }


}

WidgetBaseDeDonnees::~WidgetBaseDeDonnees()
{
    delete ui;
}




void WidgetBaseDeDonnees::on_pushButtonNomDepartement_clicked()
{
    QString numeroDepartement = ui->lineEditNumeroDepartement->text();
    QSqlQuery requete;
    requete.prepare("select name from departments where code=:nro ;");
    requete.bindValue(":nro",numeroDepartement);
    if (!requete.exec()){
        qDebug()<<"pb requete :" << requete.lastError();

}
else
    {
        requete.next();
        ui->labelNomDepartement->setText(
                    requete.value("name").toString());
    }








}



void WidgetBaseDeDonnees::on_comboBoxRegions_currentIndexChanged(int index)
{


        // recupere l'id de la region
        QString idRegion=ui->comboBoxRegions->itemData(index).toString();
        // vider la liste des departements
        ui->comboBoxDepartements->clear();
        ui->comboBoxDepartements->addItem("Choisissez un département");

        QSqlQuery requete;
        requete.prepare("select code,name from departments where region_code=:id;");
        requete.bindValue(":id",idRegion);
        if (!requete.exec()){
                qDebug()<<"pb requete "<<requete.lastError();
            }
            QString nom;
            QString id;

            while(requete.next())
            {
                nom=requete.value("name").toString();
                id=requete.value("code").toString();
                ui->comboBoxDepartements->addItem(nom,id);
            }

}

void WidgetBaseDeDonnees::on_comboBoxDepartements_currentIndexChanged(int index)
{
    // recupere l'id du departement
    QString idDepartement=ui->comboBoxDepartements->itemData(index).toString();
    // vider la liste des villes
    ui->comboBoxVilles->clear();
    ui->comboBoxVilles->addItem("Choisissez une Ville");

    QSqlQuery requete;
    requete.prepare("select id,name from cities where department_code=:id;");
    requete.bindValue(":id",idDepartement);
    if (!requete.exec()){
            qDebug()<<"pb requete "<<requete.lastError();
        }
        QString nom;
        QString id;

        while(requete.next())
        {
            nom=requete.value("name").toString();
            id=requete.value("id").toString();
            ui->comboBoxVilles->addItem(nom,id);
        }
}

void WidgetBaseDeDonnees::on_comboBoxVilles_currentIndexChanged(int index)
{

}
