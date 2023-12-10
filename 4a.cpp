#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;
struct Card
{
    int count{};
    int win_count{};
};
int main()
{
    ifstream file("4a.in");
    string line;
    long total = 0;
    while (getline(file, line))
    {
        stringstream ss(line);
        string s;
        ss >> s; // card
        ss >> s; // number:
        set<int> winning_numbers;
        do
        {
            ss >> s;
            if (s[0] != '|')
            {
                winning_numbers.insert(stoi(s));
            }
            else
            {
                break;
            }
        } while (true);
        set<int> numbers;
        do
        {
            ss >> s;
            if (s[0] != '|')
            {
                numbers.insert(stoi(s));
            }
            else
            {
                break;
            }
        } while (!ss.eof());
        long point_to_earn = 1, point = 0;
        for (auto n : numbers)
        {
            if (winning_numbers.find(n) != winning_numbers.end())
            {
                point = point_to_earn;
                point_to_earn *= 2;
            }
        }
        total += point;
    }
    cout << total << endl;
    file.close();
    return 0;
}