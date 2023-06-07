#include "global.h"
#include "settingdatabasewindow.h"
#include "ui_settingdatabasewindow.h"

SettingDatabaseWindow::SettingDatabaseWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDatabaseWindow)
{
    ui->setupUi(this);
    ui->databaseTypesBox->addItem("Mongodb");
    ui->databaseTypesBox->addItem("PostrgreSQL");
}

SettingDatabaseWindow::~SettingDatabaseWindow()
{
    delete ui;
}

void SettingDatabaseWindow::on_btnBack_clicked()
{
    this->close();
}


void SettingDatabaseWindow::on_btnCofirm_clicked()
{
    Global::getInstance().setDataBase(ui->addressDataBaseLineEdit->text().toStdString(), ui->usernameLineEdit->text().toStdString(), ui->passwordLineEdit->text().toStdString());
    emit databaseInfoEntered();
    this->close();
}

