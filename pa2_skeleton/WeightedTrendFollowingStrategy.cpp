#include "WeightedTrendFollowingStrategy.h"
#include "Utils.h"
#include <cmath>

WeightedTrendFollowingStrategy::WeightedTrendFollowingStrategy()
{
}

WeightedTrendFollowingStrategy::WeightedTrendFollowingStrategy(const string &name, int shortWindow, int longWindow): TrendFollowingStrategy(name, shortWindow, longWindow)
{
}

double WeightedTrendFollowingStrategy::calculateExponentialWeight(int index) const
{
    return pow(1.1, index);
}

double WeightedTrendFollowingStrategy::calculateMovingAverage(Market *market, int index, int window) const
{
    double sum = 0.0;
    double weight_sum = 0.0;
    int start = max(index - window + 1, 0);
    for (int i = start; i < index + 1; i++) {
        sum += market->getPrice(i) * calculateExponentialWeight(i - start);
        weight_sum += calculateExponentialWeight(i - start);
    }
    return sum / weight_sum;
}

WeightedTrendFollowingStrategy **WeightedTrendFollowingStrategy::generateStrategySet(const string &baseName, int minShortWindow, int maxShortWindow, int stepShortWindow, int minLongWindow, int maxLongWindow, int stepLongWindow)
{
    WeightedTrendFollowingStrategy **StrategySet = new WeightedTrendFollowingStrategy *[((maxShortWindow - minShortWindow) / stepShortWindow + 1) * ((maxLongWindow - minLongWindow) / stepLongWindow + 1)];
    for (int i = minShortWindow; i < maxShortWindow + 1; i += stepShortWindow) {
        for (int j = minLongWindow; j < maxLongWindow + 1; j += stepLongWindow) {
            string strategy_name = baseName + "_" + to_string(i) + "_" + to_string(j);
            StrategySet[(i - minShortWindow) / stepShortWindow * ((maxLongWindow - minLongWindow) / stepLongWindow + 1) + (j - minLongWindow) / stepLongWindow] = new WeightedTrendFollowingStrategy(strategy_name, i, j);
        }
    }
    return StrategySet;
}
