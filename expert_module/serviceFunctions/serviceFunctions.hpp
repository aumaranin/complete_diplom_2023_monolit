#include <vector>
#include <string>

namespace sf
{
    /**
     * Выполнение bash-запроса.
     *
     * @param command сам bash-запрос
     * @return Вектор строк с результатами запроса
    */
    std::vector<std::string> executeCommand(const std::string command);


    /**
     * Проверка правильности ввода IP-адреса и порта
     *
     * @param ipAddress ip-адресс и порт
     * @return true - если формат верный, false - формат неверный
    */
    bool verifyIp(std::string ipAddress);
}
