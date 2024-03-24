#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H


class GameManager
{
public:
    GameManager();
    void setNumberOfCells(int _n);

    int getNumberOfCells() const;

private:
    int numberOfCells;

};

#endif // GAMEMANAGER_H
