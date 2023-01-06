#ifndef POSITION_H
#define POSITION_H

class Position
{
public:
    void setRotateX(int newValue);
    void setRotateY(int newValue);
    void setRotateZ(int newValue);
    int getRotateX() const;
    int getRotateY() const;
    int getRotateZ() const;

    void setMoveX(int newValue);
    void setMoveY(int newValue);
    void setMoveZ(int newValue);
    int getMoveX() const;
    int getMoveY() const;
    int getMoveZ() const;

private:
    int rotateX;
    int rotateY;
    int rotateZ;
    int moveX;
    int moveY;
    int moveZ;
};

#endif // POSITION_H
