#include "configurationlistwindow.h"
#include "./ui_configurationlistwindow.h"
#include "settingdatabasewindow.h"
#include "configurationmenu.h"

#include "DataBase.h"
#include "global.h"
#include "configuration.h"

#include <string>
#include <vector>
#include <QLabel>

#include <iostream>
#include <QDebug>

using namespace std;

ConfigurationListWindow::ConfigurationListWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ConfigurationListWindow)
{
    ui->setupUi(this);    
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->btnAddConf->setEnabled(false);
    ui->btnChangeConf->setEnabled(false);
    ui->btnDeleteConf->setEnabled(false);
}

ConfigurationListWindow::~ConfigurationListWindow()
{
    delete ui;
}

void ConfigurationListWindow::showConfigs()
{
    ui->tableWidget->clear();
    vector<string> configurationNames = Global::getInstance().getDataBase()->getListConfigurationNames();
    ui->tableWidget->setRowCount(configurationNames.size());
    for (int i = 0; i < configurationNames.size(); i++)
    {
        QString qname = QString::fromStdString(configurationNames.at(i));
        QTableWidgetItem *item = new QTableWidgetItem();
        item->setText(qname);
        ui->tableWidget->setItem(i,0, item);
    }
}


void ConfigurationListWindow::on_btnSetDatabase_clicked()
{
    SettingDatabaseWindow *settingdatabasewindow = new SettingDatabaseWindow;
    connect(settingdatabasewindow, SIGNAL(databaseInfoEntered()), this, SLOT(showConfigs()));
    connect(settingdatabasewindow, SIGNAL(databaseInfoEntered()), this, SLOT(dataBaseSet()));
    settingdatabasewindow->show();
}


void ConfigurationListWindow::on_btnAddConf_clicked()
{
    /*
    std::string json_object = R"({"age": 13, "name": "Вася", "nums" : [1, 2, 3]})";
    Global::getInstance().getDataBase()->writeConfiguration("first", json_object);
    Global::getInstance().getDataBase()->writeConfiguration("second", json_object);
    Global::getInstance().getDataBase()->writeConfiguration("third", json_object);
*/

    ConfigurationMenu *configurationMenu = new ConfigurationMenu();
    Configuration *newConfiguration = new Configuration();
    Global::getInstance().setConfiguration(newConfiguration);
    configurationMenu->configuration = newConfiguration;
    connect(configurationMenu, SIGNAL(configuration_entered()), this, SLOT(showConfigs()));
    configurationMenu->show();
}


void ConfigurationListWindow::on_btnDeleteConf_clicked()
{
    auto configurationList = ui->tableWidget->selectedItems();
    for (QTableWidgetItem* item : configurationList)
    //for (int i = 0; i < configurationList.size(); i++)
    {
        //auto item = configurationList.at(i);
        Global::getInstance().getDataBase()->removeConfiguration(item->text().toStdString());
    }
    showConfigs();
    qDebug() << "Конфигурации удалены";
}


void ConfigurationListWindow::on_btnChangeConf_clicked()
{
    // TO-DO Дописать в файл конфигураций загрузку конфы из JSON-объекта

    auto selectedConfList = ui->tableWidget->selectedItems();
    if (selectedConfList.size())
    {
        ConfigurationMenu *configurationMenu = new ConfigurationMenu();
        std::string selectedConfigurationName = selectedConfList.at(0)->text().toStdString();
        std::string jsonConf = Global::getInstance().getDataBase()->readConfiguration(selectedConfigurationName);
        Configuration *loadedConfiguration = new Configuration(jsonConf);
        Global::getInstance().setConfiguration(loadedConfiguration);
        configurationMenu->configuration = loadedConfiguration;
        connect(configurationMenu, SIGNAL(configuration_entered()), this, SLOT(showConfigs()));
        configurationMenu->show();
    }
}

void ConfigurationListWindow::dataBaseSet()
{
    ui->btnAddConf->setEnabled(true);
    ui->btnChangeConf->setEnabled(true);
    ui->btnDeleteConf->setEnabled(true);
}

