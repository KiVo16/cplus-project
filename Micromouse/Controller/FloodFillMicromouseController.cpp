#include "FloodFillMicromouseController.h"
#include <cmath>

const int INF = 100000;

void FloodFillMicromouseController::step() {
    if (finished) return;
    std::vector<std::vector<int> > cost(mazeSize, std::vector<int>(mazeSize, INF));

    auto isValid = [this](const int r, const int c) {
        return r >= 0 && r < mazeSize && c >= 0 && c < mazeSize;
    };

    int goalRow = goal.x();
    int goalCol = goal.y();
    cost[goalRow][goalCol] = 0;

    std::queue<QPoint> q;
    q.push(QPoint(goalRow, goalCol));

    const int dx[4] = {-1, 0, 1, 0};
    const int dy[4] = {0, 1, 0, -1};

    while (!q.empty()) {
        QPoint cur = q.front();
        q.pop();
        int curCost = cost[cur.x()][cur.y()];
        for (int d = 0; d < 4; ++d) {
            int nx = cur.x() + dx[d];
            int ny = cur.y() + dy[d];
            if (
                isValid(nx, ny) &&
                micromouse->getSensor()->canMove(cur.x(), cur.y(), nx, ny) &&
                curCost + 1 < cost[nx][ny]
            ) {
                cost[nx][ny] = curCost + 1;
                q.push(QPoint(nx, ny));
            }
        }
    }

    QPoint pos = micromouse->getCurrentPosition();
    int bestCost = INF;
    int bestDir = -1;
    for (int d = 0; d < 4; ++d) {
        int nx = pos.x() + dx[d];
        int ny = pos.y() + dy[d];
        if (
            isValid(nx, ny) &&
            micromouse->getSensor()->canMove(pos.x(), pos.y(), nx, ny)
        ) {
            if (cost[nx][ny] < bestCost) {
                bestCost = cost[nx][ny];
                bestDir = d;
            }
        }
    }

    if (bestDir != -1) {
        int newX = pos.x() + dx[bestDir];
        int newY = pos.y() + dy[bestDir];

        micromouse->rotate(bestDir);
        micromouse->move(newX, newY);

        if (newX == goalRow && newY == goalCol) finished = true;
    } else {
        micromouse->rotate((micromouse->getCurrentOrientation() + 1) % 4);
    }
}
