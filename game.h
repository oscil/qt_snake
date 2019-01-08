#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QtGlobal>
#include <QList>
#include <QPoint>
#include <QKeyEvent>
#include <QDebug>

#include "snake.h"
#include "levelmap.h"


class Game
{
public:
    Game(qint32 w, qint32 h);
    void update(QKeyEvent*);
    const Snake* getSnake() const;
    const LevelMap* getMap() const;

private:
    Snake m_snake;
    qint32 m_w;
    qint32 m_h;
    LevelMap m_map;
    enum SNAKE_DIRECTION {DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN, DIR_NONE};
    SNAKE_DIRECTION m_direction;

    SNAKE_DIRECTION trySetDirection(QKeyEvent*);
    bool checkWallCollision();
    bool checkSelfCollision();
    bool checkFoodCollision();


    void redrag(bool has_feed);
    void moveLeft(bool has_feed);
    void moveRight(bool has_feed);
    void moveUp(bool has_feed);
    void moveDown(bool has_feed);
    void stop();

};

#endif // GAME_H
