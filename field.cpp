#include "field.h"

Field::Field(qint32 w, qint32 h, qint32 side, QWidget* parent):
    QWidget(parent),
    m_w(w),
    m_h(h),
    m_side(side),
    m_snake(nullptr)
{

}


void Field::setSnake(const Snake* snake)
{
    m_snake = snake;
}

void Field::setMap(const LevelMap * map)
{
    m_map = map;
}

void Field::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    drawMesh(&painter);
    drawMap(&painter);
    drawSnake(&painter);
}


void Field::drawMesh(QPainter *painter)
{
    for (qint32  r = 0; r < m_h+1; r++){
        painter->drawLine(0, r*m_side, m_w*m_side, r*m_side);
    }

    for (qint32  c = 0; c < m_w+1; c++){
        painter->drawLine(c*m_side, 0, c*m_side, m_h*m_side);
    }
}

void Field::drawSnake(QPainter *painter)
{
    painter->setBrush(Qt::cyan);
    for (Point p: m_snake->points){
        painter->drawRect(p.x * m_side + 1, p.y * m_side + 1, m_side-2, m_side-2);
    }
    painter->setBrush(Qt::darkCyan);
    painter->drawRect(m_snake->points[0].x * m_side + 1, m_snake->points[0].y * m_side + 1, m_side-2, m_side-2);
}

void Field::drawMap(QPainter *painter)
{
    for (qint32 r = 0; r < m_map->getMap()->size(); ++r)
        for (qint32 c = 0; c < m_map->getMap()->at(r).size(); ++c){
            if (m_map->getMap()->at(r).at(c) == LevelMap::CELL_STATUS::CELL_WALL){
                painter->setBrush(Qt::black);
                painter->drawRect(c * m_side + 1, r * m_side + 1, m_side-2, m_side-2);
            }
            else if (m_map->getMap()->at(r).at(c) == LevelMap::CELL_STATUS::CELL_FOOD){
                painter->setBrush(Qt::green);
                painter->drawRect(c * m_side + 1, r * m_side + 1, m_side-2, m_side-2);
            }
        }
}
