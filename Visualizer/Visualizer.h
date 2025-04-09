//
// Created by Jakub Kurek on 08/04/2025.
//

#ifndef VISUALIZER_H
#define VISUALIZER_H
#include "../MazeGenerator/MazeGenerator.h"
#include "../MicromouseController/MicromouseController.h"

struct MazeGeneratorVisualizationData {
  Maze maze;
  QPoint current;
  QPoint startPoint;
  QPoint solutionPoint;
  bool isFinished;
};

struct MicrmouseVisualizationData {
  QPoint currentPosition;
  int currentOrientation;
  std::vector<MicrmouseStep> path;
};


class Visualizer {
public:
  Visualizer() = default;

  virtual ~Visualizer() = default;

  virtual void draw(MazeGeneratorVisualizationData *mazeData, MicrmouseVisualizationData *micromouseData);
};


#endif //VISUALIZER_H
