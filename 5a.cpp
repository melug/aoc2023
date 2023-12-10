#include <iostream>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;

struct ThreeNumbers
{
    long destination_range_start;
    long source_range_start;
    long range_length;
};

using CategoryMap = unordered_map<string, vector<ThreeNumbers>>;

int main()
{
    ifstream file("5a.in");
    string line, null;
    vector<string> lines;
    vector<long> seeds;
    CategoryMap categoryMap;
    while (getline(file, line))
    {
        lines.push_back(line);
    }

    {
        stringstream ss(lines[0]);
        ss >> null;
        while (!ss.eof())
        {
            long d;
            ss >> d;
            seeds.push_back(d);
        }
    }
    for (int i = 2; i < lines.size(); i++)
    {
        // get header
        stringstream ss(lines[i]);
        string mapName;
        ss >> mapName;
        i += 1;
        for (; i < lines.size() && !lines[i].empty(); i++)
        {
            stringstream ls(lines[i]);
            ThreeNumbers threeNumbers;
            ls >> threeNumbers.destination_range_start;
            ls >> threeNumbers.source_range_start;
            ls >> threeNumbers.range_length;
            categoryMap[mapName].push_back(threeNumbers);
        }
    }
    for (const auto &[key, value] : categoryMap)
    {
        cout << key << endl;
        for (const auto &v : value)
        {
            cout << v.destination_range_start << " " << v.source_range_start << " " << v.range_length << endl;
        }
    }
    vector<string> mapOrders{
        "seed-to-soil",
        "soil-to-fertilizer",
        "fertilizer-to-water",
        "water-to-light",
        "light-to-temperature",
        "temperature-to-humidity",
        "humidity-to-location"};
    long lowestLocation = 1000000000000;
    for (const auto &seed : seeds)
    {
        long number = seed;
        cout << "Seed " << seed << endl;
        for (const auto &mapOrder : mapOrders)
        {
            bool hasFoundMatching = false;
            for(const auto& threeNumber: categoryMap[mapOrder])
            {
                if (threeNumber.source_range_start <= number && number < threeNumber.source_range_start + threeNumber.range_length)
                {
                    number = threeNumber.destination_range_start + (number-threeNumber.source_range_start);
                    hasFoundMatching = true;
                    break;
                }
            }
            // cout << " Mapped to " << number << endl;
        }
        lowestLocation = min(lowestLocation, number);
    }
    cout << lowestLocation << endl;
    file.close();
    return 0;
}