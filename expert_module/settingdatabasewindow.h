#ifndef SETTINGDATABASEWINDOW_H
#define SETTINGDATABASEWINDOW_H

#include <QDialog>
#include "DataBase.h"

namespace Ui {
class SettingDatabaseWindow;
}

class SettingDatabaseWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDatabaseWindow(QWidget *parent = nullptr);
    ~SettingDatabaseWindow();

private slots:
    void on_btnBack_clicked();

    void on_btnCofirm_clicked();

private:
    Ui::SettingDatabaseWindow *ui;

signals:
    ////
    /// \brief Сигнал - информация о БД введена
    ///
    void databaseInfoEntered();

};

#endif // SETTINGDATABASEWINDOW_H
