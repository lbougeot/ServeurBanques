#ifndef WIDGETBASEDEDONNEES_H
#define WIDGETBASEDEDONNEES_H

#include <QWidget>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class WidgetBaseDeDonnees; }
QT_END_NAMESPACE

class WidgetBaseDeDonnees : public QWidget
{
    Q_OBJECT

public:
    WidgetBaseDeDonnees(QWidget *parent = nullptr);
    ~WidgetBaseDeDonnees();


private slots:


    void on_pushButtonNomDepartement_clicked();



    void on_comboBoxRegions_currentIndexChanged(int index);

    void on_comboBoxDepartements_currentIndexChanged(int index);

    void on_comboBoxVilles_currentIndexChanged(int index);

private:
    Ui::WidgetBaseDeDonnees *ui;
    QSqlDatabase bd;

};
#endif // WIDGETBASEDEDONNEES_H
