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
        std::vector<std::vector<char>> triangle(2 * height - 1, std::vector<char>(2 * height - 1, ' '));

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


class Circle : public Figure {
private:
    int rad;
    vector<int> coordinates;

public:
    Circle(int r, int _x, int _y) : rad(r) {
        coordinates.push_back(_x);
        coordinates.push_back(_y);
    }

    std::vector<std::vector<char>> draw() const override {
        std::vector<std::vector<char>> circle(rad * 2 + 1, std::vector<char>(rad * 2 + 1, ' '));
        double aspect_ratio = 1;

        for (int i = -rad; i <= rad; i++) {
            for (int j = -rad; j <= rad; j++) {
                double distance = sqrt(pow(i * aspect_ratio, 2) + pow(j, 2));

                if (distance >= rad - 0.5 && distance <= rad + 0.5) {
                    circle[i + rad][j + rad] = '*';
                }
            }
        }
        return circle;
    }



    vector<int> positon() const override {
        return coordinates;
    }
    int getRadius() {
        return rad;
    }
};

class Square : public Figure {
private:
    int side;
    vector<int> coordinates;

public:
    const string typeName = "Square";
    Square(int s, int _x, int _y) : side(s) {
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
    void setGrid(std::vector<std::vector<char>>& temp_grid) {
        for (int i = 0; i < BOARD_HEIGHT; i++) {
            for (int j = 0; j < BOARD_WIDTH; j++) {
                grid[i][j] = temp_grid[i][j];
            }
        }

    }

};

class CLI {
public:
    Board board;
    vector<shared_ptr<Figure>> Figures;

    void start() {
        while (1) {
            auto input = user_input();
            if (input.empty()) continue;

            string command = input[0];

            if (command == "add") {
                add(input);
            }
            else if (command == "list") {
                list();
            }
            else if (command == "draw") {
                draw();
            }

            else if (command == "undo") {
                if (!Figures.empty()) {
                    Figures.pop_back();
                    board.reset();
                }
            }

            else if (command == "clear") {
                clear();
            }

            else if (command == "save") {
                save();
            }

            else if (command == "load") {
                load();
            }

            else if (command == "exit") {
                break;
            }
            else {
                cout << "Unknown command" << endl;
            }
        }
    }




    void save() {

        auto grid = board.getGrid();
        string input;

        cout << "Enter path to file: ";
        getline(cin, input);
        cout << endl;

        std::ofstream output_file(input);

        for (const auto& row : grid) {
            for (char c : row) {
                output_file << c;
            }
            output_file << '\n';
        }
    }

    void list() {
        int ID = 0;
        for (auto& fig : Figures) {
            Circle* circle = dynamic_cast<Circle*>(fig.get());
            Square* square = dynamic_cast<Square*>(fig.get());
            Triangle* triangle = dynamic_cast<Triangle*>(fig.get());
            Rectangle* rectangle = dynamic_cast<Rectangle*>(fig.get());
            auto coordinates = fig->positon();

            if (circle != nullptr) {
                cout << "ID " << ID << " Circle radius " << circle->getRadius() << "coordanates " << coordinates[0] << " " << coordinates[1] << endl;

            }

            if (square != nullptr) {
                cout << "ID " << ID << " Square side " << square->getSide() << "coordanates " << coordinates[0] << " " << coordinates[1] << endl;

            }
            if (triangle != nullptr) {
                cout << "ID " << ID << " Triangle height " << triangle->getHeigh() << "coordanates " << coordinates[0] << " " << coordinates[1] << endl;

            }
            if (rectangle != nullptr) {
                cout << "ID " << ID << " Rectangle side " << triangle->getHeigh() << "coordanates " << coordinates[0] << " " << coordinates[1] << endl;

            }


            ID++;

        }
    }

    void load() {
        string input;

        cout << "Enter path to file: ";
        getline(cin, input);
        cout << endl;


        ifstream input_stream(input);
        if (!input_stream) {
            cerr << "Error opening file: " << input << endl;
            return;
        }

        std::vector<std::vector<char>> grid;
        string line;
        while (getline(input_stream, line)) {
            vector<char> row;


            for (char c : line) {
                if (c == ' ' || c == '*') {
                    row.push_back(c);
                }
            }

            grid.push_back(row);
        }

        input_stream.close();

        clear();

        board.setGrid(grid);

    }


    void clear() {
        while (!Figures.empty()) {
            Figures.pop_back();
        }
        board.reset();
    }

    void draw() {
        for (auto& fig : Figures) {
            auto cords = fig->positon();
            board.placeShape(*fig, cords[0], cords[1]);
        }
        board.print();
    }
    void add(vector<string> input) {

        if (input[1] == "circle") {
            int rad = stoi(input[2]);
            int x = stoi(input[3]);
            int y = stoi(input[4]);

            Figures.emplace_back(make_shared<Circle>(rad, x, y));
        }
        else if (input[1] == "triangle") {
            int height = stoi(input[2]);
            int x = stoi(input[3]);
            int y = stoi(input[4]);

            Figures.emplace_back(make_shared<Triangle>(height, x, y));
        }
        else if (input[1] == "square") {
            int side = stoi(input[2]);
            int x = stoi(input[3]);
            int y = stoi(input[4]);

            Figures.emplace_back(make_shared<Square>(side, x, y));
        }

        else if (input[1] == "rectangle") {
            int side = stoi(input[2]);
            int x = stoi(input[3]);
            int y = stoi(input[4]);

            Figures.emplace_back(make_shared<Rectangle>(side, x, y));
        }
    }

    vector<string> user_input() {
        string line;
        cout << "Input: ";
        getline(cin, line);
        stringstream ss(line);
        string token;
        vector<string> row;
        char delimiter = ' ';

        while (getline(ss, token, delimiter)) {
            row.push_back(token);
        }

        return row;
    }
};

int main() {
    CLI cli;
    cli.start();
    return 0;
}
