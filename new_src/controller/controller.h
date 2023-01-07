#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "../model/position.h"

class Controller
{
public:
    Controller();
    ~Controller();
    void updateValue(int newValue);

private:
    Position *position;
};

#endif