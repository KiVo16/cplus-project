#include "QVisualizer.h"

#include <QGraphicsView>
#include <QVBoxLayout>
#include <QPainterPath>

#include "QMaze.h"

QVisualizer::QVisualizer(QWidget *parent)
    : QWidget(parent), cellSize(20) {
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    view = new QGraphicsView(scene, this);
    layout = new QVBoxLayout(this);
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
    if (!d.maze) return;
    scene->addItem(new QMaze(d, cellSize));
}

void QVisualizer::drawMicromouse(const MicrmouseVisualizationData &d) const {
    if (!d.path.empty()) {
        QPainterPath mousePath;
        mousePath.moveTo(d.path[0].pos.y() * cellSize + cellSize / 2,
                         d.path[0].pos.x() * cellSize + cellSize / 2);
        for (size_t i = 1; i < d.path.size(); ++i) {
            mousePath.lineTo(d.path[i].pos.y() * cellSize + cellSize / 2,
                             d.path[i].pos.x() * cellSize + cellSize / 2);
        }
        QPen mousePathPen(Qt::darkGreen);
        mousePathPen.setWidth(2);
        scene->addPath(mousePath, mousePathPen);
    }

    if (d.currentPosition == QPoint(-1, -1)) return;
    const int cx = d.currentPosition.y() * cellSize;
    const int cy = d.currentPosition.x() * cellSize;

    QPolygonF triangle{
        QPointF(cx + cellSize / 2.0, cy + cellSize / 4.0),
        QPointF(cx + cellSize / 4.0, cy + 3 * cellSize / 4.0),
        QPointF(cx + 3 * cellSize / 4.0, cy + 3 * cellSize / 4.0)
    };

    QPointF center(cx + cellSize / 2.0, cy + cellSize / 2.0);
    double angle = d.currentOrientation * 90.0;

    QTransform transform;
    transform.translate(center.x(), center.y());
    transform.rotate(angle);
    transform.translate(-center.x(), -center.y());

    scene->addPolygon(transform.map(triangle), QPen(Qt::blue), QBrush(Qt::blue));
}
