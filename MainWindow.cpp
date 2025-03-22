#include "MainWindow.h"

#include <iostream>
#include <QVBoxLayout>
#include <QTimer>

#include "AldousBroderMazeGenerator.h"
#include "FloodFillMicromouseController.h"
#include "RecursiveBacktracker.h"
#include "PrimsMazeGenerator.h"
#include "WallFollowerController.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    visualizer = new MazeVisualizer(this);

    mazeAlgoCombo = new QComboBox(this);
    mazeAlgoCombo->addItem("Recursive Backtracker");
    mazeAlgoCombo->addItem("Prim's Algorithm");
    mazeAlgoCombo->addItem("Aldous–Broder Algorithm");

    mouseAlgoCombo = new QComboBox(this);
    mouseAlgoCombo->addItem("Left-Hand Rule");
    mouseAlgoCombo->addItem("Flood Fill");

    solutionCombo = new QComboBox(this);
    solutionCombo->addItem("Top Left");
    solutionCombo->addItem("Top Right");
    solutionCombo->addItem("Bottom Left");
    solutionCombo->addItem("Bottom Right");
    solutionCombo->addItem("Center");

    visualizeCheck = new QCheckBox("Visualize Maze Generation", this);
    visualizeCheck->setChecked(true);

    startMazeButton = new QPushButton("Start Maze Generation", this);
    connect(startMazeButton, &QPushButton::clicked, this, &MainWindow::startMazeGeneration);

    skipMazeGenerationVisualizationButton = new QPushButton("Skip", this);
    skipMazeGenerationVisualizationButton->setVisible(false);
    connect(skipMazeGenerationVisualizationButton, &QPushButton::clicked, this,
            &MainWindow::skipMazeGenerationVisualization);

    startMouseButton = new QPushButton("Start Mouse", this);
    startMouseButton->setEnabled(false);
    connect(startMouseButton, &QPushButton::clicked, this, &MainWindow::startMicromouseSimulation);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(mazeAlgoCombo);
    layout->addWidget(solutionCombo);
    layout->addWidget(mouseAlgoCombo);
    layout->addWidget(visualizeCheck);
    layout->addWidget(startMazeButton);
    layout->addWidget(skipMazeGenerationVisualizationButton);
    layout->addWidget(startMouseButton);
    layout->addWidget(visualizer);
    setLayout(layout);

    connect(visualizer, &MazeVisualizer::generationFinished, [=]() {
        skipMazeGenerationVisualizationButton->setVisible(false);
        startMouseButton->setEnabled(true);
    });
}

void MainWindow::startMazeGeneration() {
    int rows = 20, cols = 20;
    visualizer->startMazeGeneration(determineMazeGenerator(rows, cols), determineSolutionPoint());

    if (visualizeCheck->isChecked()) {
        skipMazeGenerationVisualizationButton->setVisible(true);
        return;
    }

    startMouseButton->setEnabled(false);
    skipMazeGenerationVisualization();
    skipMazeGenerationVisualizationButton->setVisible(false);
}

SolutionPoint MainWindow::determineSolutionPoint() {
    QString solChoice = solutionCombo->currentText();
    if (solChoice == "Top Left") return SolutionPoint::TOP_LEFT;
    if (solChoice == "Top Right") return SolutionPoint::TOP_RIGHT;
    if (solChoice == "Bottom Left") return SolutionPoint::BOTTOM_LEFT;
    if (solChoice == "Bottom Right") return SolutionPoint::BOTTOM_RIGHT;
    return SolutionPoint::CENTER;
}

MazeGenerator *MainWindow::determineMazeGenerator(int rows, int cols) {
    QString solChoice = mazeAlgoCombo->currentText();
    if (solChoice == "Recursive Backtracker") return new RecursiveBacktracker(rows, cols);
    if (solChoice == "Prim's Algorithm") return new PrimsMazeGenerator(rows, cols);
    return new AldousBroderMazeGenerator(rows, cols);
}

MicromouseController *MainWindow::determineMicromouseController() {
    QString solChoice = mouseAlgoCombo->currentText();
    if (solChoice == "Left-Hand Rule") return new WallFollowerController();
    if (solChoice == "Flood Fill") return new FloodFillMicromouseController();
}

void MainWindow::skipMazeGenerationVisualization() const {
    visualizer->skipMazeGenerationVisualisation();
    skipMazeGenerationVisualizationButton->setVisible(false);
}

void MainWindow::startMicromouseSimulation() {
    visualizer->startMicromouse(determineMicromouseController());
}
