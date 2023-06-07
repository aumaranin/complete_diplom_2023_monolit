#ifndef CONFIGURATIONMENU_H
#define CONFIGURATIONMENU_H

#include <QDialog>
#include "configuration.h"

namespace Ui {
class ConfigurationMenu;
}

class ConfigurationMenu : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigurationMenu(QWidget *parent = nullptr);
    ~ConfigurationMenu();

    Configuration *configuration;

signals:
    void configuration_entered();

private slots:
    void on_btnSetName_clicked();

    void on_btnBack_clicked();

    void on_btnSetSource_clicked();

    void on_btnSetZone_clicked();

    void on_btnSetRule_clicked();

    void on_btnConfirm_clicked();

private:
    Ui::ConfigurationMenu *ui;
};

#endif // CONFIGURATIONMENU_H
