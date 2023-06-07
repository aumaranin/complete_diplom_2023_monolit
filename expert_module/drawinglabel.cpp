#include "drawinglabel.h"
#include <segmentedimagelabel.h>
#include "fillZoneAlgorithm.h"
#include <iostream>
#include <memory>

DrawingLabel::DrawingLabel(QWidget *parent)
{
    mode = Mode::NODRAW;
}

void DrawingLabel::mouseMoveEvent(QMouseEvent *event)
{    
    this->x = event->x();
    this->y = event->y();
    verifyPos(x, y);
    if (mode!=Mode::NODRAW)
    {
        this->paintSegmentByPos(y, x);
        std::cout << "x=" << x << "  y=" << y << std::endl;
        this->updateFrame();
    }
}

void DrawingLabel::mousePressEvent(QMouseEvent *event)
{
    std::cout << "зона" << std::endl;
}

void DrawingLabel::mouseLeftEvent(QEvent *event)
{
}

void DrawingLabel::verifyPos(int &x, int &y)
{
    if (x <= getSegmentSize())
        x = getSegmentSize();
    if (x > getImgWidth() - getSegmentSize())
        x = getImgWidth() - getSegmentSize();
    if (y <= getSegmentSize())
        y = getSegmentSize();
    if (y >= getImgHeight() - getSegmentSize())
        y = getImgHeight() - getSegmentSize();
}


