#ifndef ZONE_H
#define ZONE_H

#include <string>
#include <vector>
#include "kbobject.h"

class Zone : public KBObject
{
    std::string name;
    std::string description;
    std::string color;
    std::vector<int> listSegments;
    int segSize;
    int frameWidth;
    int frameHeight;
public:
    Zone();
    Zone(std::string name, std::string description, std::string color, int segSize, int frameWidth, int frameHeight);
    Zone(std::string jsonString);

    const std::string &getName() const;
    void setName(const std::string &newName);
    const std::string &getDescription() const;
    void setDescription(const std::string &newDescription);
    const std::string &getColor() const;
    void setColor(const std::string &newColor);
    const std::vector<int> &getListSegments() const;
    void setListSegments(const std::vector<int> &newListSegments);
    int getSegSize() const;
    void setSegSize(int newSegSize);
    int getFrameWidth() const;
    void setFrameWidth(int newFrameWidth);
    int getFrameHeight() const;
    void setFrameHeight(int newFrameHeight);
    virtual std::string toJson();
    static Zone* fromJson(std::string jsonStr);
};

#endif // ZONE_H
