#include "operatorstackedwindow.h"
#include "./ui_operatorstackedwindow.h"
#include <global.h>
#include <qvideolabel.h>
#include <QVector>
#include <classification/yolo2dnn.h>
#include <logicengine.h>
#include <logwindow.h>

OperatorStackedWindow::OperatorStackedWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OperatorStackedWindow)
{
    logWindow = make_shared<LogWindow>();
    ui->setupUi(this);
    w = 1280;
    h = 720;
    // Преднастройка левой таблицы
    ui->tableWidgetConfigNames->setColumnCount(1);
    ui->tableWidgetConfigNames->horizontalHeader()->hide();
    ui->tableWidgetConfigNames->verticalHeader()->hide();
    ui->tableWidgetConfigNames->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidgetConfigNames->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Преднастройка правой таблицы с видео-метками
    ui->tableWidgetVideoLabels->setColumnCount(MAXCOLUMNS);
    ui->tableWidgetVideoLabels->horizontalHeader()->hide();
    ui->tableWidgetVideoLabels->verticalHeader()->hide();
    ui->tableWidgetVideoLabels->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidgetVideoLabels->setColumnWidth(0, 640);
    ui->tableWidgetVideoLabels->setColumnWidth(1, 640);

    // Загрузка всех конфигураций из базы данных
    refreshConfigList();

    // Обновление количества окошек для видеопотоков основного окна
    refreshVideoLabels();
    ui->page2Widget->setFixedWidth(w);
    ui->page2Widget->setFixedHeight(h);
    //this->setFixedWidth(1618);
    //this->setFixedHeight(900);

    // Разметка второй страницы
    detectionLabel = make_shared<QDetectionLabel>();
    ui->stackedWidget->setCurrentIndex(1);
    //ui->stackedWidget->addWidget(detectionLabel.get());
    QGridLayout *lay = new QGridLayout();
    lay->addWidget(detectionLabel.get());
    ui->page2Widget->setLayout(lay);

    //ui->page2Widget->addWidget(detectionLabel.get());
    //detectionLabel->setFrameShape(QFrame::Box);
    //detectionLabel->setLineWidth(2);
    detectionLabel->setFixedSize(w, h);
    detectionLabel->show();
    ui->stackedWidget->setCurrentIndex(0);
    std::cout << ui->page2Widget->width() << " : " << ui->page2Widget->height() << endl;
}

OperatorStackedWindow::~OperatorStackedWindow()
{
    delete ui;
}

void OperatorStackedWindow::addWidgetToTableWidget(int &currentNumberItems, QWidget *item)
{
    int row = currentNumberItems / MAXCOLUMNS;
    int column = currentNumberItems % MAXCOLUMNS;
    ui->tableWidgetVideoLabels->setCellWidget(row, column, item);
    ui->tableWidgetVideoLabels->setColumnWidth(column, item->width());
    //int colW = tw->columnWidth(column);
    //std::cout << "item width: " << item->width() << std::endl;
    //std::cout << "Column width: " << colW << std::endl;
    ui->tableWidgetVideoLabels->setRowHeight(row, item->height());
    currentNumberItems++;
}


void OperatorStackedWindow::on_btmAllCams_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    turnOnAllCams();
}

void OperatorStackedWindow::refreshConfigList()
{
    if (Global::getInstance().getDataBase() == nullptr)
        statusBar()->showMessage("База данных не подключена.");
    else
    {
        // Загрузка конфигураций из базы данных
        vector<string> listConfigurationNames = Global::getInstance().getDataBase()->getListConfigurationNames();
        vector<shared_ptr<Configuration>> listConfiguration;
        for (auto configurationName : listConfigurationNames)
        {
            string confJson = Global::getInstance().getDataBase()->readConfiguration(configurationName);
            shared_ptr<Configuration> newConfiguration = make_shared<Configuration>(confJson);
            listConfiguration.push_back(newConfiguration);
        }
        Global::getInstance().setListConfiguration(listConfiguration);

        // Обновление левого tableWidget
        ui->tableWidgetConfigNames->clear();
        ui->tableWidgetConfigNames->setRowCount(listConfiguration.size());

        // Не получается реализовать shared_ptr
        /*
        static vector<QCheckConfiguration*> itemsList;
        for (int i=0 ; i < itemsList.size(); i++)
            delete itemsList.at(i);
        */
        listConfigurationList.clear();
        for (int i = 0; i < listConfiguration.size(); i++)
        {
            auto configuration = listConfiguration.at(i);
            // Добавление виджетов в первую tableWidget
            //shared_ptr<QTableWidgetItem> it = make_shared<QTableWidgetItem>();
            //it->setText(QString::fromStdString(configuration->getName()));

            // Рабочий вариант, основанный на QTableWidgetItem
            //QTableWidgetItem *newItem = new QTableWidgetItem();
            //newItem->setText(QString::fromStdString(configuration->getName()));
            //shared_ptr<QTableWidgetItem> it (newItem);
            //ui->tableWidgetConfigNames->setItem(i, 0, newItem);

            // Вариант на QCheckConfiguration
            //shared_ptr<QCheckConfiguration> newItemSmart (new QCheckConfiguration());
            //listConfigurationList.push_back(newItemSmart);

            //shared_ptr<QTableLabel> newItemSmart (new QTableLabel());
            //listConfigurationList.push_back(newItemSmart);
            //newItemSmart->setText(QString::fromStdString(configuration->getName()));
            //newItemSmart->idConf = i;
            //ui->tableWidgetConfigNames->setCellWidget(i, 0, newItemSmart.get());

            shared_ptr<QTableLabel> newItemSmart = make_shared<QTableLabel>();
            newItemSmart->setText(QString::fromStdString(" " + configuration->getName()));
            newItemSmart->idConf = i;
            connect(newItemSmart.get(), SIGNAL(camSelected(int)), this, SLOT(computeNoteInit(int)));
            listConfigurationList.push_back(newItemSmart);
            ui->tableWidgetConfigNames->setCellWidget(i, 0, newItemSmart.get());
        }
    }
}

void OperatorStackedWindow::refreshVideoLabels()
{
    // ВРЕМЕННЫЕ ПАРАМЕТРЫ
    //int maxItems=5;
    //QPixmap pixmap("../resources/images/sample1.png");
    QPixmap pixmap("../resources/images/empty_image.png");
    QPixmap scaledPixmap = pixmap.scaled(640, 480, Qt::AspectRatioMode::KeepAspectRatio);

    int maxItems = Global::getInstance().getListConfiguration().size();

    int maxRows;
    if (maxItems%MAXCOLUMNS)
        maxRows = maxItems/MAXCOLUMNS + 1;
    else
        maxRows = maxItems/MAXCOLUMNS;
    ui->tableWidgetVideoLabels->setRowCount(maxRows);

    shared_ptr<QVideoLabel> lb;

    for (int i = 0; i < maxItems; i++)
    {
        lb = make_shared<QVideoLabel>(i);
        connect(lb.get(), SIGNAL(camSelected(int)), this, SLOT(computeNoteInit(int)));
        lb->setFrameShape(QFrame::Box);
        lb->setLineWidth(2);
        lb->setPixmap(scaledPixmap);
        lb->setFixedSize(scaledPixmap.width(), scaledPixmap.height());
        listLabel.push_back(lb);
    }
    int currentNumberItems = 0;
    for (auto item : listLabel)
        addWidgetToTableWidget(currentNumberItems, item.get());
}

void OperatorStackedWindow::turnOnAllCams()
{    
    Global::getInstance().mode = Mode::NONE;
    for (auto item: listLabel)
        item->refreshSource();
    Global::getInstance().mode = Mode::ALL_CAMS;
    while (true)
    {
        for (auto item : listLabel)
        {
            item->update();
            cv::waitKey(0);
        }
    }
}

void OperatorStackedWindow::on_turnOnAllCams_triggered()
{
    turnOnAllCams();
}


void OperatorStackedWindow::on_stopAllCams_triggered()
{
    Global::getInstance().mode = Mode::NONE;
}



void OperatorStackedWindow::computeNoteInit(int confId)
{
    if (videoEngine.get() != nullptr)
        videoEngine->releaseResources();
    ui->stackedWidget->setCurrentIndex(1);
    // Создание базы знаний
    knowledgeBase = make_shared<KnowledgeBase>();
    knowledgeBase->listZone = Global::getInstance().getListConfiguration().at(confId)->getListZone();
    knowledgeBase->listRule = Global::getInstance().getListConfiguration().at(confId)->getListRule();
    knowledgeBase->configurationName = Global::getInstance().getListConfiguration().at(confId)->getName();
    knowledgeBase->flagComparison = false;

    videoEngine = make_shared<VideoEngine>();
    videoEngine->url = Global::getInstance().getListConfiguration().at(confId)->getSource()->getUrl();
    videoEngine->detectionLabel = detectionLabel.get();
    videoEngine->scaledWidth = w;
    videoEngine->scaledHeight = h;
    videoEngine->knowledgeBase = knowledgeBase;
    videoEngine->flagDrawZone = false;
    videoEngine->flagDetectObjects = false;
    videoEngine->flagCompareObjects = true;

    videoEngine->classificationModule = make_shared<Yolo2Dnn>();

    t_del = Global::getInstance().getListConfiguration().at(confId)->getPeriodComparison() * 1000;
    shared_ptr<LogicEngine> logicEngine = make_shared<LogicEngine>(t_del);
    logicEngine->knowledgeBase = knowledgeBase;
    logicEngine->timer->stop();
    videoEngine->logicEngine = logicEngine;

    // Загружаем из всех правил основные имена распознаваемых классов объектов (MajorObject)
    for (auto config : Global::getInstance().getListConfiguration())
        for (auto rule : config->getListRule())
            videoEngine->classificationModule->allowedClasses.push_back(rule->getMajorClass());

    videoEngine->update();
}


void OperatorStackedWindow::on_btnLog_clicked()
{
    logWindow->refresh();
    logWindow->show();
}


void OperatorStackedWindow::on_btnShowZoneOn_triggered()
{
    if (videoEngine.get()!=nullptr)
        videoEngine->flagDrawZone = true;
}


void OperatorStackedWindow::on_btnShowZoneOff_triggered()
{
    if (videoEngine.get()!=nullptr)
        videoEngine->flagDrawZone = false;
}


void OperatorStackedWindow::on_btnDetectObjectsOn_triggered()
{
    if (videoEngine.get()!=nullptr)
        videoEngine->flagDetectObjects = true;
}


void OperatorStackedWindow::on_btnDetectObjectsOff_triggered()
{
    if (videoEngine.get()!=nullptr)
        videoEngine->flagDetectObjects = false;
}

