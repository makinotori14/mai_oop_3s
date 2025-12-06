#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "Figure.h"
#include "Hexagon.h"
#include "Octagon.h"
#include "Triangle.h"

void removeFigure(std::vector<std::unique_ptr<Figure>>& figures, size_t index) {
    if (index >= figures.size()) {
        std::cout << "wrong index" << std::endl;
        return;
    }
    figures.erase(figures.begin() + index);
    std::cout << "removed" << std::endl;
}

double getTotalArea(const std::vector<std::unique_ptr<Figure>>& figures) {
    double totalArea = 0.0;
    for (const auto& fig : figures) {
        totalArea += static_cast<double>(*fig);
    }
    return totalArea;
}

void printCentersAndAreas(const std::vector<std::unique_ptr<Figure>>& figures) {
    if (figures.empty()) {
        std::cout << "no figures" << std::endl;
        return;
    }

    for (size_t i = 0; i < figures.size(); ++i) {
        auto center = figures[i]->getCenter();
        double area = static_cast<double>(*figures[i]);
        std::cout << "figure " << i << ": "; // индекс 0,1,2,...
        std::cout << "center - (" << center.first << ", " << center.second << "), ";
        std::cout << "area = " << area << std::endl;
    }
}

int main() {
    std::vector<std::unique_ptr<Figure>> figures;

    std::cout << "commands:\n"
              << "  add hexagon   - add hexagon\n"
              << "  add octagon   - add octagon\n"
              << "  add triangle  - add triangle\n"
              << "  print         - print centers and areas\n"
              << "  total         - print total area\n"
              << "  remove i      - remove figure with index i (0-based)\n"
              << "  exit          - quit program\n\n";

    std::string cmd;
    while (true) {
        std::cout << "cmd> ";
        if (!(std::cin >> cmd)) {
            break;
        }

        if (cmd == "add") {
            std::string figureType;
            std::cin >> figureType;

            if (figureType == "hexagon") {
                std::vector<std::pair<double, double>> vertices(6);
                std::cout << "Enter 6 vertices (x y) for hexagon:" << std::endl;
                for (int i = 0; i < 6; ++i) {
                    std::cin >> vertices[i].first >> vertices[i].second;
                }
                figures.push_back(std::make_unique<Hexagon>(vertices));

            } else if (figureType == "octagon") {
                std::vector<std::pair<double, double>> vertices(8);
                std::cout << "Enter 8 vertices (x y) for octagon:" << std::endl;
                for (int i = 0; i < 8; ++i) {
                    std::cin >> vertices[i].first >> vertices[i].second;
                }
                figures.push_back(std::make_unique<Octagon>(vertices));

            } else if (figureType == "triangle") {
                std::vector<std::pair<double, double>> vertices(3);
                std::cout << "Enter 3 vertices (x y) for triangle:" << std::endl;
                for (int i = 0; i < 3; ++i) {
                    std::cin >> vertices[i].first >> vertices[i].second;
                }
                figures.push_back(std::make_unique<Triangle>(vertices));

            } else {
                std::cout << "Unknown figure type: " << figureType << std::endl;
            }

        } else if (cmd == "print") {
            printCentersAndAreas(figures);

        } else if (cmd == "total") {
            std::cout << "total area: " << getTotalArea(figures) << std::endl;

        } else if (cmd == "remove") {
            size_t indexToRemove;
            if (!(std::cin >> indexToRemove)) {
                std::cout << "index expected" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            removeFigure(figures, indexToRemove);

        } else if (cmd == "exit") {
            break;

        } else {
            std::cout << "unknown command, type again" << std::endl;
        }
    }

    return 0;
}
