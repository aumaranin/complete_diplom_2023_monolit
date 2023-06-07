#ifndef NEWCAMERA2_H
#define NEWCAMERA2_H

#include <QDialog>
#include "Source.h"

namespace Ui {
class Newcamera2;
}

class Newcamera2 : public QDialog
{
    Q_OBJECT

public:
    explicit Newcamera2(QWidget *parent = nullptr);
    ~Newcamera2();

signals:
    void cameraAdded();

private slots:
    void on_radioButtonIpCam_clicked();

    void on_radioButtonUsbCam_clicked();

    void on_backButton_clicked();

    void on_addCameraButton_clicked();

    void on_radioButtonVideoTape_clicked();

    void on_btnFileBrowser_clicked();

private:
    Ui::Newcamera2 *ui;
};

#endif // NEWCAMERA2_H
