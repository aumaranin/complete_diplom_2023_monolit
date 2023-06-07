#include "qvideolabel.h"
#include "global.h"
#include "operatorstackedwindow.h"

QVideoLabel::QVideoLabel(int id)
{
    idWindow = id;
    refreshSource();
}

void QVideoLabel::mouseDoubleClickEvent(QMouseEvent *e)
{
    std::cout << "id: " << idWindow << endl;
    emit camSelected(idWindow);
}

void QVideoLabel::update()
{
    if (isReady && Global::getInstance().mode==Mode::ALL_CAMS)
    {
        cv::Mat inFrame;
        *inVid >> inFrame;
        QPixmap frame = QPixmap::fromImage(QImage((unsigned char*) inFrame.data, inFrame.cols, inFrame.rows, QImage::Format_BGR888));
        //QPixmap scaledPixmap = frame.scaled(640, 480, Qt::AspectRatioMode::KeepAspectRatio);
        //this->setPixmap(scaledPixmap);
        this->setPixmap(frame.scaled(640, 480, Qt::AspectRatioMode::KeepAspectRatio));
    }
}

QVideoLabel::~QVideoLabel()
{
    inVid->release();
}

void QVideoLabel::refreshSource()
{
    isReady = false;
    url = Global::getInstance().getListConfiguration().at(idWindow)->getSource()->getUrl();
    //url = "/media/data/OBS videos/2023-05-03 12-48-39.mkv";
    inVid = make_shared<cv::VideoCapture>(url);
    if (inVid->isOpened())
    {
        cv::Mat frame;
        *inVid >> frame;
        if (!frame.empty())
            isReady = true;
    }
}
