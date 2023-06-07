#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QPixmap MatToPic(cv::Mat src);

private slots:
    void on_btnLoadScene_clicked();

    void on_btnEdit1_clicked();

    void on_btnEdit2_clicked();

    void on_pushStop_clicked();

    void on_spinBoxSegmentSize_valueChanged(int arg1);

    void on_pushBack_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
