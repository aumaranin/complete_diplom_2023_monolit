#include "segmentedimagelabel.h"
#include <iostream>
#include "fillZoneAlgorithm.h"

SegmentedImageLabel::SegmentedImageLabel()
{
    fillZone = new CycleFillZone();
}

SegmentedImageLabel::~SegmentedImageLabel()
{
    delete fillZone;
}

void SegmentedImageLabel::setFrame(std::shared_ptr<QPixmap> frame)
{
    this->frame = frame;
    this->setPixmap(*frame);
    this->setFixedSize(frame->width(), frame->height());
}

void SegmentedImageLabel::setSegmentSize(int size)
{
    segmentSize = size;
    refreshMatrix();
}

void SegmentedImageLabel::refreshMatrix()
{
    using namespace std;
    // Обновление значений высоты и ширины кадра
    imgHeight = this->height();
    imgWidth = this->width();

    // Вычисление количества столбцов (высоты матрицы)
    n_row = imgHeight/segmentSize;
    if (imgHeight%segmentSize)
        ++n_row;

    // Вычисление количества столбцов (ширины матрицы)
    n_column = imgWidth/segmentSize;
    if (imgWidth%segmentSize)
        ++n_row;

    // Задание размеров матрицы
    segmentMatrix.resize(n_row);
    for (int i = 0; i < n_row; i++)
        segmentMatrix.at(i).resize(n_column);

    // Обнуление значений матрицы
    for (int i = 0; i < n_row; i++)
        for (int j = 0; j < n_column; j++)
            segmentMatrix.at(i).at(j) = 0;
}

void SegmentedImageLabel::labelInfo()
{
    using namespace std;
    cout << "Ширина изображения: " << getImgWidth() << endl;
    cout << "Высота изображения: " << getImgHeight() << endl;
    cout << "Размер сегментов: " << getSegmentSize() << endl;
    cout << "Размер матрицы: " << n_row << " - " << n_column << endl;
    cout << "Матрица сегментов: " << endl;
    for (auto row: segmentMatrix)
    {
        for (auto value: row)
            cout << value << " ";
        cout << endl;
    }

}

void SegmentedImageLabel::setValueSegment(int row, int column, char value)
{
    segmentMatrix.at(row).at(column) = value;
}

std::vector<int> SegmentedImageLabel::calculateSegmentByPos(int x, int y)
{
    using namespace std;

    // Вычисление строки
    int row = x/segmentSize;

    // Вычисление столбца
    int column = y/segmentSize;

    vector<int> pos{row, column};
    return pos;
}

void SegmentedImageLabel::setValueSegmentByPos(int x, int y, int value)
{
    int row = calculateSegmentByPos(x, y).at(0);
    int column = calculateSegmentByPos(x, y).at(1);
    setValueSegment(row, column, value);
}

void SegmentedImageLabel::paintSegment(int row, int column)
{
    // Преобразуем полученный QPixMap в QImage для работы с цветом
    try
    {
        QImage qImage = frame->toImage();
        for (int i = 0 + row*segmentSize; i < segmentSize + row*segmentSize; i++)
        {
            for (int j = 0 + column*segmentSize; j < segmentSize + column*segmentSize; j++)
            {
                // Получаем цвет пикселя
                QColor pixColor = qImage.pixelColor(j, i);
                // Устанавливаем красный в 255
                pixColor.setRed(255);
                qImage.setPixelColor(j, i, pixColor);
            }
        }
        *frame = QPixmap::fromImage(qImage);
    } catch (const std::out_of_range& e)
    {

    }
}

void SegmentedImageLabel::paintSegmentByPos(int x, int y)
{
    int row = calculateSegmentByPos(x, y).at(0);
    int column = calculateSegmentByPos(x, y).at(1);
    setValueSegment(row, column, 1);
    paintSegment(row, column);
}

void SegmentedImageLabel::paintMatrix()
{
    for (int i = 0; i < n_row; i++)
    {
        for (int j = 0; j < n_column; j++)
            if (segmentMatrix.at(i).at(j))
                paintSegment(i, j);
    }
}

void SegmentedImageLabel::updateFrame()
{
    this->setPixmap(*frame);
}

void SegmentedImageLabel::setMatrix(std::vector<std::vector<char> > newMatrix)
{
    this->segmentMatrix = newMatrix;
}


