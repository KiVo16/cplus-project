//
// Created by Jakub Kurek on 20/03/2025.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>

#include "Controller.h"
#include "Visualizer/QVisualizer.h"

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
private:
    Controller *controller;
    QVisualizer *visualizer;
    QComboBox *mazeAlgoCombo;
    QComboBox *mouseAlgoCombo;
    QComboBox *solutionCombo;
    QCheckBox *visualizeCheck;
    QPushButton *startMazeButton;
    QPushButton *skipMazeGenerationVisualizationButton;
    QPushButton *startMouseButton;

    SolutionPoint determineSolutionPoint() const;
    MazeGenerator* determineMazeGenerator(int rows, int cols) const;
    MicromouseController* determineMicromouseController() const;

    void startMazeGeneration() const;
    void skipMazeGenerationVisualization() const;
    void startMicromouseSimulation() const;
};

#endif //MAINWINDOW_H
