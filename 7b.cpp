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
string CARD_ORDER = "AKQT98765432J";

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
    string improvedCards;
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

string replace(string s, char c, char p)
{
    string ans;
    for (char l : s)
    {
        if (l == c)
            ans.push_back(p);
        else
            ans.push_back(l);
    }
    return ans;
}

vector<int> handType(const string &cards)
{
    unordered_map<char, int> counter;
    vector<int> groupedCounter;
    for (const char c : cards)
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

void makeStronger(Hand &hand)
{
    // replace J by all possible and return highest;
    string cards = hand.cards;
    if (cards.find('J') == string::npos)
        return;
    vector<Hand> candidates;
    for (int i = 0; i < CARD_ORDER.size() - 1; i++)
    {
        char c = CARD_ORDER[i];
        Hand candidate(hand);
        candidate.cards = replace(hand.cards, 'J', c);
        candidate.improvedCards = candidate.cards;
        candidate.handType = handType(candidate.cards);
        candidates.push_back(candidate);
    }
    sort(
        candidates.begin(), candidates.end());
    for (auto candidate : candidates)
        cout << " candidates " << candidate.cards << endl;
    hand.improvedCards = candidates[0].cards;
    hand.handType = candidates[0].handType;
}

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
        hand.handType = handType(hand.cards);
        makeStronger(hand);
        cout << hand.cards << " " << hand.improvedCards << " ";
        for (auto h : hand.handType)
        {
            cout << h << " ";
        }
        cout << endl;
        hands.push_back(hand);
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