#include <iostream>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <limits>

using namespace std;

static long MAX_LONG = numeric_limits<long>::max() / 2;

struct Position
{
    int row{-1};
    int column{-1};
    bool operator==(const Position &other)
    {
        return row == other.row && column == other.column;
    }
    bool operator!=(const Position &other)
    {
        return !(*this == other);
    }
};

bool isValidPosition(int row, int column, int rows, int columns)
{
    return 0 <= row && row < rows && 0 <= column && column < columns;
}

struct Cell
{
    bool north{}, east{}, south{}, west{};
};

using Karta = vector<vector<Cell>>;

Position findNextPosition(const Karta &karta, Position current, Position previous)
{
    Position nextPosition;
    int rows = karta.size(), columns = karta[0].size();
    if (isValidPosition(current.row - 1, current.column, rows, columns) &&
        karta[current.row - 1][current.column].south &&
        karta[current.row][current.column].north &&
        Position{current.row - 1, current.column} != previous)
    {
        nextPosition.row = current.row - 1;
        nextPosition.column = current.column;
    }
    if (isValidPosition(current.row + 1, current.column, rows, columns) &&
        karta[current.row + 1][current.column].north &&
        karta[current.row][current.column].south &&
        Position{current.row + 1, current.column} != previous)
    {
        nextPosition.row = current.row + 1;
        nextPosition.column = current.column;
    }
    if (isValidPosition(current.row, current.column - 1, rows, columns) &&
        karta[current.row][current.column - 1].east &&
        karta[current.row][current.column].west &&

        Position{current.row, current.column - 1} != previous)
    {
        nextPosition.row = current.row;
        nextPosition.column = current.column - 1;
    }
    if (isValidPosition(current.row, current.column + 1, rows, columns) &&
        karta[current.row][current.column + 1].west &&
        karta[current.row][current.column].east &&
        Position{current.row, current.column + 1} != previous)
    {
        nextPosition.row = current.row;
        nextPosition.column = current.column + 1;
    }
    return nextPosition;
}

long findFarthestPoint(const Karta &karta, Position start)
{
    int rows = karta.size(), columns = karta[0].size();
    vector<Position> path{start};
    auto current = start,
         previousPosition = Position{};
    for (auto nextPosition = findNextPosition(karta, current, previousPosition);
         nextPosition != start;
         nextPosition = findNextPosition(karta, nextPosition, previousPosition))
    {
        cout << "Next: " << nextPosition.row << " " << nextPosition.column << endl;
        previousPosition = path.back();
        path.push_back(nextPosition);
    }
    long answer = path.size();
    for (auto p : path)
    {
        cout << p.row << " - " << p.column << endl;
    }
    return answer;
}

int main()
{
    ifstream file("10a.in");
    string line, null, instruction;
    vector<string> lines;
    while (getline(file, line))
    {
        lines.push_back(line);
    }
    Karta karta(lines.size(), vector<Cell>(lines[0].size()));
    int rows = karta.size(), columns = karta[0].size();
    int startRow, startColumn;
    for (int i = 0; i < lines.size(); i++)
    {
        for (int j = 0; j < lines[i].size(); j++)
        {
            if (lines[i][j] == 'S')
            {
                startRow = i;
                startColumn = j;
            }
            switch (lines[i][j])
            {
            case '|':
            {
                karta[i][j].north = true;
                karta[i][j].south = true;
                break;
            }
            case '-':
            {
                karta[i][j].east = true;
                karta[i][j].west = true;
                break;
            }
            case 'L':
            {
                karta[i][j].north = true;
                karta[i][j].east = true;
                break;
            }
            case 'J':
            {
                karta[i][j].north = true;
                karta[i][j].west = true;
                break;
            }
            case '7':
            {
                karta[i][j].west = true;
                karta[i][j].south = true;
                break;
            }
            case 'F':
            {
                karta[i][j].east = true;
                karta[i][j].south = true;
                break;
            }
            }
        }
    }
    // Fix start position
    if (isValidPosition(startRow + 1, startColumn, rows, columns) && karta[startRow + 1][startColumn].north)
    {
        karta[startRow][startColumn].south = true;
    }
    if (isValidPosition(startRow - 1, startColumn, rows, columns) && karta[startRow - 1][startColumn].south)
    {
        karta[startRow][startColumn].north = true;
    }
    if (isValidPosition(startRow, startColumn + 1, rows, columns) && karta[startRow][startColumn + 1].west)
    {
        karta[startRow][startColumn].east = true;
    }
    if (isValidPosition(startRow, startColumn - 1, rows, columns) && karta[startRow][startColumn - 1].east)
    {
        karta[startRow][startColumn].west = true;
    }
    cout << findFarthestPoint(karta, {startRow, startColumn}) << endl;
    file.close();
    return 0;
}