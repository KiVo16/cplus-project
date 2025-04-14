#ifndef QMAZE_H
#define QMAZE_H

#include <QGraphicsItem>
#include <qpainter.h>

#include "Visualizer.h"

class QMaze : public QGraphicsItem {
public:
    QMaze(const MazeGeneratorVisualizationData &data, int cellSize)
        : d(data), cellSize(cellSize), wallPen(new QPen(Qt::black)) {
    }

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
private:
    MazeGeneratorVisualizationData d;
    int cellSize;
    QPen *wallPen;
};


#endif //QMAZE_H
