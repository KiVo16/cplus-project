//
// Created by Jakub Kurek on 20/03/2025.
//

#ifndef MAZEVISUALIZER_H
#define MAZEVISUALIZER_H

#include <QWidget>
#include <QGraphicsScene>
#include "MazeGenerator.h"
#include <QTimer>
#include <QPoint>

#include "MicromouseController.h"

enum class SolutionPoint {
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
    CENTER
};

class MazeVisualizer : public QWidget {
    Q_OBJECT

public:
    explicit MazeVisualizer(QWidget *parent);

    void startMazeGeneration(MazeGenerator *mazeGenerator, SolutionPoint point);

    void startMicromouse(MicromouseController *micromouseController);

    void skipMazeGenerationVisualisation();

private:
    QGraphicsScene *scene;
    QTimer *timerMaze;
    QTimer *timerMicroMouse;

    int cellSize;
    QPen wallPen;

    QPoint startPoint;
    QPoint solutionPoint;

    MazeGenerator *mazeGenerator = nullptr;
    MicromouseController *micromouseController = nullptr;

    void draw();

    void drawMaze();

    void drawMicromouse();

    void updateMaze();

    void updateMicromouse();

    void setupStartEndPoint(SolutionPoint point);

signals:
    void generationFinished();
};

#endif //MAZEVISUALIZER_H
