#include "TrendFollowingStrategy.h"
#include "Utils.h"
#include <iostream>

TrendFollowingStrategy::TrendFollowingStrategy()
{
    shortMovingAverageWindow = longMovingAverageWindow = 0;
}

TrendFollowingStrategy::TrendFollowingStrategy(const std::string &name, int shortWindow, int longWindow): Strategy(name)
{
    shortMovingAverageWindow = shortWindow;
    longMovingAverageWindow = longWindow;
}

Action TrendFollowingStrategy::decideAction(Market *market, int index, double currentHolding) const
{
    double shortMA = calculateMovingAverage(market, index, shortMovingAverageWindow);
    // cout << "shortMA:" << shortMA << endl;
    double longMA = calculateMovingAverage(market, index, longMovingAverageWindow);
    // cout << "longMA:" << longMA << endl;
    if (shortMA > longMA && !currentHolding) {
        return BUY;
    }
    if (shortMA < longMA && currentHolding) {
        return SELL;
    }
    return HOLD;
}

TrendFollowingStrategy **TrendFollowingStrategy::generateStrategySet(const string &baseName, int minShortWindow, int maxShortWindow, int stepShortWindow, int minLongWindow, int maxLongWindow, int stepLongWindow)
{
    TrendFollowingStrategy **StrategySet = new TrendFollowingStrategy *[((maxShortWindow - minShortWindow) / stepShortWindow + 1) * ((maxLongWindow - minLongWindow) / stepLongWindow + 1)];
    for (int i = minShortWindow; i < maxShortWindow + 1; i += stepShortWindow) {
        for (int j = minLongWindow; j < maxLongWindow + 1; j += stepLongWindow) {
            string strategy_name = baseName + "_" + to_string(i) + "_" + to_string(j);
            StrategySet[(i - minShortWindow) / stepShortWindow * ((maxLongWindow - minLongWindow) / stepLongWindow + 1) + (j - minLongWindow) / stepLongWindow] = new TrendFollowingStrategy(strategy_name, i, j);
        }
    }
    return StrategySet;
}
