#include "levelmap.h"

LevelMap::LevelMap(qint32 w, qint32 h):
    m_w(w),
    m_h(h),
    m_map( m_h, QVector<CELL_STATUS>(m_w, CELL_STATUS::CELL_EMPTY) ),
    m_gen(QTime::currentTime().msecsSinceStartOfDay())
{
    qDebug() << "MAP 0 = " << m_map.size() << " MAP 1 = " << m_map[0].size();
    addMainWalls();
    addAdditionWalls(20);
    addFood(40);
}

const QVector<QVector<LevelMap::CELL_STATUS> >* LevelMap::getMap() const
{
    return &m_map;
}

void LevelMap::gotFood(qint32 x, qint32 y)
{
    m_map[x][y] = CELL_STATUS::CELL_SNAKE;
    while(true){
        qint32 x1 = m_gen.bounded(1, m_w-2);
        qint32 y1 = m_gen.bounded(1, m_h-2);
        if (m_map[y1][x1] == CELL_STATUS::CELL_EMPTY){
            m_map[y1][x1] = CELL_STATUS::CELL_FOOD;
            return;
        }
    }
}

void LevelMap::setSnake(const QVector<Point> *snake)
{
    static QVector<Point> prev_snake;
    for (Point& p : prev_snake){
        m_map[p.y][p.x] = CELL_STATUS::CELL_EMPTY;
    }
    for (const Point& p : *snake){
        if (m_map[p.y][p.x] != CELL_STATUS::CELL_WALL)
            m_map[p.y][p.x] = CELL_STATUS::CELL_SNAKE;
    }
    prev_snake = *snake;
}

void LevelMap::addMainWalls()
{
    //line up
    for (int i = 0 ; i < m_map[0].size(); ++i){
        m_map[0][i] = CELL_STATUS::CELL_WALL;
    }

    //line down
    for (int i = 0 ; i < m_map.last().size(); ++i)
        m_map[m_map.size()-1][i] = CELL_STATUS::CELL_WALL;

    //line left
    for (int i = 0 ; i < m_map.size(); ++i)
        m_map[i][0] = CELL_STATUS::CELL_WALL;

    //line right
    for (int i = 0 ; i < m_map.size(); ++i)
        m_map[i][ m_map[0].size()-1 ] = CELL_STATUS::CELL_WALL;
}

void LevelMap::addAdditionWalls(qint32 count)
{
    for (int i = 0 ; i < count; ++i){
        qint32 c = m_gen.bounded(1, m_w-2);
        qint32 r = m_gen.bounded(1, m_h-2);
        m_map[r][c] = CELL_STATUS::CELL_WALL;
    }
}


void LevelMap::addFood(qint32 count)
{
    for (int i = 0 ; i < count; ++i){
        qint32 c = m_gen.bounded(1, m_w-2);
        qint32 r = m_gen.bounded(1, m_h-2);
        if (m_map.at(r).at(c) == CELL_STATUS::CELL_EMPTY)
            m_map[r][c] = CELL_STATUS::CELL_FOOD;
    }
}
