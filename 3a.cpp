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
int main()
{
    ifstream file("3a.in");
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
        long current_number = 0;
        bool is_adjacent = false;
        for (int c = 0; c < cols; c++)
        {

            if (is_digit(lines[r][c]))
            {
                current_number = 10 * current_number + (lines[r][c] - '0');
                for (int i = -1; i <= 1; i++)
                {
                    for (int j = -1; j <= 1; j++)
                    {
                        if (i == 0 && j == 0)
                            continue;
                        if (0 <= r + i && r + i < rows && 0 <= c + j && c + j < cols)
                        {
                            if (is_symbol(lines[r + i][c + j]))
                            {
                                is_adjacent = true;
                            }
                        }
                    }
                }
            }

            if (!is_digit(lines[r][c]) || c == cols - 1)
            {
                if (is_adjacent)
                {
                    if (current_number != 0)
                        cout << current_number << endl;
                    total += current_number;
                }
                current_number = 0;
                is_adjacent = false;
            }
        }
    }
    cout << total;
    file.close();
    return 0;
}