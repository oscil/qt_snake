#ifndef POINT_H
#define POINT_H

#include <QtGlobal>



class Point
{
public:
    Point(qint32 x = 0, qint32 y = 0);
    qint32 x;
    qint32 y;
};

#endif // POINT_H
