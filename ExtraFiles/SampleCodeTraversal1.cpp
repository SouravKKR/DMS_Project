#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdlib>
#include <ctime>
#include<chrono>
using namespace std;

void f(char currNode, map<char, vector<char>>& adjacencyList, char destinationNode, vector<char> currPath, vector<vector<char>>& allPaths, char prev)
{
    currPath.emplace_back(currNode);
    if (currNode == destinationNode)
    {
        allPaths.emplace_back(currPath);
        return;
    }
    if (currPath.size() > 20) {
        return;
    }

    for (char nbr : adjacencyList[currNode])
    {
        if (nbr == prev) continue;
        f(nbr, adjacencyList, destinationNode, currPath, allPaths, currNode);
    }
    return;
}

int main()
{
    auto StartTime = std::chrono::high_resolution_clock::now();

    std::map<char, std::vector<char>> adjacencyList;

    adjacencyList.insert({ 'A', {'F', 'D', 'B'} });
    adjacencyList.insert({ 'B', {'A', 'C', 'E'} });
    adjacencyList.insert({ 'C', {'B', 'D'} });
    adjacencyList.insert({ 'D', {'A', 'C', 'E'} });
    adjacencyList.insert({ 'E', {'B', 'D', 'F'} });
    adjacencyList.insert({ 'F', {'A', 'E'} });

    vector<vector<char>> allPaths;
    allPaths.reserve(2000);
   
    
    std::vector<char> Curr;
    f('A', adjacencyList, 'F', {}, allPaths, '\0');

    for (auto path : allPaths)
    {
        for (auto node : path)
        {
            cout << node << "->";
        }
        cout << "\n";
    }

    auto vectorLengthComparator = [](const std::vector<char>& a, const std::vector<char>& b)
        {
            return a.size() < b.size();
        };

   
    std::sort(allPaths.begin(), allPaths.end(), vectorLengthComparator);

    auto EndTime = std::chrono::high_resolution_clock::now();

    auto DurationInMs = std::chrono::duration_cast<std::chrono::microseconds>(EndTime - StartTime);
    double Duration= DurationInMs.count();

    for (auto node : allPaths[0])
    {
        cout << node << "->";
    }

    std::cout << " : " << Duration<<std::endl;
}
