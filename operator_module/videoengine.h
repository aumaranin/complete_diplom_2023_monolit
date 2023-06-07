#ifndef VIDEOENGINE_H
#define VIDEOENGINE_H

#include "Source.h"
#include <vector>
#include <memory>
#include <opencv2/opencv.hpp>
#include <qdetectionlabel.h>
#include <classification/classificationalgorithm.h>
#include <knowledgebase.h>
#include <zone.h>
#include <logicengine.h>

using namespace std;

class VideoEngine
{
public:
    VideoEngine();
    std::string url;
    std::shared_ptr<cv::VideoCapture> inVid;
    bool isReady;
    QDetectionLabel *detectionLabel;

    shared_ptr<ClassificationAlgorithm> classificationModule;
    shared_ptr<KnowledgeBase> knowledgeBase;
    shared_ptr<LogicEngine> logicEngine;

    bool flagDrawZone;
    bool flagCompareObjects;
    bool flagDetectObjects;

    void update();    
    void releaseResources();
    ~VideoEngine();


    bool flagZoneExisted; // флаг, устанавливается в true, если есть зоны и правила. В противном случае - false
    int scaledWidth;   // ширина скалированного изображение
    int scaledHeight;  // высота скалированного изображения
    int imgWidth;      // ширина оригинального изображения
    int imgHeight;     // высота оригинального изображения
    int segSize;       // размер сегментов. Используется только если есть зоны в правилах.
    vector<vector<int>> matrix;  // общая матрица зон для отрисовки. Используется только если есть зоны в правилах.
    void drawZone(cv::Mat &frame);
    void createUnitedZoneMatrix();
    //void paintSegment(int row, int column, QImage &image);
    void paintSegment(int row, int column, cv::Mat &frame);
};

#endif // VIDEOENGINE_H
