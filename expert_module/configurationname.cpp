#include "configurationname.h"
#include "ui_configurationname.h"
#include "global.h"

ConfigurationName::ConfigurationName(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ConfigurationName)
{
    ui->setupUi(this);
    ui->lineEditConfigurationName->setText(QString::fromStdString(Global::getInstance().getConfiguration()->getName()));
}

ConfigurationName::~ConfigurationName()
{
    delete ui;
}

bool ConfigurationName::verifyConfigurationName(QString configurationName)
{
    bool result = false;
    if (configurationName.trimmed().size())
        result = true;
    return result;
}

void ConfigurationName::on_btnBack_clicked()
{
    this->close();
}


void ConfigurationName::on_btnConfirm_clicked()
{
    if (verifyConfigurationName(ui->lineEditConfigurationName->text()))
    {
        Global::getInstance().getConfiguration()->setName(ui->lineEditConfigurationName->text().toStdString());
        this->close();
    }
    else
        ui->statusbar->showMessage("Формат названия конфигурации неверен.");
}

