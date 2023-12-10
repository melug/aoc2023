#include <iostream>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <limits>

using namespace std;

static long MAX_LONG = numeric_limits<long>::max() / 2;

long extraPolate(const vector<long> &numbers)
{
    int zeroCount = 0;
    for (auto n : numbers)
        if (n == 0)
            zeroCount += 1;
    if (zeroCount == numbers.size())
    {
        return 0;
    }
    vector<long> newNumbers;
    for (int i = 1; i < numbers.size(); i++)
    {
        newNumbers.push_back(numbers[i] - numbers[i - 1]);
    }
    auto value = extraPolate(newNumbers);
    return numbers.back()+value;
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
        vector<long> numbers;
        while (!ss.eof())
        {
            long d;
            ss >> d;
            numbers.push_back(d);
        }
        total += extraPolate(numbers);
    }
    cout << total << endl;
    file.close();
    return 0;
}