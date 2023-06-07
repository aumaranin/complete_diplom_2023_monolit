#include "newcamera2.h"
#include "ui_newcamera2.h"
#include "serviceFunctions.hpp"
#include "global.h"
#include <vector>
#include <QFileDialog>

#include <iostream>

Newcamera2::Newcamera2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Newcamera2)
{
    ui->setupUi(this);
    this->setFixedSize(this->width(), 320);
    ui->radioButtonIpCam->click();
    ui->warningLabel->hide();
    QFileDialog *fileDialog = new QFileDialog();
    //fileDialog->show();
}

Newcamera2::~Newcamera2()
{
    delete ui;
}

void Newcamera2::on_radioButtonIpCam_clicked()
{
    ui->ipGroup->show();
    ui->usbGroup->hide();
    ui->videoTapeGroup_2->hide();
}

void Newcamera2::on_radioButtonUsbCam_clicked()
{
    ui->usbGroup->show();
    ui->ipGroup->hide();
    ui->videoTapeGroup_2->hide();

    // Поиск всех usb-камер
    std::vector<std::string> usbCams = sf::executeCommand("ls /dev | grep video");
    ui->deviceComboBox->clear();
    for (std::string item: usbCams)
    {
        std::string usbAddress = "/dev/" + item;
        ui->deviceComboBox->addItem(QString::fromStdString(usbAddress));
    }
}

void Newcamera2::on_radioButtonVideoTape_clicked()
{
    ui->usbGroup->hide();
    ui->ipGroup->hide();
    ui->videoTapeGroup_2->show();
}

void Newcamera2::on_backButton_clicked()
{
    this->close();
}

void Newcamera2::on_addCameraButton_clicked()
{    
    // Проверка для IP-камеры
    if (ui->radioButtonIpCam->isChecked())
    {
        bool flag = true;
        QString cameraName = ui->ipCameraLineEdit->text();
        QString cameraAddress = ui->ipAdressLineEdit->text();
        QString username = ui->usernameLineEdit->text();
        QString password = ui->passwordLineEdit->text();

        //Проверка имени камеры не пустое ли оно
        if (!cameraName.trimmed().length())
        {
            ui->warningLabel->setText("Название камеры не введено.");
            ui->warningLabel->setStyleSheet("QLabel {color: red;}");
            ui->warningLabel->setVisible(true);
            flag = false;
        }

        //Проверка, правильно ли введен IP-адресс и порт        
        else if (!cameraAddress.length()) //|| !sf::verifyIp(cameraAddress.toStdString()))
        {
            ui->warningLabel->setText("IP-адрес введен неверно.");
            ui->warningLabel->setStyleSheet("QLabel {color: red;}");
            ui->warningLabel->setVisible(true);
            flag = false;
        }        

        //Добавление IP-камеры
        if (flag)
        {
            //ui->warningLabel->setText("Камера добавлена.");
            //ui->warningLabel->setStyleSheet("QLabel {color: green;}");
            //ui->warningLabel->setVisible(true);
            Source *newCamera = IpCamera::create(cameraName.toStdString(), cameraAddress.toStdString(), username.toStdString(), password.toStdString());
            Global::getInstance().getConfiguration()->setSource(newCamera);
            std::cout << newCamera->toJson() << endl;
            this->close();
            //emit cameraAdded();
        }

    }
    // Проверка для USB-камеры
    else if (ui->radioButtonUsbCam->isChecked())
    {
        bool flag = true;
        QString cameraName = ui->usbCameraLineEdit->text();
        QString deviceName = ui->deviceComboBox->currentText();

        //Проверка имени камеры не пустое ли оно
        if (!cameraName.trimmed().length())
        {
            ui->warningLabel->setText("Название камеры не введено.");
            ui->warningLabel->setStyleSheet("QLabel {color: red;}");
            ui->warningLabel->setVisible(true);
            flag = false;
        }

        //Добавление USB-камеры
        if (flag)
        {
            //ui->warningLabel->setText("Камера добавлена.");
            //ui->warningLabel->setStyleSheet("QLabel {color: green;}");
            //ui->warningLabel->setVisible(true);

            Source *newCamera = UsbCamera::create(cameraName.toStdString(), deviceName.toStdString());
            Global::getInstance().getConfiguration()->setSource(newCamera);
            std::cout << newCamera->toJson() << endl;
            this->close();
            //emit cameraAdded();
        }
    }
    else
    {
        QString videotapeName = ui->videoTapeNameLineEdit->text();
        QString fileName = ui->fileNameLineEdit->text();
        if (!fileName.trimmed().size())
        {
            ui->warningLabel->setText("Имя файла не введено.");
            ui->warningLabel->setStyleSheet("QLabel {color: red;}");
            ui->warningLabel->setVisible(true);
        }
        else if (!videotapeName.trimmed().size())
        {
            ui->warningLabel->setText("Название видеозаписи не введено.");
            ui->warningLabel->setStyleSheet("QLabel {color: red;}");
            ui->warningLabel->setVisible(true);
        }
        else
        {
            Source *newCamera = VideoTape::create(videotapeName.toStdString(), fileName.toStdString());
            Global::getInstance().getConfiguration()->setSource(newCamera);
            std::cout << newCamera->toJson() << endl;
            this->close();
        }
    }
}




void Newcamera2::on_btnFileBrowser_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this, "Выберите видеозапись", "./");
    ui->fileNameLineEdit->setText(fileName);
}

