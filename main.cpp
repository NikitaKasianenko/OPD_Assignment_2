#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>


using namespace std;

const int BOARD_WIDTH = 80;
const int BOARD_HEIGHT = 25;

class Figure {
public:
    virtual std::vector<std::vector<char>> draw() const = 0;
    virtual vector<int> positon() const = 0;
    virtual ~Figure() = default;
};

class Triangle : public Figure {
private:
    int height;
    vector<int> coordinates;

public:
    Triangle(int h, int _x, int _y) : height(h) {
        coordinates.push_back(_x);
        coordinates.push_back(_y);
    }

    std::vector<std::vector<char>> draw() const override {
        std::vector<std::vector<char>> triangle(height, std::vector<char>(2 * height - 1, ' '));
        for (int i = 0; i < height; ++i) {
            int leftMost = height - 1 - i;
            int rightMost = height - 1 + i;
            triangle[i][leftMost] = '*';
            triangle[i][rightMost] = '*';
        }

        for (int j = 0; j < 2 * height - 1; ++j) {
            triangle[height - 1][j] = '*';
        }
        return triangle;
    }

    

    vector<int> positon() const override {
        return coordinates;
    }
    int getHeigh() {
        return height;
    }
};

class Rectangle : public Figure {
private:
    int height;
    vector<int> coordinates;

public:
    Rectangle(int h, int _x, int _y) : height(h) {
        coordinates.push_back(_x);
        coordinates.push_back(_y);
    }

    std::vector<std::vector<char>> draw() const override {
        std::vector<std::vector<char>> triangle(2*height - 1, std::vector<char>(2 * height - 1, ' '));

        for (int i = 0; i < height; ++i) {
            int leftMost = height - 1 - i;
            int rightMost = height - 1 + i;
            triangle[i][leftMost] = '*';
            triangle[i][rightMost] = '*';
        }

        for (int i = height; i < 2 * height - 1; ++i) {
            int leftMost = i - height + 1;
            int rightMost = 3 * height - i - 3;
            triangle[i][leftMost] = '*';
            triangle[i][rightMost] = '*';
        }

        
        return triangle;
    }

   

    vector<int> positon() const override {
        return coordinates;
    }
    int getHeigh() {
        return height;
    }
};


class Square : public Figure {
private:
    int side;
    vector<int> coordinates;

public:
    const string typeName = "Square";
    Square(int s,int _x, int _y) : side(s) {
        coordinates.push_back(_x);
        coordinates.push_back(_y);
    }

    std::vector<std::vector<char>> draw() const override {
        std::vector<std::vector<char>> square(side, std::vector<char>(side, ' '));
        for (int i = 0; i < side; i++) {
            if (i == 0 || i == side - 1) {
                for (int j = 0; j < side; j++) {
                    square[i][j] = '*';
                }
            }
            else {
                for (int k = 0; k < side; k++) {
                    if (k == 0 || k == side - 1) {
                        square[i][k] = '*';
                    }
                    else {
                        square[i][k] = ' ';
                    }
                }
            }
        }
        return square;
    }

    

    vector<int> positon() const override {
        return coordinates;
    }
    
    int getSide() {
        return side;
    }
};

struct Board {
    std::vector<std::vector<char>> grid;

    Board() : grid(BOARD_HEIGHT, std::vector<char>(BOARD_WIDTH, ' ')) {}

    void print() {
        for (auto& row : grid) {
            cout << "|";
            for (char c : row) {
                std::cout << c;
            }
            cout << "|";
            std::cout << "\n";
        }
    }

    void placeShape(const Figure& shape, int x, int y) {
        std::vector<std::vector<char>> shapeGrid = shape.draw();
        for (int i = 0; i < shapeGrid.size(); ++i) {
            for (int j = 0; j < shapeGrid[i].size(); ++j) {
                if (shapeGrid[i][j] != ' ' && x + i < BOARD_HEIGHT && y + j < BOARD_WIDTH) {
                    grid[x + i][y + j] = shapeGrid[i][j];
                }
            }
        }
    }
    void reset() {
        for (int i = 0; i < BOARD_HEIGHT; i++) {
            for (int j = 0; j < BOARD_WIDTH; j++) {
                grid[i][j] = ' ';
            }
        }

    }
    std::vector<std::vector<char>> getGrid() {
        return grid;
    }
    void setGrid(std::vector<std::vector<char>>&temp_grid) {
        for (int i = 0; i < BOARD_HEIGHT; i++) {
            for (int j = 0; j < BOARD_WIDTH; j++) {
                grid[i][j] = temp_grid[i][j];
            }
        }

    }
    
};

