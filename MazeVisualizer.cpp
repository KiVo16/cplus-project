#include "MazeVisualizer.h"
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QVBoxLayout>
#include <QPen>
#include <iostream>

MazeVisualizer::MazeVisualizer(QWidget *parent)
    : QWidget(parent), cellSize(20), timerMaze(new QTimer(this)), timerMicroMouse(new QTimer(this)) {
    scene = new QGraphicsScene(this);
    QGraphicsView *view = new QGraphicsView(scene, this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    QPen *wallPen = new QPen(Qt::black);
    layout->addWidget(view);
    setLayout(layout);

    connect(timerMaze, &QTimer::timeout, this, &MazeVisualizer::updateMaze);
    connect(timerMicroMouse, &QTimer::timeout, this, &MazeVisualizer::updateMicromouse);
}

void MazeVisualizer::startMazeGeneration(MazeGenerator *mg, SolutionPoint sp) {
    scene->clear();
    mazeGenerator = mg;
    setupStartEndPoint(sp);
    timerMaze->start(5);
    micromouseController = nullptr;
}

void MazeVisualizer::startMicromouse(MicromouseController *mc) {
    if (!mazeGenerator || !mazeGenerator->isFinished()) return;
    micromouseController = mc;
    micromouseController->setup(mazeGenerator->getMaze(), startPoint, solutionPoint);
    timerMicroMouse->start(5);
}

void MazeVisualizer::setupStartEndPoint(SolutionPoint sp) {
    if (!mazeGenerator) return;
    const auto &mazeData = mazeGenerator->getMaze();
    int rows = mazeData.size() - 1;
    int cols = mazeData[0].size() - 1;

    switch (sp) {
        case SolutionPoint::TOP_LEFT:
            solutionPoint = QPoint(0, 0);
            startPoint = QPoint(cols, rows);
            break;
        case SolutionPoint::TOP_RIGHT:
            solutionPoint = QPoint(0, rows);
            startPoint = QPoint(cols, 0);
            break;
        case SolutionPoint::BOTTOM_LEFT:
            solutionPoint = QPoint(cols, 0);
            startPoint = QPoint(0, rows);
            break;
        case SolutionPoint::BOTTOM_RIGHT:
            solutionPoint = QPoint(cols, rows);
            startPoint = QPoint(0, 0);
            break;
        case SolutionPoint::CENTER:
            solutionPoint = QPoint(cols / 2, rows / 2);
            startPoint = QPoint(0, 0);
            break;
    }
}

void MazeVisualizer::draw() {
    scene->clear();
    drawMaze();
    drawMicromouse();
}

void MazeVisualizer::drawMaze() {
    if (!mazeGenerator) return;

    const auto &mazeData = mazeGenerator->getMaze();
    QPoint current = mazeGenerator->getCurrentCell();

    int rows = mazeData.size();
    int cols = mazeData[0].size();

    // Draw cells
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int x = j * cellSize;
            int y = i * cellSize;
            QColor cellColor = Qt::white;

            if (mazeData[i][j].visited) cellColor = QColor(200, 200, 255);
            if (current == QPoint(i, j) && !mazeGenerator->isFinished()) cellColor = QColor(100, 255, 100);
            if (startPoint == QPoint(i, j)) cellColor = QColor(153, 221, 231);
            if (solutionPoint == QPoint(i, j)) cellColor = QColor(255, 0, 0);

            scene->addRect(x, y, cellSize, cellSize, QPen(Qt::NoPen), QBrush(cellColor));

            if (mazeData[i][j].walls[0])
                scene->addLine(x, y, x + cellSize, y, wallPen);
            if (mazeData[i][j].walls[1])
                scene->addLine(x + cellSize, y, x + cellSize, y + cellSize, wallPen);
            if (mazeData[i][j].walls[2])
                scene->addLine(x, y + cellSize, x + cellSize, y + cellSize, wallPen);
            if (mazeData[i][j].walls[3])
                scene->addLine(x, y, x, y + cellSize, wallPen);
        }
    }
}

void MazeVisualizer::drawMicromouse() {
    if (!micromouseController) return;
    QPoint micromousePos = micromouseController->currentPosition();
    std::vector<MicrmouseStep> micromousePath = micromouseController->path();
    if (!micromousePath.empty()) {
        QPainterPath mousePath;
        mousePath.moveTo(micromousePath[0].pos.y() * cellSize + cellSize/2,
                         micromousePath[0].pos.x() * cellSize + cellSize/2);
        for (size_t i = 1; i < micromousePath.size(); ++i) {
            mousePath.lineTo(micromousePath[i].pos.y() * cellSize + cellSize/2,
                             micromousePath[i].pos.x() * cellSize + cellSize/2);
        }
        QPen mousePathPen(Qt::darkGreen);
        mousePathPen.setWidth(2);
        scene->addPath(mousePath, mousePathPen);
    }


    int currentMouseOrientation = micromouseController->currentOrientation();
    // Draw current micromouse as a triangle pointing in its current direction.
    if (micromousePos != QPoint(-1,-1)) {
        int cx = micromousePos.y() * cellSize;
        int cy = micromousePos.x() * cellSize;
        // Define a default triangle for North orientation.
        QPolygonF triangle;
        triangle << QPointF(cx + cellSize/2.0, cy + cellSize/4.0)  // Tip
                 << QPointF(cx + cellSize/4.0, cy + 3*cellSize/4.0) // Bottom left
                 << QPointF(cx + 3*cellSize/4.0, cy + 3*cellSize/4.0); // Bottom right
        // Rotate the triangle based on current orientation.
        QPointF center(cx + cellSize/2.0, cy + cellSize/2.0);
        double angle = 0.0;
        switch (currentMouseOrientation) {
            case 0: angle = 0.0; break;      // North
            case 1: angle = 90.0; break;     // East
            case 2: angle = 180.0; break;    // South
            case 3: angle = 270.0; break;    // West
            default: angle = 0.0; break;
        }
        QTransform transform;
        transform.translate(center.x(), center.y());
        transform.rotate(angle);
        transform.translate(-center.x(), -center.y());
        QPolygonF rotatedTriangle = transform.map(triangle);
        QPen mousePen(Qt::blue);
        QBrush mouseBrush(Qt::blue);
        scene->addPolygon(rotatedTriangle, mousePen, mouseBrush);
    }
}


void MazeVisualizer::updateMaze() {
    if (!mazeGenerator) return;
    if (!mazeGenerator->isFinished()) mazeGenerator->step();
    else {
        timerMaze->stop();
        emit generationFinished();
    }
    draw();
}

void MazeVisualizer::updateMicromouse() {
    if (!micromouseController) return;
    if (!micromouseController->isFinished()) micromouseController->step();
    else timerMicroMouse->stop();
    draw();
}

void MazeVisualizer::skipMazeGenerationVisualisation() {
    if (!mazeGenerator) return;
    timerMaze->stop();
    mazeGenerator->finishInstantly();
    emit generationFinished();
    draw();
}

