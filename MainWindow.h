//
// Created by Jakub Kurek on 20/03/2025.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H




#include <QWidget>
#include "MazeVisualizer.h"
#include "MicromouseController.h"
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
private:
    MazeVisualizer *visualizer;
    QComboBox *mazeAlgoCombo;
    QComboBox *mouseAlgoCombo;
    QComboBox *solutionCombo;
    QCheckBox *visualizeCheck;
    QPushButton *startMazeButton;
    QPushButton *skipMazeGenerationVisualizationButton;
    QPushButton *startMouseButton;

    SolutionPoint determineSolutionPoint();
    MazeGenerator* determineMazeGenerator(int rows, int cols);
    MicromouseController* determineMicromouseController();

    void startMazeGeneration();
    void skipMazeGenerationVisualization() const;
    void startMicromouseSimulation();
};

#endif //MAINWINDOW_H
