#ifndef CONFIGURATIONLISTWINDOW_H
#define CONFIGURATIONLISTWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ConfigurationListWindow; }
QT_END_NAMESPACE

class ConfigurationListWindow : public QMainWindow
{
    Q_OBJECT

public:
    ConfigurationListWindow(QWidget *parent = nullptr);
    ~ConfigurationListWindow();


private slots:

    ////
    /// \brief Обновление таблицы с названиями конфигураций
    ///
    void showConfigs();

    void dataBaseSet();

    void on_btnSetDatabase_clicked();

    void on_btnAddConf_clicked();

    void on_btnDeleteConf_clicked();

    void on_btnChangeConf_clicked();

private:
    Ui::ConfigurationListWindow *ui;
};
#endif // CONFIGURATIONLISTWINDOW_H
