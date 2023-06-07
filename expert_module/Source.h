#ifndef SOURCE_H
#define SOURCE_H

#include <string>

class Source
{
    std::string name;
    std::string type;
public:
    Source(std::string name) : name{name} {};
    Source() {}
    void setName(std::string name) {this->name = name;}
    std::string getName() {return name;}
    void setType(std::string type) {this->type = type;}
    std::string getType() {return type;}

    /**
     * @brief Функция для получения url источника
     * @param type - дополнительный параметр для выбора потока (1 или 2)
     * @return строка url-источника
     */
    virtual std::string getUrl(int type=1) = 0;        
    virtual std::string toJson() = 0;
    static Source* create(std::string json);
};

class IpCamera: public Source
{
    std::string address;
    std::string username;
    std::string password;
public:
    IpCamera() {}
    IpCamera(std::string name, std::string address, std::string username, std::string password) :
        Source(name), address{address}, username{username}, password{password} {};
    IpCamera(std::string jsonStr);
    /**
     * @brief Функция для получения url камеры
     * @param type - для ip-камеры выбор потока (1 или 2)
     * @return строка url-камеры
     */
    virtual std::string getUrl(int type=1);

    /**
     * @brief Функция для создания камеры фабричным методом
     * @param имя камеры
     * @param адресс камеры
     * @param имя пользователя
     * @param пароль
     * @return указатель на созданный объект камеры
     */
    //virtual Source* create(std::string json) override;
    static Source * create(std::string name, std::string address, std::string username, std::string password);
    virtual std::string toJson();
};

class UsbCamera: public Source
{
    std::string device;
public:
    UsbCamera(std::string name, std::string device) :
        Source(name), device{device} {};
    UsbCamera(std::string jsonStr);

    /**
     * @brief Функция для получения url камеры
     * @param type - дополнительный параметр для выбора потока (1 или 2)
     * @return строка url-камеры
     */
    virtual std::string getUrl(int type=1);

    /**
     * @brief Функция для создания камеры фабричным методом
     * @param имя камеры
     * @param адресс устройства
     * @return указатель на созданный объект камеры
     */
    static Source * create(std::string name, std::string device);
    virtual std::string toJson();
};

class VideoTape: public Source
{
    std::string fileName;
public:
    VideoTape(std::string name, std::string fileName) :
        Source(name), fileName{fileName} {};
    VideoTape(std::string jsonStr);

    /**
     * @brief Функция для получения url камеры
     * @param type - дополнительный параметр для выбора потока (1 или 2)
     * @return строка url-камеры
     */
    virtual std::string getUrl(int type=1);

    /**
     * @brief Функция для создания камеры фабричным методом
     * @param имя камеры
     * @param адресс устройства
     * @return указатель на созданный объект камеры
     */
    static Source *create(std::string name, std::string fileName);
    virtual std::string toJson();
};

#endif // SOURCE_H
