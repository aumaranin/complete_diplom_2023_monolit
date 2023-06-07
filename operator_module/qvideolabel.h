#ifndef QVIDEOLABEL_H
#define QVIDEOLABEL_H

#include <QLabel>
#include <opencv2/opencv.hpp>
#include <memory>

class QVideoLabel : public QLabel
{
    Q_OBJECT
public:
    bool isReady;
    QVideoLabel() {}
    QVideoLabel(int id);
    int idWindow;
    std::string url;
    std::shared_ptr<cv::VideoCapture> inVid;
    virtual void mouseDoubleClickEvent( QMouseEvent * e );
    void update();
    ~QVideoLabel();

    void refreshSource();
signals:
    void camSelected(int id);
};

#endif // QVIDEOLABEL_H
