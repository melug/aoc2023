#include <iostream>
#include <fstream>
#include <sstream>
#include <bits/stdc++.h>
#include <limits>

using namespace std;

static long MAX_LONG = numeric_limits<long>::max() / 2;

vector<int> FIVE_OF_KIND = {5},
            FOUR_OF_KIND = {1, 4},
            FULL_HOUSE = {2, 3},
            THREE_OF_KIND = {1, 1, 3},
            TWO_PAIR = {1, 2, 2},
            ONE_PAIR = {1, 1, 1, 2},
            HIGH_CARD = {1, 1, 1, 1, 1};
vector<vector<int>> KINDS = {
    FIVE_OF_KIND,
    FOUR_OF_KIND,
    FULL_HOUSE,
    THREE_OF_KIND,
    TWO_PAIR,
    ONE_PAIR,
    HIGH_CARD};
string CARD_ORDER = "AKQJT98765432";

int findCardOrderIndex(char c)
{
    for (int i = 0; i < CARD_ORDER.size(); i++)
    {
        if (CARD_ORDER[i] == c)
            return i;
    }
    return -1;
}

int findHandTypeIndex(const vector<int> &kind)
{
    for (int i = 0; i < KINDS.size(); i++)
    {
        if (kind == KINDS[i])
            return i;
    }
    return -1;
}

bool isHighCard(const string &card1, const string &card2)
{
    for (int i = 0; i < 5; i++)
    {
        auto index1 = findCardOrderIndex(card1[i]),
             index2 = findCardOrderIndex(card2[i]);
        if (index1 < index2)
            return true;
        if (index1 > index2)
            return false;
    }
    return true;
}

struct Hand
{
    string cards;
    long bid;
    vector<int> handType;
    bool operator<(const Hand &other)
    {
        int myIndex = findHandTypeIndex(handType);
        int otherIndex = findHandTypeIndex(other.handType);
        if (myIndex != otherIndex)
        {
            return myIndex < otherIndex;
        }
        return isHighCard(cards, other.cards);
    }
};

vector<int> handType(const Hand &hand)
{
    unordered_map<char, int> counter;
    vector<int> groupedCounter;
    for (const char c : hand.cards)
    {
        counter[c] += 1;
    }
    for (const auto &[_, count] : counter)
    {
        groupedCounter.push_back(count);
    }
    sort(groupedCounter.begin(), groupedCounter.end());
    return groupedCounter;
};

int main()
{
    ifstream file("7a.in");
    string line, null;
    vector<string> lines;
    vector<long> times, distances;
    vector<Hand> hands;
    while (getline(file, line))
    {
        Hand hand;
        stringstream ss(line);
        ss >> hand.cards;
        ss >> hand.bid;
        hand.handType = handType(hand);
        hands.push_back(hand);
        cout << hand.cards << " ";
        for (auto h : hand.handType)
        {
            cout << h << " ";
        }
        cout << endl;
    }
    sort(hands.begin(), hands.end());
    long total{};
    cout << "Hands:" << endl;
    for (int rank = 0; rank < hands.size(); rank++)
    {
        long points = (hands.size() - rank) * hands[rank].bid;
        cout << hands[rank].cards << " " << hands[rank].bid << " " << points << endl;
        total += points;
    }
    cout << total << endl;
    file.close();
    return 0;
}