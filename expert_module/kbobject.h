#ifndef KBOBJECT_H
#define KBOBJECT_H

#include <string>

class KBObject
{
    int id;
public:
    KBObject() {};
    void setId(int id) {this->id = id;}
    int getId() {return id;}
    virtual std::string toJson() = 0;
};

#endif // KBOBJECT_H
