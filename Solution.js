
/**
 * @param {number[]} colors
 * @param {number[][]} queries
 * @return {number[]}
 */
var shortestDistanceColor = function (colors, queries) {
    this.NOT_FOUND = -1;
    const colorToIndexes = new Map();
    for (let i = 0; i < colors.length; ++i) {
        if (!colorToIndexes.has(colors[i])) {
            colorToIndexes.set(colors[i], []);
        }
        colorToIndexes.get(colors[i]).push(i);
    }

    return findShortestDistancesForAllQueries(colorToIndexes, queries);
};

/**
 * @param {Map<number,[]>} colorToIndexes
 * @param {number[][]} queries
 * @return {number[]}
 */
function findShortestDistancesForAllQueries(colorToIndexes, queries) {
    const resultShortestDistanceColor = [];
    for (let query of queries) {
        let indexStartSearch = query[0];
        let color = query[1];

        if (!colorToIndexes.has(color)) {
            resultShortestDistanceColor.push(this.NOT_FOUND);
            continue;
        }
        let distance = findForShortestDistanceForCurrentQuery(colorToIndexes.get(color), indexStartSearch);
        resultShortestDistanceColor.push(distance);
    }

    return resultShortestDistanceColor;
}

/**
 * @param {number[]} indexes
 * @param {number} indexStartSearch
 * @return {number}
 */
function findForShortestDistanceForCurrentQuery(indexes, indexStartSearch) {
    let left = 0;
    let right = indexes.length - 1;

    while (left <= right) {

        let middle = left + Math.floor((right - left) / 2);
        if (indexStartSearch === indexes[middle]) {
            return 0;
        }
        if (indexStartSearch > indexes[middle]) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
    }

    if (left === 0) {
        return indexes[0] - indexStartSearch;

    }
    if (left === indexes.length) {
        return indexStartSearch - indexes[indexes.length - 1];
    }

    return Math.min(indexStartSearch - indexes[left - 1], indexes[left] - indexStartSearch);
}
