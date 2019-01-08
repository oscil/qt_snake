#ifndef LEVELMAP_H
#define LEVELMAP_H


#include <QtGlobal>
#include <QVector>
#include <QRandomGenerator>
#include <QTime>
#include <QDebug>

#include "point.h"

class LevelMap
{
public:
    LevelMap(qint32 w, qint32 h);
    enum class CELL_STATUS : quint32 {CELL_EMPTY, CELL_WALL, CELL_FOOD, CELL_SNAKE};
    const QVector< QVector<CELL_STATUS> >* getMap() const;
    void gotFood(qint32 x, qint32 y);
    void setSnake(const QVector<Point>*);


private:
    qint32 m_w;
    qint32 m_h;
    QVector< QVector<CELL_STATUS> > m_map;


    void addMainWalls();
    void addAdditionWalls(qint32 count = 20);
    void addFood(qint32 count = 10);
    QRandomGenerator m_gen;

};

#endif // LEVELMAP_H
