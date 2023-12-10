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

void doAnalysis(const string &start, const string &instruction, const Network &network)
{
    map<tuple<string, int>, int> nodeAndIndextoCounter;
    string current = start;
    int step = 0, instructionIndex = 0;
    int zDistance = -1;
    cout << "From: " << start << endl;
    while (nodeAndIndextoCounter[make_tuple(current, instructionIndex)] != 3)
    {
        auto nodeAndIndex = make_tuple(current, instructionIndex);
        nodeAndIndextoCounter[nodeAndIndex] += 1;
        if (instruction[instructionIndex] == 'L')
        {
            current = network.at(current).L;
        }
        else
        {
            current = network.at(current).R;
        }
        step += 1;
        instructionIndex = (instructionIndex + 1) % instruction.size();
        if (current[2] == 'Z')
        {
            cout << " " << current << " " << instructionIndex << " " << step << endl;
        }
    }
    // int oneCount{}, twoCount{};
    // for (const auto &[_, count] : hitCounter)
    // {
    //     if (count == 1)
    //         oneCount += 1;
    //     if (count == 2)
    //         twoCount += 1;
    // }
    // cout << "to loop: " << oneCount << endl;
    // cout << "inside loop: " << twoCount << endl;
    // cout << endl;
}

long gcd(long a, long b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

long lcd(long a, long b)
{
    return a * b / gcd(a, b);
}

int main()
{
    ifstream file("8b.in");
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
    vector<string> currents;
    for (const auto &[key, _] : network)
    {
        if (key[2] == 'A')
        {
            currents.push_back(key);
        }
    }
    cout << "Size:" << currents.size() << endl;
    for (int i = 0; i < currents.size(); i++)
    {
        doAnalysis(currents[i], instruction, network);
    }
    vector<long> cycles = {
        20569,
        18727,
        22411,
        16271,
        14429,
        24253
    };
    long temp = cycles[0];
    for(int i=1; i<cycles.size(); i++)
    {
        temp = lcd(temp, cycles[i]);
    }
    cout << "LCD:"<< temp << endl;
    file.close();
    return 0;
}