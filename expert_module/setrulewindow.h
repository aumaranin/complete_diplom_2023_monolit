#ifndef SETRULEWINDOW_H
#define SETRULEWINDOW_H

#include <QDialog>
#include <QStatusBar>
#include <vector>
#include <QCheckBox>

namespace Ui {
class SetRuleWindow;
}

class SetRuleWindow : public QDialog
{
    Q_OBJECT
    std::vector<std::string> listMajorClasses;
    std::vector<std::string> listMinorClasses;
    std::vector<QCheckBox *> listCheckBoxProperties;
public:
    explicit SetRuleWindow(QWidget *parent = nullptr);
    ~SetRuleWindow();
    QStatusBar *statusBar = nullptr;

    const std::vector<std::string> &getListMajorClasses() const;
    void setListMajorClasses(const std::vector<std::string> &newListMajorClasses);

    const std::vector<std::string> &getListMinorClasses() const;
    void setListMinorClasses(const std::vector<std::string> &newListMinorClasses);

    const std::vector<QCheckBox *> &getListCheckBoxProperties() const;
    void setListCheckBoxProperties(const std::vector<QCheckBox *> &newListCheckBoxProperties);

private slots:
    void on_checkBoxExecuteBash_stateChanged(int arg1);

    void on_btnBack_clicked();

    void on_btnConfirm_clicked();

private:
    Ui::SetRuleWindow *ui;
};

#endif // SETRULEWINDOW_H
