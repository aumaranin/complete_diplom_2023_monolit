#include "videoengine.h"
#include "global.h"
#include <QPixmap>
#include <set>

VideoEngine::VideoEngine()
{
}

void VideoEngine::createUnitedZoneMatrix()
{
    flagZoneExisted = false;
    int rows = 0;
    int columns = 0;
    // Сложение зон
    if (knowledgeBase->listZone.size()!=0)
    {
        imgWidth = knowledgeBase->listZone.at(0)->getFrameWidth();
        imgHeight = knowledgeBase->listZone.at(0)->getFrameHeight();
        flagZoneExisted = true;
        set<int> segmentSet;
        for (auto &zone : knowledgeBase->listZone)
        {
            for (auto &segment : zone->getListSegments())
            {
                segmentSet.insert(segment);
            }
        }
        vector<int> segments(segmentSet.begin(), segmentSet.end());

        // Если есть зоны - задаем размер сегментов
        segSize = knowledgeBase->listZone.at(0)->getSegSize();

        /*
        // Строим матрицу сегментов
        rows = imgHeight/segSize;
        columns = imgWidth/segSize;

        matrix.resize(rows);
        for (int i = 0; i < rows; i++)
        {
            matrix.at(i).resize(columns);
        }
        for (auto segmentNumber : segments)
        {
            int selectRow = segmentNumber/columns;
            int selectColumn = segmentNumber%columns;
            //int matrix_rows = matrix.size();
            //int matrix_columns = matrix.at(0).size();
            matrix.at(selectRow).at(selectColumn) = 1;
        }
        */
        // Строим матрицу сегментов
        int n_rows;
        int n_cols;
        if (imgHeight%segSize)
            n_rows = imgHeight/segSize + 1;
        else
            n_rows = imgHeight/segSize;
        if (imgWidth%segSize)
            n_cols = imgWidth/segSize + 1;
        else
            n_cols = imgWidth/segSize;
        //vector<vector<int>> matrix(n_rows);
        matrix.resize(n_rows);
        for (int i = 0; i < n_rows; ++i)
            matrix.at(i).resize(n_cols);

        // Устанавливаем в единицу значения матрицы по списку сегментов.
        for (auto segmentNumber : segments)
        {
            int selectRow = segmentNumber/n_cols;
            int selectColumn = segmentNumber%n_cols;
            // На всякий случай, проверяем: если сегмент - крайний, оставляем его нулем. Остальные устанавливаем в единицу
            if ((selectRow != 0) && (selectRow != (n_rows-1)) && (selectColumn != 0) && (selectColumn != (n_cols-1)))
                matrix.at(selectRow).at(selectColumn) = 1;
        }

        cout << "Размеры изображения: " << imgWidth << ":" << imgHeight << endl;
        cout << "Размер сегментов " << segSize << endl;

        cout << "Размеры матрицы: " << n_cols << ":" << n_rows << endl;

        // Печать матрицы
        cout << "Матрица: " << endl;
        for (int row = 0; row < n_rows; ++row)
        {
            for (int col = 0; col < n_cols; ++col)
                cout << matrix.at(row).at(col) << " ";
            cout << endl;
        }
    }

}

void VideoEngine::releaseResources()
{
    inVid->release();
}

VideoEngine::~VideoEngine()
{
    releaseResources();
}
    /*
void VideoEngine::paintSegment(int row, int column, QImage &image)
{

    int segmentSize = knowledgeBase->listZone.at(0)->getSegSize();
    try
    {
        for (int i = 0 + row*segmentSize; i < segmentSize + row*segmentSize; i++)
        {
            for (int j = 0 + column*segmentSize; j < segmentSize + column*segmentSize; j++)
            {
                // Получаем цвет пикселя
                QColor pixColor = image.pixelColor(j, i);
                // Устанавливаем красный в 255
                pixColor.setRed(255);
                image.setPixelColor(j, i, pixColor);
            }
        }
    } catch (const std::out_of_range& e)
    {

    }

}
    */

void VideoEngine::paintSegment(int row, int column, cv::Mat &frame)
{
    for (int x = column*segSize; x < (segSize + column*segSize); ++x)
        for (int y = row*segSize; y < (segSize + row*segSize); ++y)
        {
            cv::Vec3b & color = frame.at<cv::Vec3b>(y,x);
            color[2] = 250;   // Красный цвет
        }
}

void VideoEngine::drawZone(cv::Mat &frame)
{
    /*
    int rows = matrix.size();
    int columns = matrix.at(0).size();
    int segmentSize = knowledgeBase->listZone.at(0)->getSegSize();
    QImage qImage = QImage((unsigned char*) frame.data, frame.cols, frame.rows, QImage::Format_BGR888);
    for (int i = 0 + row*segmentSize; i < segmentSize + row*segmentSize; i++)
    {
        for (int j = 0 + column*segmentSize; j < segmentSize + column*segmentSize; j++)
        {
            // Получаем цвет пикселя
            QColor pixColor = qImage.pixelColor(j, i);
            // Устанавливаем красный в 255
            pixColor.setRed(230);
            qImage.setPixelColor(j, i, pixColor);
        }
    }
    frame = cv::Mat(qImage.height(), qImage.width(),CV_8UC3, qImage.bits());
    */
    /*
    if (matrix.size() != 0)
    {
        int rows = matrix.size();
        int columns = matrix.at(0).size();
        QImage qImage = QImage((unsigned char*) frame.data, frame.cols, frame.rows, QImage::Format_BGR888);
        for (int row = 0; row < rows; ++row)
            for (int column = 0; column < columns; ++column)
                if (matrix[row][column])
                    paintSegment(row, column, qImage);
        frame = cv::Mat(qImage.height(), qImage.width(),CV_8UC3, qImage.bits());
    }*/

    int n_rows; // количество строк сегментов (высота матрицы)
    int n_cols; // количество столбцов сегментов (ширина матрицы
    if (imgHeight%segSize)
        n_rows = imgHeight/segSize + 1;
    else
        n_rows = imgHeight/segSize;
    if (imgWidth%segSize)
        n_cols = imgWidth/segSize + 1;
    else
        n_cols = imgWidth/segSize;

    for (int row = 1; row < n_rows-1; ++row)
        for (int col = 1; col < n_cols-1; ++col)
            if (matrix.at(row).at(col))
                paintSegment(row, col, frame);
}

void VideoEngine::update()
{
    // Строим матрицу зон
    createUnitedZoneMatrix();
    cv::Mat inFrame;
    QPixmap pixmap;
    QPixmap scaledPixmap;
    isReady = false;
    inVid = make_shared<cv::VideoCapture>(url);
    if (inVid->isOpened())
    {
        cv::Mat frame;
        *inVid >> frame;
        if (!frame.empty())
        {
            isReady = true;
            imgWidth = frame.cols;
            imgHeight = frame.rows;
            Global::getInstance().mode = Mode::DETECTION;
        }
        vector<shared_ptr<DetectObject>> objects;
        logicEngine->timer->start();

        while(isReady && (Global::getInstance().mode==Mode::DETECTION))
        {
            if (knowledgeBase->flagComparison && flagZoneExisted && flagCompareObjects)
            {
                knowledgeBase->compare();
                std::cout << "Сопоставление завершено." << endl;
                knowledgeBase->flagComparison = false;
                logicEngine->timer->start();
            }

            // Получаем кадр из видеопотока
            *inVid >> inFrame;
            if (inFrame.empty())
                continue;
            cv::Mat clone = inFrame.clone();

            // Отправляем кадр в алгоритм детектирования, получаем сложный объект
            if (flagDetectObjects)
            {
                objects = classificationModule->detect(clone);

                // Добавляем обнаруженные объекты в базу знаний
                knowledgeBase->listObjects = objects;
            }

            // Отрисовываем зоны
            if (flagDrawZone && flagZoneExisted)
                drawZone(inFrame);

            // Отрисовываем объекты
            if (flagDetectObjects)
                for (auto obj : objects)
                {
                    obj->imageHeight = imgHeight;
                    obj->imageWidth = imgWidth;
                    obj->segSize = segSize;
                    obj->displayObject(inFrame, BLUE);
                }

            // Передаем кадр на метку
            pixmap = QPixmap::fromImage(QImage((unsigned char*) inFrame.data, inFrame.cols, inFrame.rows, QImage::Format_BGR888));
            scaledPixmap = pixmap.scaled(scaledWidth, scaledHeight, Qt::AspectRatioMode::KeepAspectRatio);
            detectionLabel->setPixmap(scaledPixmap);
            cv::waitKey(0);
        }
    }
    //inVid->release();
}
