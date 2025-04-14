#include "MainWindow.h"

#include <iostream>
#include <QVBoxLayout>

#include "Controller.h"
#include "Visualizer/QVisualizer.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    visualizer = new QVisualizer(this);
    controller = new Controller(visualizer);

    mazeAlgoComboLabel = new QLabel("Maze generator", this);
    mazeAlgoCombo = new QComboBox(this);
    mazeAlgoCombo->addItem("Recursive Backtracker");
    mazeAlgoCombo->addItem("Prim's Algorithm");
    mazeAlgoCombo->addItem("Aldous–Broder Algorithm");

    mazeSizeLabel = new QLabel("Maze Size: 20", this);
    mazeSizeSlider = new QSlider(Qt::Horizontal, this);
    mazeSizeSlider->setMinimum(20);
    mazeSizeSlider->setMaximum(100);
    mazeSizeSlider->setValue(20);
    connect(mazeSizeSlider, &QSlider::valueChanged, this, &MainWindow::onMazeSizeChanged);

    mouseAlgoComboLabel = new QLabel("Micromouse controller", this);\
    mouseAlgoCombo = new QComboBox(this);
    mouseAlgoCombo->addItem("Wall following");
    mouseAlgoCombo->addItem("Flood Fill");

    solutionComboLabel = new QLabel("Solution position", this);
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

    layout = new QVBoxLayout(this);
    layout->addWidget(mazeAlgoComboLabel);
    layout->addWidget(mazeAlgoCombo);
    layout->addWidget(mazeSizeLabel);
    layout->addWidget(mazeSizeSlider);
    layout->addWidget(solutionComboLabel);
    layout->addWidget(solutionCombo);
    layout->addWidget(visualizeCheck);
    layout->addWidget(startMazeButton);
    layout->addWidget(skipMazeGenerationVisualizationButton);

    layout->addWidget(mouseAlgoComboLabel);
    layout->addWidget(mouseAlgoCombo);
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

void MainWindow::onMazeSizeChanged(int size) const {
    mazeSizeLabel->setText(QString("Maze Size: %1").arg(size));
    controller->setMazeSize(size);
}

void MainWindow::startMazeGeneration() const {
    startMouseButton->setEnabled(false);
    controller->startMazeGeneration(determineMazeGenerator(), determineSolutionPoint());

    if (visualizeCheck->isChecked()) {
        skipMazeGenerationVisualizationButton->setVisible(true);
        return;
    }

    startMouseButton->setEnabled(false);
    skipMazeGenerationVisualization();
    skipMazeGenerationVisualizationButton->setVisible(false);
}

SolutionPointPosition MainWindow::determineSolutionPoint() const {
    QString solChoice = solutionCombo->currentText();
    if (solChoice == "Top Left") return SolutionPointPosition::TOP_LEFT;
    if (solChoice == "Top Right") return SolutionPointPosition::TOP_RIGHT;
    if (solChoice == "Bottom Left") return SolutionPointPosition::BOTTOM_LEFT;
    if (solChoice == "Bottom Right") return SolutionPointPosition::BOTTOM_RIGHT;
    return SolutionPointPosition::CENTER;
}

MazeGeneratorType MainWindow::determineMazeGenerator() const {
    QString solChoice = mazeAlgoCombo->currentText();
    if (solChoice == "Recursive Backtracker") return MazeGeneratorType::RecursiveBacktracking;
    if (solChoice == "Prim's Algorithm") return MazeGeneratorType::Prims;
    return MazeGeneratorType::AldousBroder;
}

MicromouseControllerType MainWindow::determineMicromouseController() const {
    QString solChoice = mouseAlgoCombo->currentText();
    if (solChoice == "Wall following") return MicromouseControllerType::WallFollower;
    if (solChoice == "Flood Fill") return MicromouseControllerType::FloodFill;
    return MicromouseControllerType::WallFollower;
}

void MainWindow::skipMazeGenerationVisualization() const {
    controller->skipMazeGenerationVisualisation();
    skipMazeGenerationVisualizationButton->setVisible(false);
}

void MainWindow::startMicromouseSimulation() const {
    controller->startMicromouse(determineMicromouseController());
}
