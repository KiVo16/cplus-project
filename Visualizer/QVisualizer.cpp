//
// Created by Jakub Kurek on 08/04/2025.
//

#include "QVisualizer.h"

#include <iostream>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QPainterPath>

QVisualizer::QVisualizer(QWidget *parent)
    : QWidget(parent), cellSize(20) {
    scene = new QGraphicsScene(this);
    auto *view = new QGraphicsView(scene, this);
    auto *layout = new QVBoxLayout(this);
    wallPen = new QPen(Qt::black);
    layout->addWidget(view);
    setLayout(layout);
}

void QVisualizer::draw(MazeGeneratorVisualizationData *mazeData, MicrmouseVisualizationData *micromouseData) {
    QMetaObject::invokeMethod(this, [this, mazeData, micromouseData]() {
        scene->clear();
        if (mazeData) drawMaze(*mazeData);
        if (micromouseData) drawMicromouse(*micromouseData);
    }, Qt::QueuedConnection);
}

void QVisualizer::drawMaze(const MazeGeneratorVisualizationData &d) const {
    auto rows = d.maze.size();
    auto cols = d.maze[0].size();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int x = j * cellSize;
            int y = i * cellSize;
            Cell cell = d.maze[i][j];
            QPoint currentPoint(i, j);
            QColor cellColor = Qt::white;

            if (cell.visited) cellColor = QColor(200, 200, 255);
            if (d.current == currentPoint && !d.isFinished) cellColor = QColor(100, 255, 100);

            if (d.startPoint == currentPoint) cellColor = QColor(153, 221, 231);
            if (d.solutionPoint == currentPoint) cellColor = QColor(255, 0, 0);

            scene->addRect(x, y, cellSize, cellSize, QPen(Qt::NoPen), QBrush(cellColor));

            if (cell.walls[0])
                scene->addLine(x, y, x + cellSize, y, *wallPen);
            if (cell.walls[1])
                scene->addLine(x + cellSize, y, x + cellSize, y + cellSize, *wallPen);
            if (cell.walls[2])
                scene->addLine(x, y + cellSize, x + cellSize, y + cellSize, *wallPen);
            if (cell.walls[3])
                scene->addLine(x, y, x, y + cellSize, *wallPen);
        }
    }
}

void QVisualizer::drawMicromouse(const MicrmouseVisualizationData &d) const {
    QPoint micromousePos = d.currentPosition;
    std::vector<MicrmouseStep> micromousePath = d.path;
    if (!micromousePath.empty()) {
        QPainterPath mousePath;
        mousePath.moveTo(micromousePath[0].pos.y() * cellSize + cellSize / 2,
                         micromousePath[0].pos.x() * cellSize + cellSize / 2);
        for (size_t i = 1; i < micromousePath.size(); ++i) {
            mousePath.lineTo(micromousePath[i].pos.y() * cellSize + cellSize / 2,
                             micromousePath[i].pos.x() * cellSize + cellSize / 2);
        }
        QPen mousePathPen(Qt::darkGreen);
        mousePathPen.setWidth(2);
        scene->addPath(mousePath, mousePathPen);
    }


    int currentMouseOrientation = d.currentOrientation;
    if (micromousePos != QPoint(-1, -1)) {
        const int cx = micromousePos.y() * cellSize;
        const int cy = micromousePos.x() * cellSize;
        QPolygonF triangle;
        triangle << QPointF(cx + cellSize / 2.0, cy + cellSize / 4.0) // Tip
                << QPointF(cx + cellSize / 4.0, cy + 3 * cellSize / 4.0) // Bottom left
                << QPointF(cx + 3 * cellSize / 4.0, cy + 3 * cellSize / 4.0); // Bottom right
        // Rotate the triangle based on current orientation.
        QPointF center(cx + cellSize / 2.0, cy + cellSize / 2.0);
        double angle = 0.0;
        switch (currentMouseOrientation) {
            case 0: angle = 0.0;
                break; // North
            case 1: angle = 90.0;
                break; // East
            case 2: angle = 180.0;
                break; // South
            case 3: angle = 270.0;
                break; // West
            default: angle = 0.0;
                break;
        }
        QTransform transform;
        transform.translate(center.x(), center.y());
        transform.rotate(angle);
        transform.translate(-center.x(), -center.y());
        const QPolygonF rotatedTriangle = transform.map(triangle);
        const QPen mousePen(Qt::blue);
        const QBrush mouseBrush(Qt::blue);
        scene->addPolygon(rotatedTriangle, mousePen, mouseBrush);
    }
}
