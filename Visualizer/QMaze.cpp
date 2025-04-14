#include "QMaze.h"

QRectF QMaze::boundingRect() const {
    if (!d.maze) return QRectF();
    return QRectF(0, 0, d.maze->getColsCount() * cellSize, d.maze->getRowsCount() * cellSize);
}

void QMaze::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    if (!d.maze) return;
    auto rows = d.maze->getRowsCount();
    auto cols = d.maze->getColsCount();
    painter->setPen(*wallPen);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int x = j * cellSize;
            int y = i * cellSize;
            auto cell = d.maze->getCell(i, j);
            if (!cell) continue;
            QPoint currentPoint(i, j);
            QColor cellColor = Qt::white;

            if (d.visitedCoordinates.contains(std::make_pair(i, j))) cellColor = QColor(200, 200, 255);
            if (d.current == currentPoint && !d.isFinished) cellColor = QColor(100, 255, 100);
            if (d.startPoint == currentPoint) cellColor = QColor(153, 221, 231);
            if (d.solutionPoint == currentPoint) cellColor = QColor(255, 0, 0);

            painter->fillRect(x, y, cellSize, cellSize, cellColor);

            if (cell->walls[0])
                painter->drawLine(x, y, x + cellSize, y);
            if (cell->walls[1])
                painter->drawLine(x + cellSize, y, x + cellSize, y + cellSize);
            if (cell->walls[2])
                painter->drawLine(x, y + cellSize, x + cellSize, y + cellSize);
            if (cell->walls[3])
                painter->drawLine(x, y, x, y + cellSize);
        }
    }
}