//
// Created by Jakub Kurek on 08/04/2025.
//

#ifndef QVISUALIZER_H
#define QVISUALIZER_H

#include <QGraphicsScene>
#include "Visualizer.h"
#include <QWidget>

class QVisualizer final : public QWidget, public Visualizer {
    Q_OBJECT

public:
    explicit QVisualizer(QWidget *parent);

    void draw(MazeGeneratorVisualizationData *mazeData, MicrmouseVisualizationData *micromouseData) override;

private:
    QGraphicsScene *scene;
    QPen *wallPen;
    int cellSize;

    void drawMaze(const MazeGeneratorVisualizationData &mazeData) const;
    void drawMicromouse(const MicrmouseVisualizationData &micromouseData) const;
};


#endif //QVISUALIZER_H
