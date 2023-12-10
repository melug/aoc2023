#include <iostream>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <limits>

using namespace std;

static long MAX_LONG = numeric_limits<long>::max() / 2;

int main()
{
    ifstream file("6a.in");
    string line, null;
    vector<string> lines;
    vector<long> times, distances;
    while (getline(file, line))
    {
        lines.push_back(line);
    }
    file.close();
    stringstream ss(lines[0]);
    ss >> null;
    while (!ss.eof())
    {
        long time;
        ss >> time;
        times.push_back(time);
    }
    stringstream ss2(lines[1]);
    ss2 >> null;
    while (!ss2.eof())
    {
        long distance;
        ss2 >> distance;
        distances.push_back(distance);
    }
    long total{1};
    for (long i = 0; i < times.size(); i++)
    {
        long ways = 0;
        for (long time_start = 0; time_start <= times[i]; time_start++)
        {
            if (time_start * (times[i] - time_start) > distances[i])
            {
                ways += 1;
            }
        }
        total *= ways;
    }
    cout << total << endl;
    return 0;
}