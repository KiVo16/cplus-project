#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "../Maze/Maze.h"
#include "../Maze/Generator/MazeGenerator.h"
#include "../Micromouse/Micromouse.h"

struct MazeGeneratorVisualizationData {
  const std::unique_ptr<Maze> &maze;
  QPoint current;
  QPoint startPoint;
  QPoint solutionPoint;
  bool isFinished;
  VisitedCoordinates visitedCoordinates;
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

  /**
   * draws maze and micromouse based on provided data
   * @param mazeData data used for maze visualization
   * @param micromouseData data user for micromouse visualization
   */
  virtual void draw(MazeGeneratorVisualizationData *mazeData, MicrmouseVisualizationData *micromouseData) {
  };
};


#endif //VISUALIZER_H
