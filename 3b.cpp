#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool is_digit(char c)
{
    return '0' <= c && c <= '9';
}
bool is_dot(char c)
{
    return c == '.';
}
bool is_symbol(char c)
{
    return !is_digit(c) && !is_dot(c);
}
int extend_numbers(vector<string> &lines, int i, int j, int rows, int cols)
{
    cout << "extend from "<< i << " " << j << endl;
    int number = lines[i][j] - '0';
    lines[i][j] = '.';
    int mul = 10;
    for (int j0 = j - 1; j >= 0 && is_digit(lines[i][j0]); j0--)
    {
        number = mul * (lines[i][j0] - '0') + number;
        mul *= 10;
        lines[i][j0] = '.';
    }
    // cout << number << endl;
    for (int j1 = j + 1; j < cols && is_digit(lines[i][j1]); j1++)
    {
        number = 10*number + (lines[i][j1]-'0');
        lines[i][j1] = '.';
    }
    cout << number << endl;
    return number;
}
int main()
{
    ifstream file("3b.in");
    string line;
    vector<string> lines;
    while (getline(file, line))
    {
        lines.push_back(line);
    }
    int rows = lines.size(), cols = lines[0].size();
    long total = 0;
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (lines[r][c] == '*')
            {
                vector<int> found_numbers;
                for (int i = -1; i <= 1; i++)
                {
                    for (int j = -1; j <= 1; j++)
                    {
                        if (i == 0 && j == 0)
                            continue;
                        if (0 <= r + i && r + i < rows && 0 <= c + j && c + j < cols)
                        {
                            if (is_digit((lines[r + i][c + j])))
                            {
                                found_numbers.push_back(
                                    extend_numbers(lines, r + i, c + j, rows, cols));
                            }
                        }
                    }
                }
                if (found_numbers.size() == 2)
                {
                    total += found_numbers[0] * found_numbers[1];
                }
            }
        }
    }
    cout << total;
    file.close();
    return 0;
}