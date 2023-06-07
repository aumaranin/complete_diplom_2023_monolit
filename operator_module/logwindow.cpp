#include "logwindow.h"
#include "ui_logwindow.h"
#include "global.h"

using namespace std;

LogWindow::LogWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogWindow)
{
    ui->setupUi(this);
    ui->tableWidgetLog->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    refresh();
}

LogWindow::~LogWindow()
{
    delete ui;
}

void LogWindow::refresh()
{
    listWidgets.clear();

    vector<ReportFromDb> listReports = Global::getInstance().getDataBase()->readAllReports();
    ui->tableWidgetLog->setRowCount(listReports.size());
    for (int i = 0; i < listReports.size(); i++)
    {
        shared_ptr<QTableWidgetItem> newDate = make_shared<QTableWidgetItem>();
        newDate->setText(QString::fromStdString(listReports.at(i).getDate()));
        listWidgets.push_back(newDate);
        ui->tableWidgetLog->setItem(ui->tableWidgetLog->rowCount()-i-1, 0, newDate.get());

        shared_ptr<QTableWidgetItem> newConfigName = make_shared<QTableWidgetItem>();
        newConfigName->setText(QString::fromStdString(listReports.at(i).getConfigName()));
        listWidgets.push_back(newConfigName);
        ui->tableWidgetLog->setItem(ui->tableWidgetLog->rowCount()-i-1, 1, newConfigName.get());

        shared_ptr<QTableWidgetItem> newZone = make_shared<QTableWidgetItem>();
        newZone->setText(QString::fromStdString(listReports.at(i).getZone()));
        listWidgets.push_back(newZone);
        ui->tableWidgetLog->setItem(ui->tableWidgetLog->rowCount()-i-1, 2, newZone.get());

        shared_ptr<QTableWidgetItem> newClassObject = make_shared<QTableWidgetItem>();
        newClassObject->setText(QString::fromStdString(listReports.at(i).getClassObject()));
        listWidgets.push_back(newClassObject);
        ui->tableWidgetLog->setItem(ui->tableWidgetLog->rowCount()-i-1, 3, newClassObject.get());

        shared_ptr<QTableWidgetItem> newReason = make_shared<QTableWidgetItem>();
        newReason->setText(QString::fromStdString(listReports.at(i).getReason()));
        listWidgets.push_back(newReason);
        ui->tableWidgetLog->setItem(ui->tableWidgetLog->rowCount()-i-1, 4, newReason.get());
    }

}

void LogWindow::on_btnRefresh_clicked()
{
    refresh();
}

