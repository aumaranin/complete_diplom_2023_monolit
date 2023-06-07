#ifndef CONFIGURATIONNAME_H
#define CONFIGURATIONNAME_H

#include <QMainWindow>

namespace Ui {
class ConfigurationName;
}

class ConfigurationName : public QMainWindow
{
    Q_OBJECT

public:
    explicit ConfigurationName(QWidget *parent = nullptr);
    ~ConfigurationName();

    bool verifyConfigurationName(QString configurationName);

private slots:
    void on_btnBack_clicked();

    void on_btnConfirm_clicked();

private:
    Ui::ConfigurationName *ui;
};

#endif // CONFIGURATIONNAME_H
