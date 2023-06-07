#include "configurationmenu.h"
#include "ui_configurationmenu.h"
#include "configurationname.h"
#include "newcamera2.h"
#include "drawningZoneWindow.h"
#include "setrulewindow.h"
#include "global.h"

ConfigurationMenu::ConfigurationMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationMenu)
{
    ui->setupUi(this);
}

ConfigurationMenu::~ConfigurationMenu()
{
    delete ui;
}

void ConfigurationMenu::on_btnSetName_clicked()
{
    ConfigurationName *configurationNameWindow = new ConfigurationName();
    configurationNameWindow->show();
}


void ConfigurationMenu::on_btnBack_clicked()
{
    this->close();
}


void ConfigurationMenu::on_btnSetSource_clicked()
{
    Newcamera2 *newCameraWindow = new Newcamera2();
    newCameraWindow->show();
}


void ConfigurationMenu::on_btnSetZone_clicked()
{
    MainWindow *drawningWindow = new MainWindow();
    drawningWindow->show();
}


void ConfigurationMenu::on_btnSetRule_clicked()
{
    SetRuleWindow *setRuleWindow = new SetRuleWindow(this);
    setRuleWindow->show();
}


void ConfigurationMenu::on_btnConfirm_clicked()
{
    Global::getInstance().getDataBase()->writeConfiguration(Global::getInstance().getConfiguration()->getName(), Global::getInstance().getConfiguration()->toJson());
    cout << "Конфигурация: \n" << Global::getInstance().getConfiguration()->toJson() << endl;
    emit configuration_entered();
    this->close();
}

