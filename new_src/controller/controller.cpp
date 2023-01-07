#include "controller.h"

Controller::Controller()
{
    position = new Position();
}

Controller::~Controller()
{
    delete position;
}

void Controller::updateValue(int newValue)
{
    position->setRotateX(newValue);
}
