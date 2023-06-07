#include "drawningZoneWindow.h"
#include "./ui_drawningZoneWindow.h"
#include "segmentedimagelabel.h"
#include "zone.h"
#include <string>
#include <vector>
#include <QString>
#include "global.h"
#include <opencv2/opencv.hpp>
#include <memory>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QPixmap pix("../images/empty_image.png");
    //QPixmap *pix2 = new QPixmap("../images/empty_image.png");
    //ui->lblMouse->setPixmap(*pix2);
    std::shared_ptr<QPixmap> pix2 = std::make_shared<QPixmap>("../resources/images/empty_image.png");
    // Подключение кадра к метке
    ui->lblMouse->setFrame(pix2);

    // Настройка сегментов
    int defaultSegmentSize = 10;
    ui->lblMouse->setSegmentSize(defaultSegmentSize);
    ui->spinBoxSegmentSize->setMinimum(5);
    ui->spinBoxSegmentSize->setMaximum(100);
    ui->spinBoxSegmentSize->setValue(defaultSegmentSize);

    ui->btnEdit1->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

QPixmap MainWindow::MatToPic(cv::Mat src)
{
    QImage::Format format=QImage::Format_RGB888;
    int bpp=src.channels();
    if(bpp==3)format=QImage::Format_RGB888;
    QImage img(src.cols,src.rows,format);
    uchar *sptr,*dptr;
    int linesize=src.cols*bpp;
    for(int y=0;y<src.rows;y++){
        sptr=src.ptr(y);
        dptr=img.scanLine(y);
        memcpy(dptr,sptr,linesize);
    }
    if(bpp==3)return QPixmap::fromImage(img.rgbSwapped());
    return QPixmap::fromImage(img);
}


void MainWindow::on_btnLoadScene_clicked()
{
    // Загрузка тестового изображения.
    /*
    std::shared_ptr<QPixmap> pix = std::make_shared<QPixmap>("../images/sample1.png");
    int height = pix->height();
    int width = pix->width();
    ui->lblMouse->setFrame(pix);
    ui->lblMouse->setFixedSize(width, height);
    ui->lblMouse->refreshMatrix();
    ui->lblMouse->setMode(Mode::NODRAW);
    */

    //Загрузка кадра из видеопотока
    string source;
    //source = "/media/data/OBS videos/2023-05-03 12-48-39.mkv";

    source = Global::getInstance().getConfiguration()->getSource()->getUrl();
    ui->lblMouse->setMode(Mode::DRAW_LINE);
    ui->statusbar->showMessage("Режим разметки активирован");

/*
    cv::VideoCapture inVid(source);
    if (!inVid.isOpened())
    {
        this->statusBar()->showMessage("Видеопоток не исправен");
    }
    else
    {


        int width = (int)inVid.get(cv::CAP_PROP_FRAME_WIDTH);
        int height = (int)inVid.get(cv::CAP_PROP_FRAME_HEIGHT);
        std::cout << "Размеры изображения: \n" << "\tШирина: " << width << "\n\tВысота: " << height << endl;
        cv::Mat inFrame;
        inVid >> inFrame;
        if (inFrame.empty())
        {
            this->statusBar()->showMessage("Кадры не загружаются");
        }
        else

        {
            shared_ptr<QPixmap> pix = make_shared<QPixmap>(MatToPic(inFrame));
            ui->lblMouse->setFrame(pix);
            ui->lblMouse->setFixedSize(width, height);
            ui->lblMouse->refreshMatrix();
            ui->lblMouse->setMode(Mode::DRAW_LINE);
            //ui->lblMouse->setMode(Mode::NODRAW);
        }



        {
            shared_ptr<QPixmap> pix = make_shared<QPixmap>(MatToPic(inFrame));
            QPixmap scaledPixmap = pix->scaled(1280, 720, Qt::AspectRatioMode::KeepAspectRatio);
            shared_ptr<QPixmap> point = make_shared<QPixmap>(scaledPixmap);
            int width = point->width();
            int height = point->height();
            ui->lblMouse->setFrame(point);
            ui->lblMouse->setFixedSize(width, height);
            ui->lblMouse->refreshMatrix();
            ui->lblMouse->setMode(Mode::DRAW_LINE);
            ui->statusbar->showMessage("Режим разметки активирован");
        }


        inVid.release();
    }

*/


    QPixmap pix = QPixmap("../resources/images/my_test1.jpeg");
    QPixmap scaledPixmap = pix.scaled(1280, 720, Qt::AspectRatioMode::KeepAspectRatio);
    shared_ptr<QPixmap> point = make_shared<QPixmap>(scaledPixmap);
    ui->lblMouse->setFrame(point);
    int width = point->width();
    int height = point->height();
    ui->lblMouse->setFixedSize(width, height);
    ui->lblMouse->refreshMatrix();
    ui->lblMouse->setMode(Mode::DRAW_LINE);
    ui->statusbar->showMessage("Режим разметки активирован");



}


void MainWindow::on_btnEdit1_clicked()
{
    ui->lblMouse->setMode(Mode::DRAW_LINE);
    ui->statusbar->showMessage("Режим разметки активирован");
}


void MainWindow::on_btnEdit2_clicked()
{
    ui->lblMouse->segmentMatrix = ui->lblMouse->fillZone->fillZone(ui->lblMouse->segmentMatrix);
    ui->lblMouse->paintMatrix();
    ui->lblMouse->updateFrame();
}


void MainWindow::on_pushStop_clicked()
{
    using namespace std;
    // TO-DO
    string name = ui->lineEditZoneName->text().toStdString();
    string description = ui->lineEditZoneDescription->text().toStdString();
    string color = "red";
    int segSize = ui->lblMouse->getSegmentSize();
    int frameWidth = ui->lblMouse->getImgWidth();
    int frameHeight = ui->lblMouse->getImgHeight();
    vector<vector<char>> matrix = ui->lblMouse->getSegmentMatrix();
    // Проверка названия
    if (!ui->lineEditZoneName->text().trimmed().size())
    {
        ui->statusbar->showMessage("Неверный формат названия");
        return;
    }

    // Проверка Описания
    if (!ui->lineEditZoneDescription->text().trimmed().size())
    {
        ui->statusbar->showMessage("Неверный формат описания");
        return;
    }
    // Проверка размера сегментов
    if (segSize < 5 || segSize > 100)
    {
        ui->statusbar->showMessage("Неверный значение размера сегмента");
        return;
    }
    // Преобразование матрицы к линейному вектору
    int segmentNumber = 0;
    vector<int> listSegments;
    for (int i=0, segmentNumber = 0; i < matrix.size(); i++)
        for (int j=0; j<matrix.at(i).size(); j++)
        {
            if(matrix.at(i).at(j))
                listSegments.push_back(segmentNumber);
            ++segmentNumber;
        }
    //Создание объекта зоны и добавление к конфигурации.
    Zone *newZone = new Zone(name, description, color, segSize, frameWidth, frameHeight);
    newZone->setListSegments(listSegments);
    vector<Zone*> listZone = Global::getInstance().getConfiguration()->getListZone();
    listZone.push_back(newZone);
    Global::getInstance().getConfiguration()->setListZone(listZone);
    std::cout << newZone->toJson() << std::endl;
    this->close();
}


void MainWindow::on_spinBoxSegmentSize_valueChanged(int arg1)
{
    ui->lblMouse->setSegmentSize(arg1);
}


void MainWindow::on_pushBack_clicked()
{
    this->close();
}

