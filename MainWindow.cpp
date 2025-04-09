#include "MainWindow.h"

#include <iostream>
#include <QVBoxLayout>

#include "Controller.h"
#include "MazeGenerator/AldousBroderMazeGenerator.h"
#include "MazeGenerator/PrimsMazeGenerator.h"
#include "MazeGenerator/RecursiveBacktracker.h"
#include "MicromouseController/FloodFillMicromouseController.h"
#include "MicromouseController/WallFollowerController.h"
#include "Visualizer/QVisualizer.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    visualizer = new QVisualizer(this);
    controller = new Controller(visualizer);

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

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(mazeAlgoCombo);
    layout->addWidget(solutionCombo);
    layout->addWidget(mouseAlgoCombo);
    layout->addWidget(visualizeCheck);
    layout->addWidget(startMazeButton);
    layout->addWidget(skipMazeGenerationVisualizationButton);
    layout->addWidget(startMouseButton);
    layout->addWidget(visualizer);
    setLayout(layout);

    controller->signal.connect([this](ControllerSignal s) {
        switch (s) {
            case ControllerSignal::MAZE_GENERATION_FINISHED:
                skipMazeGenerationVisualizationButton->setVisible(false);
                startMouseButton->setEnabled(true);
            case ControllerSignal::MICROMOUSE_FINISHED:
                startMouseButton->setEnabled(true);
        }
    });
}

void MainWindow::startMazeGeneration() const {
    startMouseButton->setEnabled(false);
    constexpr int rows = 20;
    constexpr int cols = 20;
    controller->startMazeGeneration(determineMazeGenerator(rows, cols), determineSolutionPoint());

    if (visualizeCheck->isChecked()) {
        skipMazeGenerationVisualizationButton->setVisible(true);
        return;
    }

    startMouseButton->setEnabled(false);
    skipMazeGenerationVisualization();
    skipMazeGenerationVisualizationButton->setVisible(false);
}

SolutionPoint MainWindow::determineSolutionPoint() const {
    QString solChoice = solutionCombo->currentText();
    if (solChoice == "Top Left") return SolutionPoint::TOP_LEFT;
    if (solChoice == "Top Right") return SolutionPoint::TOP_RIGHT;
    if (solChoice == "Bottom Left") return SolutionPoint::BOTTOM_LEFT;
    if (solChoice == "Bottom Right") return SolutionPoint::BOTTOM_RIGHT;
    return SolutionPoint::CENTER;
}

MazeGenerator *MainWindow::determineMazeGenerator(const int rows, const int cols) const {
    QString solChoice = mazeAlgoCombo->currentText();
    if (solChoice == "Recursive Backtracker") return new RecursiveBacktracker(rows, cols);
    if (solChoice == "Prim's Algorithm") return new PrimsMazeGenerator(rows, cols);
    return new AldousBroderMazeGenerator(rows, cols);
}

MicromouseController *MainWindow::determineMicromouseController() const {
    QString solChoice = mouseAlgoCombo->currentText();
    if (solChoice == "Left-Hand Rule") return new WallFollowerController();
    if (solChoice == "Flood Fill") return new FloodFillMicromouseController();
    return new WallFollowerController();
}

void MainWindow::skipMazeGenerationVisualization() const {
    controller->skipMazeGenerationVisualisation();
    skipMazeGenerationVisualizationButton->setVisible(false);
}

void MainWindow::startMicromouseSimulation() const {
    controller->startMicromouse(determineMicromouseController());
}
