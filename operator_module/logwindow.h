#ifndef LOGWINDOW_H
#define LOGWINDOW_H

#include <QDialog>
#include <string>
#include <vector>
#include <memory>
#include <reportfromdb.h>
#include <DataBase.h>
#include <QTableWidgetItem>

using namespace std;

namespace Ui {
class LogWindow;
}

class LogWindow : public QDialog
{
    Q_OBJECT
    vector<shared_ptr<QTableWidgetItem>> listWidgets;
public:
    explicit LogWindow(QWidget *parent = nullptr);
    ~LogWindow();
    void refresh();


private slots:
    void on_btnRefresh_clicked();

private:
    Ui::LogWindow *ui;

};

#endif // LOGWINDOW_H
