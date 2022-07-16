
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Solution {

    private static final int NOT_FOUND = -1;

    public List<Integer> shortestDistanceColor(int[] colors, int[][] queries) {
        Map<Integer, List<Integer>> colorToIndexes = new HashMap<>();
        for (int i = 0; i < colors.length; ++i) {
            colorToIndexes.computeIfAbsent(colors[i], indexes -> new ArrayList<>()).add(i);
        }
        return findShortestDistancesForAllQueries(colorToIndexes, queries);
    }

    private List<Integer> findShortestDistancesForAllQueries(Map<Integer, List<Integer>> colorToIndexes, int[][] queries) {
        List<Integer> resultShortestDistanceColor = new ArrayList<>();
        for (int[] query : queries) {
            int indexStartSearch = query[0];
            int color = query[1];

            if (!colorToIndexes.containsKey(color)) {
                resultShortestDistanceColor.add(NOT_FOUND);
                continue;
            }
            int distance = findForShortestDistanceForCurrentQuery(colorToIndexes.get(color), indexStartSearch);
            resultShortestDistanceColor.add(distance);
        }

        return resultShortestDistanceColor;
    }

    private int findForShortestDistanceForCurrentQuery(List<Integer> indexes, int indexStartSearch) {
        int left = 0;
        int right = indexes.size() - 1;

        while (left <= right) {

            int middle = left + (right - left) / 2;
            if (indexStartSearch == indexes.get(middle)) {
                return 0;
            }
            if (indexStartSearch > indexes.get(middle)) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }

        if (left == 0) {
            return indexes.get(0) - indexStartSearch;
        }
        if (left == indexes.size()) {
            return indexStartSearch - indexes.get(indexes.size() - 1);
        }

        return Math.min(indexStartSearch - indexes.get(left - 1), indexes.get(left) - indexStartSearch);

    }
}
