#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

using namespace std;
struct Card
{
    int copies{1};
    int matches{0};
};
int main()
{
    ifstream file("4a.in");
    string line;
    vector<Card> cards;
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
        int point = 0;
        for (auto n : numbers)
        {
            if (winning_numbers.find(n) != winning_numbers.end())
            {
                point++;
            }
        }
        cards.push_back({.copies = 1, .matches = point});
    }
    long total = 0;
    for(int i=0; i<cards.size(); i++)
    {
        for(int j=0; j<cards[i].copies; j++)
        {
            for(int m=0; m<cards[i].matches; m++)
            {
                cards[i+m+1].copies += 1;
            }
        }
        total += cards[i].copies;
        cout << "Card " << i << " = " << cards[i].copies << " " << cards[i].matches << endl;
    }
    cout << total << endl;

    file.close();
    return 0;
}