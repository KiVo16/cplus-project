#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>

#include "Controller.h"
#include "Maze/Generator/MazeGenerator.h"
#include "Micromouse/Controller/MicromouseController.h"
#include "Visualizer/QVisualizer.h"

class MainWindow : public QWidget {
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
private:
    Controller *controller;
    QVisualizer *visualizer;

    QLayout *layout;

    QLabel *mazeAlgoComboLabel;
    QComboBox *mazeAlgoCombo;

    QLabel *mouseAlgoComboLabel;
    QComboBox *mouseAlgoCombo;

    QLabel *solutionComboLabel;
    QComboBox *solutionCombo;

    QCheckBox *visualizeCheck;
    QPushButton *startMazeButton;
    QPushButton *skipMazeGenerationVisualizationButton;
    QPushButton *startMouseButton;

    QSlider *mazeSizeSlider;
    QLabel *mazeSizeLabel;


    void onMazeSizeChanged(int size) const;

    /**
     * picks solution point position based on combobox
    */
    SolutionPoint determineSolutionPoint() const;

    /**
     * defines appropriate maze generator type based on combobox
     * @return appropriate maze generator type
    */
    MazeGeneratorType determineMazeGenerator() const;

    /**
     * defines appropriate micromouse controller type based on combobox
     * @return appropriate micromouse controller type
    */
    MicromouseControllerType determineMicromouseController() const;

    /**
     * starts maze generation
    */
    void startMazeGeneration() const;

    /**
     * initialize skip of maze generation visualization
    */
    void skipMazeGenerationVisualization() const;

    /**
     * starts micromouse path finding
    */
    void startMicromouseSimulation() const;
};

#endif //MAINWINDOW_H
