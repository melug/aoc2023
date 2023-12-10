#include <iostream>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <limits>

using namespace std;

static long MAX_LONG = numeric_limits<long>::max() / 2;

struct Node
{
    string L;
    string R;
};

using Network = unordered_map<string, Node>;

int main()
{
    ifstream file("8a.in");
    string line, null, instruction;
    Network network;
    vector<string> lines;
    getline(file, instruction);
    getline(file, null);
    while (getline(file, line))
    {
        string key = line.substr(0, 3);
        string left = line.substr(7, 3);
        string right = line.substr(12, 3);
        network[key] = Node{left, right};
    }
    int step = 0;
    string current = "AAA";
    while (current != "ZZZ")
    {
        if (instruction[step%instruction.size()] == 'L')
        {
            current = network[current].L;
        }
        else
        {
            current = network[current].R;
        }
        cout << current << endl;
        step += 1;
    }
    cout << step << endl;
    file.close();
    return 0;
}