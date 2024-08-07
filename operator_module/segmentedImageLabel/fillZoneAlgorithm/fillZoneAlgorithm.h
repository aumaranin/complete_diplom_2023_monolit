#ifndef FILLZONEALGORITHM_H
#define FILLZONEALGORITHM_H

#include <vector>

/// @brief Базовый класс для определения семейства алгоритмов заполнения зоны
class FillZoneBehavior
{
    public:
    /// @brief Алгоритм заполнения зоны
    /// @param originalMatrix - вектор векторов однобайтовых символов оригинальной матрицы
    /// @return - вектор векторов измененной новой матрицы
    virtual std::vector<std::vector<char>> fillZone(std::vector<std::vector<char>> originalMatrix){std::vector<std::vector<char>> res; return res;};
};


class CycleFillZone : public FillZoneBehavior
{
public:
    /// @brief Алгоритм заполнения зоны
    /// @param originalMatrix - вектор векторов однобайтовых символов оригинальной матрицы
    /// @return - вектор векторов измененной новой матрицы
    virtual std::vector<std::vector<char>> fillZone(std::vector<std::vector<char>> originalMatrix);
};

#endif
