#include <iostream>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <limits>

using namespace std;

static long MAX_LONG = numeric_limits<long>::max() / 2;

void extraPolate(vector<long> &numbers)
{
    int zeroCount = 0;
    for (int i = 1; i < numbers.size(); i++)
        if (numbers[i] == 0)
            zeroCount += 1;
    if (zeroCount == numbers.size() - 1)
    {
        numbers[0] = 0;
        for (auto n : numbers)
            cout << n << " ";
        cout << endl;
        return;
    }
    vector<long> newNumbers{-1};
    for (int i = 2; i < numbers.size(); i++)
    {
        newNumbers.push_back(numbers[i] - numbers[i - 1]);
    }
    extraPolate(newNumbers);
    // numbers[1]-numbers[0] = newNumbers[0]
    numbers[0] = numbers[1] - newNumbers[0];
    for (auto n : numbers)
        cout << n << " ";
    cout << endl;
}

int main()
{
    ifstream file("9a.in");
    string line, null, instruction;
    vector<string> lines;
    long total{};
    while (getline(file, line))
    {
        stringstream ss(line);
        vector<long> numbers{-1};
        while (!ss.eof())
        {
            long d;
            ss >> d;
            numbers.push_back(d);
        }
        extraPolate(numbers);
        for(int i=1; i<numbers.size(); i++)
            cout << numbers[i] << " ";
        cout << endl << numbers[0] << endl;
        total += numbers[0];
    }
    cout << total << endl;
    file.close();
    return 0;
}