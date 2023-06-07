#ifndef DRAWINGLABEL_H
#define DRAWINGLABEL_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#include <QEvent>
#include <vector>
#include <segmentedimagelabel.h>
#include <memory>
#include "fillZoneAlgorithm.h"

enum class Mode{NODRAW=0, DRAW_LINE=1, DRAW_ZONE=2};

class DrawingLabel : public SegmentedImageLabel
{
    Q_OBJECT


public:
    Mode mode;

    DrawingLabel(QWidget *parent = 0);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseLeftEvent(QEvent *event);

    void verifyPos(int &x, int &y);


    int x, y;
    void setMode(Mode mode) {this->mode = mode;}

signals:
    void MousePressed();
    void MousePos();
    void MouseLeft();
};

#endif // DRAWINGLABEL_H
