#include "setrulewindow.h"
#include "ui_setrulewindow.h"

#include <QDebug>
#include <QCheckBox>
#include <fstream>
#include <string>
#include <vector>
#include "global.h"
#include "zone.h"
#include "rule.h"
#include "systemreaction.h"

const std::vector<std::string> &SetRuleWindow::getListMajorClasses() const
{
    return listMajorClasses;
}

void SetRuleWindow::setListMajorClasses(const std::vector<std::string> &newListMajorClasses)
{
    listMajorClasses = newListMajorClasses;
}

const std::vector<std::string> &SetRuleWindow::getListMinorClasses() const
{
    return listMinorClasses;
}

void SetRuleWindow::setListMinorClasses(const std::vector<std::string> &newListMinorClasses)
{
    listMinorClasses = newListMinorClasses;
}

const std::vector<QCheckBox *> &SetRuleWindow::getListCheckBoxProperties() const
{
    return listCheckBoxProperties;
}

void SetRuleWindow::setListCheckBoxProperties(const std::vector<QCheckBox *> &newListCheckBoxProperties)
{
    listCheckBoxProperties = newListCheckBoxProperties;
}

SetRuleWindow::SetRuleWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetRuleWindow)
{
    // Временно убрал чекбоксы notify и saveFrame
    //ui->checkBoxNotifyOperator->hide();
    //ui->checkBoxSaveFrame->hide();


    ui->setupUi(this);
    statusBar = new QStatusBar(this);
    this->layout()->addWidget(statusBar);

    //Добавление в comboBox размеченных зон
    std::vector<Zone *> listZone = Global::getInstance().getConfiguration()->getListZone();
    for (Zone* zone : listZone)
    {
        ui->comboBoxZone->addItem(QString::fromStdString(zone->getName()));
    }

    std::ifstream majorClassesFile("../resources/classes/major.names");
    std::ifstream minorClassesFile("../resources/classes/minor.names");
    std::string className;
    while (majorClassesFile >> className)
        listMajorClasses.push_back(className);
    while (minorClassesFile >> className)
        listMinorClasses.push_back(className);
    for (std::string className : listMajorClasses)
        ui->comboBoxMajorClass->addItem(QString::fromStdString(className));

    for (std::string className : listMinorClasses)
    {
        QCheckBox *checkBox = new QCheckBox(this);
        checkBox->setText(QString::fromStdString(className));
        ui->groupBoxProperties->layout()->addWidget(checkBox);
        listCheckBoxProperties.push_back(checkBox);
    }
    this->setMaximumHeight(400);
    ui->groupBoxBashScript->hide();    
}

SetRuleWindow::~SetRuleWindow()
{
    delete ui;
}

void SetRuleWindow::on_checkBoxExecuteBash_stateChanged(int arg1)
{
    if (ui->checkBoxExecuteBash->isChecked())
        ui->groupBoxBashScript->show();
    else
        ui->groupBoxBashScript->hide();
}

void SetRuleWindow::on_btnBack_clicked()
{
    this->close();
}


void SetRuleWindow::on_btnConfirm_clicked()
{
    if (!ui->lineEditRuleName->text().trimmed().size())
        statusBar->showMessage("Название правило введено неверно.");
    else
    {
        Rule *newRule = new Rule();

        // Ввод названия
        newRule->setName(ui->lineEditRuleName->text().trimmed().toStdString());

        // Ввод зоны
        std::vector<Zone *> listZone = Global::getInstance().getConfiguration()->getListZone();
        std::string zoneName = ui->comboBoxZone->currentText().toStdString();
        for (Zone* zone : listZone)
        {
            if (zone->getName() == zoneName)
            {
                newRule->setZone(zone);
                break;
            }
        }

        // Ввод основного класса
        newRule->setMajorClass(ui->comboBoxMajorClass->currentText().toStdString());

        //задание правилу списка свойств
        std::vector<std::string> listProperties;
        for (QCheckBox *item : getListCheckBoxProperties())
        {
             if (item->isChecked())
                 listProperties.push_back(item->text().toStdString());
        }
        newRule->setListProperties(listProperties);

        // задание списка действий (реакции системы) новому правилу.
        std::vector<SystemReaction *> listSystemReaction;
        SystemReaction *reaction;
        /*
        if (ui->checkBoxNotifyOperator->isChecked())
        {
            reaction = new NotifyOperator();
            std::cout << reaction->toJson() << std::endl;
            listSystemReaction.push_back(reaction);
        }
        if (ui->checkBoxSaveFrame->isChecked())
        {
            reaction = new SaveFrame();
            std::cout << reaction->toJson() << std::endl;
            listSystemReaction.push_back(reaction);
        }
        */
        if (ui->checkBoxNoteToBd->isChecked())
        {
            reaction = new NoteToDatabase();
            std::cout << reaction->toJson() << std::endl;
            listSystemReaction.push_back(reaction);
        }
        if (ui->checkBoxExecuteBash->isChecked())
        {
            reaction = new BashScript(ui->lineEditBashFile->text().toStdString());
            std::cout << reaction->toJson() << std::endl;
            listSystemReaction.push_back(reaction);
        }
        newRule->setListSystemReaction(listSystemReaction);
        auto listRules = Global::getInstance().getConfiguration()->getListRule();
        listRules.push_back(newRule);
        Global::getInstance().getConfiguration()->setListRule(listRules);
        std::cout << newRule->toJson() << std::endl;

        // Ввод период сопоставления в конфигурацию. Проверка, является ли старое значение больше, чем новое. Вносится меньшее из двух.
        int oldPeriod = Global::getInstance().getConfiguration()->getPeriodComparison();
        if (oldPeriod > ui->spinBoxPeriodComparison->value())
            Global::getInstance().getConfiguration()->setPeriodComparison(ui->spinBoxPeriodComparison->value());

        this->close();
    }
}
