#include "serviceFunctions.hpp"
#include <fstream>
#include <vector>
#include <set>

namespace sf
{
    /**
     * Выполнение bash-запроса.
     *
     * @param command сам bash-запрос
     * @return Вектор строк с результатами запроса
    */
    std::vector<std::string> executeCommand(const std::string command)
    {
        using namespace std;
        string fileName = "executeCommand.txt";
        string request = command + " > " + fileName;
        system(request.c_str());
        vector<string> result;
        ifstream resFile(fileName);
        string line;
        while (resFile >> line)
            result.push_back(line);
        resFile.close();
        request = "rm " + fileName;
        system(request.c_str());
        return result;
    }

    std::string trimStr(const std::string &str)
    {
        using namespace std;
        set<char> spacers;
        spacers.insert(' ');
        spacers.insert('\t');
        spacers.insert('\n');
        string newStr;
        int pos1 = 0, pos2 = str.length();
        bool flag = false; //флаг устанавливается в true если какие-либо числа найдены.
        for (int i = 0; i < str.length(); i++)
        {
            char sim = str.at(i);
            if (!spacers.count(sim)==1)
            {
                flag = true;
                pos1 = i;
                break;
            }
        }
        for (int i = str.length()-1; i >= 0; i--)
        {
            char sim = str.at(i);
            if (!spacers.count(sim)==1)
            {
                flag = true;
                pos2 = i;
                break;
            }
        }
        if (flag)
            newStr = str.substr(pos1, pos2-pos1+1);
        else
            newStr = "";
        return newStr;
    }

    bool verifyIp(const std::string &ipAddress)
    {
        using namespace std;
        bool result = false;
        set<int> numbers;
        for (int i='0'; i<='9'; i++)
            numbers.insert(i);


        if (ipAddress.length() >= 15)
            //012.456.89(10).(12)(13)(14):(16)(17)(18)(19)(20)(21)

            if (numbers.count(ipAddress.at(0)) && numbers.count(ipAddress.at(1)) && numbers.count(ipAddress.at(2)) &&
                    numbers.count(ipAddress.at(4)) && numbers.count(ipAddress.at(5)) && numbers.count(ipAddress.at(6)) &&
                    numbers.count(ipAddress.at(8)) && numbers.count(ipAddress.at(9)) && numbers.count(ipAddress.at(10)) &&
                    numbers.count(ipAddress.at(12)) && numbers.count(ipAddress.at(13)) && numbers.count(ipAddress.at(14)) &&
                    ipAddress.at(3)=='.' && ipAddress.at(7)=='.' && ipAddress.at(11)=='.'
                    )
                result = true;
            if (ipAddress.length() > 15)
                {
                if (ipAddress.at(15)!=':')
                    {
                        result = false;
                    }
                    else
                        for (int j=16; j<ipAddress.length();j++)
                            if (numbers.count(ipAddress.at(j))!=1)
                            {
                                result = false;
                                break;
                            }
                }
        return result;
    }
}
