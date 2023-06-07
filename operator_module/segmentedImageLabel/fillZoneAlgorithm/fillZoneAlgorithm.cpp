#include <iostream>
#include "fillZoneAlgorithm.h"

std::vector<std::vector<char>> CycleFillZone::fillZone(const std::vector<std::vector<char>> originalMatrix)
{
    std::vector<std::vector<char>> result = originalMatrix;
    // Горизонтальный цикл
    for (int i = 0; i < originalMatrix.size(); i++)
    {
        enum class State{
            NOTHING=0, DETECT=1, SECOND=2, FILL_ZONE=3, DETECT_SECOND=4};
        State gorState = State::NOTHING;
        int first = 0, last = 0;
        for (int j = 0; j < originalMatrix.at(i).size(); j++)
        {
            if (gorState == State::NOTHING && originalMatrix.at(i).at(j) == 0)
                continue;
            else if (gorState == State::NOTHING && originalMatrix.at(i).at(j) == 1)
            {
                gorState = State::DETECT;                
                first = j;
            }
            else if (gorState == State::DETECT && originalMatrix.at(i).at(j) == 0)
                gorState = State::FILL_ZONE;
            else if (gorState == State::DETECT && originalMatrix.at(i).at(j) == 1)
                continue;
            else if (gorState == State::FILL_ZONE && originalMatrix.at(i).at(j) == 0)
                continue;
            else if (gorState == State::FILL_ZONE && originalMatrix.at(i).at(j) == 1)
            {
                gorState = State::DETECT_SECOND;
                last = j;
            }
            else if (gorState == State::DETECT_SECOND && originalMatrix.at(i).at(j) == 0)
                continue;
            else if (gorState == State::DETECT_SECOND && originalMatrix.at(i).at(j) == 1)
                last = j;
        }
        if (gorState == State::DETECT_SECOND)
        {
            for (int j=first; j <= last; j++)
                result.at(i).at(j) = 1;
        }
    }

    // Вертикальный цикл
    
    int n_row = originalMatrix.size();
    int n_column;
    if (n_row!=0)
        n_column = originalMatrix.at(0).size();

    for (int j = 0; j < n_column; j++)
    {
        enum class State{
            NOTHING=0, DETECT=1, SECOND=2, FILL_ZONE=3, DETECT_SECOND=4};
        State gorState = State::NOTHING;
        int first = 0, last = 0;
        for (int i = 0; i < n_row; i++)
        {
            if (gorState == State::NOTHING && result.at(i).at(j) == 0)
                continue;
            else if (gorState == State::NOTHING && result.at(i).at(j) == 1)
            {
                gorState = State::DETECT;                
                first = i;
            }
            else if (gorState == State::DETECT && result.at(i).at(j) == 0)
                gorState = State::FILL_ZONE;
            else if (gorState == State::DETECT && result.at(i).at(j) == 1)
                continue;
            else if (gorState == State::FILL_ZONE && result.at(i).at(j) == 0)
                continue;
            else if (gorState == State::FILL_ZONE && result.at(i).at(j) == 1)
            {
                gorState = State::DETECT_SECOND;
                last = i;
            }
            else if (gorState == State::DETECT_SECOND && result.at(i).at(j) == 0)
                continue;
            else if (gorState == State::DETECT_SECOND && result.at(i).at(j) == 1)
                last = i;
        }

        if (gorState == State::DETECT_SECOND)
        {
            for (int i=first; i <= last; i++)
                result.at(i).at(j) = 1;
        }
    }
    return result;
}

