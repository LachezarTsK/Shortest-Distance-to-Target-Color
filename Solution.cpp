
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
    
    inline static const int NOT_FOUND = -1;

public:
    vector<int> shortestDistanceColor(vector<int>& colors, vector<vector<int>>& queries) {

        unordered_map<int, vector<int>> colorToIndexes;
        for (int i = 0; i < colors.size(); ++i) {

            //C++20: !colorToIndexes.contains(colors[i])
            if (colorToIndexes.find(colors[i]) == colorToIndexes.end()) {
                colorToIndexes[colors[i]] = vector<int>();
            }
            colorToIndexes[colors[i]].push_back(i);
        }
        return findShortestDistancesForAllQueries(colorToIndexes, queries);
    }

private:
    vector<int> findShortestDistancesForAllQueries(unordered_map<int, vector<int>>& colorToIndexes, const vector<vector<int>>& queries) {

        vector<int> resultShortestDistanceColor;

        for (const auto& query : queries) {
            int indexStartSearch = query[0];
            int color = query[1];

            if (colorToIndexes.find(color) == colorToIndexes.end()) {
                resultShortestDistanceColor.push_back(NOT_FOUND);
                continue;
            }
            int distance = findForShortestDistanceForCurrentQuery(colorToIndexes[color], indexStartSearch);
            resultShortestDistanceColor.push_back(distance);
        }

        return resultShortestDistanceColor;
    }

private:
    int findForShortestDistanceForCurrentQuery(const vector<int>& indexes, int indexStartSearch) {
        int left = 0;
        int right = indexes.size() - 1;

        while (left <= right) {

            int middle = left + (right - left) / 2;
            if (indexStartSearch == indexes[middle]) {
                return 0;
            }
            if (indexStartSearch > indexes[middle]) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }

        if (left == 0) {
            return indexes[0] - indexStartSearch;
        }
        if (left == indexes.size()) {
            return indexStartSearch - indexes[indexes.size() - 1];
        }

        return min(indexStartSearch - indexes[left - 1], indexes[left] - indexStartSearch);
    }
};
