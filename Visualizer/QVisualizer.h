#ifndef QVISUALIZER_H
#define QVISUALIZER_H

#include <QGraphicsScene>
#include <QVBoxLayout>

#include "Visualizer.h"
#include <QWidget>

class QVisualizer final : public QWidget, public Visualizer {
    Q_OBJECT

public:
    explicit QVisualizer(QWidget *parent);

    void draw(MazeGeneratorVisualizationData *mazeData, MicrmouseVisualizationData *micromouseData) override;
private:
    /// Qt base scene object
    QGraphicsScene *scene;

    /// Qt view object attached to scene
    QGraphicsView *view;

    /// Qt layout object attached to view
    QVBoxLayout *layout;

    /// Qt pen used to draw maze walls
    QPen *wallPen;

    /// single cell size
    int cellSize;

    /**
     * draws maze based on provided data
     * @param mazeData data used for maze visualization
     */
    void drawMaze(const MazeGeneratorVisualizationData &mazeData) const;

    /**
     * draws micromouse based on provided data
     * @param micromouseData data user for micromouse visualization
     */
    void drawMicromouse(const MicrmouseVisualizationData &micromouseData) const;
};


#endif //QVISUALIZER_H
