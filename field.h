#ifndef FIELD_H
#define FIELD_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QtGlobal>
#include <QList>
#include <QPoint>
#include <QBrush>

#include <cstddef>

#include "snake.h"
#include "levelmap.h"

class Field : public QWidget
{
    Q_OBJECT
public:
    Field(qint32 w, qint32 h, qint32 side, QWidget* parent=0);
    void setSnake(const Snake*);
    void setMap(const LevelMap*);

protected:
    void paintEvent(QPaintEvent *event);


private:
    qint32 m_w;
    qint32 m_h;
    qint32 m_side;
    const Snake* m_snake;
    const LevelMap* m_map;

    void drawMesh(QPainter* painter);
    void drawSnake(QPainter* painter);
    void drawMap(QPainter* painter);

};

#endif // FIELD_H
