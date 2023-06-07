#ifndef OPERATORSTACKEDWINDOW_H
#define OPERATORSTACKEDWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTableWidget>
#include <memory>
#include <vector>
#include <string>
#include "qvideolabel.h"
//#include "qcheckconfiguration.h"
#include "knowledgebase.h"
#include "videoengine.h"
#include "qdetectionlabel.h"
#include "qtablelabel.h"
//#include "qtablewidgetitemdoubleclick.h"

#include <logwindow.h>

using namespace std;

const int MAXCOLUMNS = 2;

QT_BEGIN_NAMESPACE
namespace Ui { class OperatorStackedWindow; }
QT_END_NAMESPACE

class OperatorStackedWindow : public QMainWindow
{
    Q_OBJECT
public:
    int t_del;
    int w;
    int h;
    OperatorStackedWindow(QWidget *parent = nullptr);
    ~OperatorStackedWindow();

    vector<shared_ptr<QVideoLabel>> listLabel;
    //vector<shared_ptr<QCheckConfiguration>> listConfigurationList;
    vector<shared_ptr<QTableLabel>> listConfigurationList;
    //vector<shared_ptr<QTableWidgetItemDoubleClick>> listConfigurationList;

    void addWidgetToTableWidget(int &currentNumberItems, QWidget *item);

    shared_ptr<QDetectionLabel> detectionLabel;
    shared_ptr<KnowledgeBase> knowledgeBase;
    shared_ptr<VideoEngine> videoEngine;
    shared_ptr<LogWindow> logWindow;

private slots:
    void on_btmAllCams_clicked();
    void refreshConfigList();
    void refreshVideoLabels();
    void turnOnAllCams();

    void on_turnOnAllCams_triggered();

    void on_stopAllCams_triggered();

    void computeNoteInit(int confId);

    void on_btnLog_clicked();

    void on_btnShowZoneOn_triggered();

    void on_btnShowZoneOff_triggered();

    void on_btnDetectObjectsOn_triggered();

    void on_btnDetectObjectsOff_triggered();

private:
    Ui::OperatorStackedWindow *ui;
};
#endif // OPERATORSTACKEDWINDOW_H
