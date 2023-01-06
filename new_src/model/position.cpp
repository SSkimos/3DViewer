#include "Position.h"

Position::Position() {
    //TODO: конструктор должен принимать параметры и вызывать сеттеры
    //TODO: подумать над тем, чтобы разделить Rotate и Move на два класса
}

Position::~Position() {
    //TODO: разобраться с тем, что должен делать деструктор 
}

void Position::setRotateX(int newValue) {
    rotateX = newValue;
}

void Position::setRotateY(int newValue) {
    rotateY = newValue;
}

void Position::setRotateZ(int newValue) {
    rotateZ = newValue;
}

int Position::getRotateX() const {
    return rotateX;
}

int Position::getRotateY() const {
    return rotateY;
}

int Position::getRotateZ() const {
    return rotateZ;
}

void Position::setMoveX(int newValue) {
    moveX = newValue;
}

void Position::setMoveY(int newValue) {
    moveY = newValue;
}

void Position::setMoveZ(int newValue) {
    moveZ = newValue;
}

int Position::getMoveX() const {
    return moveX;
}

int Position::getMoveY() const {
    return moveY;
}
int Position::getMoveZ() const {
    return moveZ;
}
