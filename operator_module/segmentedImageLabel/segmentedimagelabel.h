#ifndef SEGMENTEDIMAGELABEL_H
#define SEGMENTEDIMAGELABEL_H

#include <QLabel>
#include <QWidget>
#include <vector>
#include <fillZoneAlgorithm.h>
#include <memory>

class SegmentedImageLabel : public QLabel
{
    int imgWidth;    // Ширина кадра
    int imgHeight;   // Высота кадра
    int segmentSize; // Размер сегментов



    int n_row;      //Количество строк
    int n_column;   //количество столбцов
    std::shared_ptr<QPixmap> frame;


public:

    // Матрица сегментов.
    // 1 - выделенный сегмент, 0 - не выделенный
    std::vector<std::vector<char>> segmentMatrix;

    FillZoneBehavior *fillZone;

    SegmentedImageLabel();
    ~SegmentedImageLabel();
    int getImgWidth() {return imgWidth;}
    int getImgHeight() {return imgHeight;}
    int getSegmentSize() {return segmentSize;}
    std::vector<std::vector<char>> getSegmentMatrix(){return segmentMatrix;}

    ////
    /// \brief Установка QPixmap и задание размеров QLabel
    /// \param указатель на QPixmap
    ///
    ///
    void setFrame(std::shared_ptr<QPixmap> frame);

    ////
    /// \brief Установка размера сегмента
    /// \param size - высота/ширина сегмента
    ///
    void setSegmentSize(int size);

    ////
    /// \brief обновление внутренних значений размеров кадра и матрицы сегментов
    ///
    void refreshMatrix();

    ////
    /// \brief Отображение информации о метке и матрице сегментов
    ///
    void labelInfo();

    ////
    /// \brief Задание значение сегмента
    /// \param row - номер строки
    /// \param column - номер столбца
    /// \param value - значение
    ///
    void setValueSegment(int row, int column, char value);

    ////
    /// \brief Вычисление номера сегмента в матрице по координатам
    /// \param x - координата x
    /// \param y - координата y
    /// \return Вектор, первое число - номер строки, второе - номер столбца
    ///
    std::vector<int> calculateSegmentByPos(int x, int y);


    ////
    /// \brief Функция устанавливает значение value в матрице сегментов по координатам
    /// \param x - координата x
    /// \param y - координата y
    /// \param value - значение
    ///
    void setValueSegmentByPos(int x, int y, int value);

    ////
    /// \brief Раскрашивает сегмент красным, задавая номер строки и столбца матрицы
    /// \param строка матрицы
    /// \param столбец матрицы
    ///
    void paintSegment(int row, int column);

    ////
    /// \brief Раскрашивает сегмент красным, задавая координаты изображения
    /// \param x - координата x
    /// \param y - координата y
    ///
    void paintSegmentByPos(int x, int y);

    ////
    /// \brief Отрисовывает зоны в соответствие с матрицей сегментов
    ///
    void paintMatrix();

    ////
    /// \brief Обновление исходного QPixelmap
    ///
    void updateFrame();

    ////
    /// \brief Задание обновленной матрицы
    /// \param newMatrix - новая матрица
    ///
    void setMatrix(std::vector<std::vector<char>> newMatrix);
};

#endif // SEGMENTEDIMAGELABEL_H
