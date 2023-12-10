#include <iostream>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <limits>

using namespace std;

static long MAX_LONG = numeric_limits<long>::max()/2;

struct ThreeNumbers
{
    long destination_range_start;
    long source_range_start;
    long range_length;
    bool operator<(const ThreeNumbers &other) const
    {
        return source_range_start < other.source_range_start;
    }
};

using CategoryMap = unordered_map<string, vector<ThreeNumbers>>;

long convertToDest(long number, ThreeNumbers &threeNumber)
{
    return threeNumber.destination_range_start + (number - threeNumber.source_range_start);
}

long findMinimumLocation(long start, long length, int mapIndex, CategoryMap &categoryMaps, vector<string> &categoryNames)
{
    if (mapIndex == categoryMaps.size())
        return start;
    string categoryName = categoryNames[mapIndex];
    vector<ThreeNumbers> &categoryMap = categoryMaps[categoryName];

    long minimumLocation = MAX_LONG;
    for (int i = 0; i < categoryMap.size(); i++)
    {
        auto &threeNumbers = categoryMap[i];
        auto newStartSource = max(start, threeNumbers.source_range_start);
        auto newDestSource = min(start + length - 1, threeNumbers.source_range_start + threeNumbers.range_length - 1);
        // do they intersect?
        if (newStartSource < newDestSource)
        {
            auto newLength = newDestSource - newStartSource + 1;
            auto newDestStart = convertToDest(newStartSource, threeNumbers);
            minimumLocation = min(minimumLocation,
                                  findMinimumLocation(newDestStart, newLength, mapIndex + 1, categoryMaps, categoryNames));
        }
    }
    // cout << categoryName << " start = " << start << " length = " << length << " minimumLocation = " << minimumLocation << endl;
    return minimumLocation;
}

struct Seed
{
    long start;
    long range;
};

int main()
{
    ifstream file("5a.in");
    string line, null;
    vector<string> lines;
    vector<Seed> seeds;
    CategoryMap categoryMaps;
    while (getline(file, line))
    {
        lines.push_back(line);
    }

    {
        stringstream ss(lines[0]);
        ss >> null;
        while (!ss.eof())
        {
            Seed seed;
            ss >> seed.start;
            ss >> seed.range;
            seeds.push_back(seed);
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
            categoryMaps[mapName].push_back(threeNumbers);
        }
        sort(
            categoryMaps[mapName].begin(),
            categoryMaps[mapName].end());
        vector<ThreeNumbers> updatedMap;

        for (int i = 0; i < categoryMaps[mapName].size(); i++)
        {
            auto &categoryMap = categoryMaps[mapName][i];
            if (i == 0)
            {
                if (categoryMap.source_range_start != 0)
                {
                    updatedMap.push_back({0, 0, categoryMap.source_range_start});
                }
            }
            else
            {
                auto &previousCategoryMap = categoryMaps[mapName][i - 1];
                if (previousCategoryMap.source_range_start + previousCategoryMap.range_length != categoryMap.source_range_start)
                {
                    updatedMap.push_back({previousCategoryMap.source_range_start + previousCategoryMap.range_length,
                                          previousCategoryMap.source_range_start + previousCategoryMap.range_length,
                                          categoryMap.source_range_start - (previousCategoryMap.source_range_start + previousCategoryMap.range_length)});
                }
            }
            updatedMap.push_back(categoryMap);

            if (i == categoryMaps[mapName].size() - 1)
            {
                updatedMap.push_back({categoryMap.source_range_start + categoryMap.range_length,
                                      categoryMap.source_range_start + categoryMap.range_length,
                                      MAX_LONG});
            }
        }
        categoryMaps[mapName] = updatedMap;
        // for (auto threeNumbers : updatedMap)
        // {
        //     cout << threeNumbers.destination_range_start << " " << threeNumbers.source_range_start << " " << threeNumbers.range_length << endl;
        // }
        // cout << endl;
    }
    vector<string> categoryNames{
        "seed-to-soil",
        "soil-to-fertilizer",
        "fertilizer-to-water",
        "water-to-light",
        "light-to-temperature",
        "temperature-to-humidity",
        "humidity-to-location"};
    long lowestLocation = MAX_LONG;
    for (const auto &seed : seeds)
    {
        lowestLocation = min(lowestLocation, findMinimumLocation(seed.start, seed.range, 0, categoryMaps, categoryNames));
    }
    cout << lowestLocation << endl;
    file.close();
    return 0;
}