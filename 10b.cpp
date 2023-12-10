#include <iostream>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <limits>
#include <functional>

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

vector<Position> findFarthestPoint(const Karta &karta, Position start)
{
    int rows = karta.size(), columns = karta[0].size();
    vector<Position> path{start};
    auto current = start,
         previousPosition = Position{};
    for (auto nextPosition = findNextPosition(karta, current, previousPosition);
         nextPosition != start;
         nextPosition = findNextPosition(karta, nextPosition, previousPosition))
    {
        // cout << "Next: " << nextPosition.row << " " << nextPosition.column << endl;
        previousPosition = path.back();
        path.push_back(nextPosition);
    }
    return path;
}

struct PositionCompare
{
    bool operator()(const Position &a, const Position &b) const
    {
        if (a.row != b.row)
            return a.row < b.row;
        return a.column < b.column;
    }
};

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
    vector<string> bigKarta(3 * rows, string(3 * columns, '.'));
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
    auto path = findFarthestPoint(karta, {startRow, startColumn});
    set<Position, PositionCompare> takenPositions(path.begin(), path.end());
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (takenPositions.count({i, j}) == 0)
            {
                lines[i][j] = '.';
                karta[i][j] = Cell();
            }
        }
    }
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            bool isEmpty = !karta[i][j].north && !karta[i][j].south && !karta[i][j].east && !karta[i][j].west;
            if (!isEmpty)
            {
                bigKarta[3 * i + 1][3 * j + 1] = '#';
            }
            if (karta[i][j].north)
            {
                bigKarta[3 * i][3 * j + 1] = '#';
            }
            if (karta[i][j].south)
            {
                bigKarta[3 * i + 2][3 * j + 1] = '#';
            }
            if (karta[i][j].east)
            {
                bigKarta[3 * i + 1][3 * j + 2] = '#';
            }
            if (karta[i][j].west)
            {
                bigKarta[3 * i + 1][3 * j] = '#';
            }
        }
    }
    queue<Position> positions;
    positions.push({0, 0});
    set<pair<int, int>> visited{{0, 0}};
    int bigKartaRows = bigKarta.size(), bigKartaColumns = bigKarta[0].size();
    vector<pair<int, int>> neighborDistance = {
        {-1, 0},
        {+1, 0},
        {0, -1},
        {0, +1},
    };

    while (!positions.empty())
    {
        Position p = positions.front();
        positions.pop();
        if (bigKarta[p.row][p.column] == '.')
        {
            bigKarta[p.row][p.column] = 'X';
            for (auto dist : neighborDistance)
            {
                int newRow = p.row + dist.first, newColumn = p.column + dist.second;
                if (isValidPosition(newRow, newColumn, bigKartaRows, bigKartaColumns) && bigKarta[newRow][newColumn] == '.' && visited.count({newRow, newColumn}) == 0)
                {
                    visited.insert({newRow, newColumn});
                    positions.push({newRow, newColumn});
                }
            }
        }
    }
    long answer = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (bigKarta[3 * i + 1][3 * j + 1] == '.')
            {
                answer += 1;
                lines[i][j] = 'I';
            }
        }
    }
    for (auto line : lines)
    {
        cout << line << endl;
    }
    cout << answer << endl;
    file.close();
    return 0;
}