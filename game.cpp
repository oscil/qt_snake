#include "game.h"

Game::Game(qint32 w, qint32 h):
    m_w(w),
    m_h(h),
    m_map(w, h),
    m_direction(DIR_UP)
{
    for (int i = 0 ; i < 3; ++i){
        m_snake.points.append(Point( qint32(m_w/2),
                               qint32(m_h/2)-2+i));
    }
}

void Game::update(QKeyEvent * event)
{
    m_direction = trySetDirection(event);
    if (checkSelfCollision()){
        stop();
    }
    if (checkWallCollision()){
        stop();
    }
    bool has_feed = checkFoodCollision();
    m_map.setSnake(&(m_snake.points));
    switch (m_direction){
        case DIR_LEFT:
            moveLeft(has_feed);
            break;
        case DIR_RIGHT:
            moveRight(has_feed);
            break;
        case DIR_UP:
            moveUp(has_feed);
            break;
        case DIR_DOWN:
            moveDown(has_feed);
            break;
        case DIR_NONE:
            stop();
            break;
    }
}

Game::SNAKE_DIRECTION Game::trySetDirection(QKeyEvent* event)
{
    SNAKE_DIRECTION out = m_direction;
    switch (event->key()){
        case Qt::Key_Left:
            out = DIR_LEFT;
            break;
        case Qt::Key_Right:
            out = DIR_RIGHT;
            break;
        case Qt::Key_Up:
            out = DIR_UP;
            break;
        case Qt::Key_Down:
            out = DIR_DOWN;
            break;
    }
    return out;
}

bool Game::checkWallCollision()
{
    if (m_map.getMap()->at(m_snake.points[0].y).at(m_snake.points[0].x) == LevelMap::CELL_STATUS::CELL_WALL ){
        return true;
    }
    return false;
}

bool Game::checkSelfCollision()
{
    for (int i = 1 ; i < m_snake.points.size(); ++i){
        if (m_snake.points[i].x == m_snake.points[0].x && m_snake.points[i].y == m_snake.points[0].y)
            return true;
    }
    return false;
}

bool Game::checkFoodCollision()
{
    if (m_map.getMap()->at(m_snake.points[0].y).at(m_snake.points[0].x) == LevelMap::CELL_STATUS::CELL_FOOD ){
        m_map.gotFood(m_snake.points[0].y, m_snake.points[0].x);
        return true;
    }
    return false;
}

const Snake *Game::getSnake() const
{
    return &m_snake;
}

const LevelMap *Game::getMap() const
{
    return &m_map;
}

void Game::redrag(bool has_feed)
{
    qint32 size_for_move = m_snake.points.size()-1;

    if (has_feed){
        Point p = Point(m_snake.points.last().x, m_snake.points.last().y);
        m_snake.points.append(p);
    }

    for (int i = size_for_move; i > 0; --i){
        m_snake.points[i] = m_snake.points[i-1];
    }
}

void Game::moveLeft(bool has_feed)
{
    redrag(has_feed);
    m_snake.points[0].x-=1;
}

void Game::moveRight(bool has_feed)
{
    redrag(has_feed);
    m_snake.points[0].x+=1;
}

void Game::moveUp(bool has_feed)
{
    redrag(has_feed);
    m_snake.points[0].y-=1;
}

void Game::moveDown(bool has_feed)
{
    redrag(has_feed);
    m_snake.points[0].y+=1;
}

void Game::stop()
{
    m_direction = DIR_NONE;
}


