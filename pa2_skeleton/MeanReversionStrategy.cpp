#include "MeanReversionStrategy.h"
#include "Utils.h"
#include <cmath>
#include <iostream>

MeanReversionStrategy::MeanReversionStrategy()
{
    window = threshold = 0;
}

MeanReversionStrategy::MeanReversionStrategy(const string &name, int window, int threshold): Strategy(name)
{
    this->window = window;
    this->threshold = threshold;
}

Action MeanReversionStrategy::decideAction(Market *market, int index, double currentHolding) const
{
    double MA = calculateMovingAverage(market, index, window);
    double price = market->getPrice(index);
    if (price > MA * (1 + threshold / 100.0) && currentHolding) {
        return SELL;
    }
    if (price < MA * (1 - threshold / 100.0) && !currentHolding) {
        return BUY;
    }
    return HOLD;
}

MeanReversionStrategy **MeanReversionStrategy::generateStrategySet(const string &baseName, int minWindow, int maxWindow, int windowStep, int minThreshold, int maxThreshold, int thresholdStep)
{
    MeanReversionStrategy **StrategySet = new MeanReversionStrategy *[((maxWindow - minWindow) / windowStep + 1) * ((maxThreshold - minThreshold) / thresholdStep + 1)];
    for (int i = minWindow; i < maxWindow + 1; i += windowStep) {
        for (int j = minThreshold; j < maxThreshold + 1; j += thresholdStep) {
            string strategy_name = baseName + "_" + to_string(i) + "_" + to_string(j);
            StrategySet[(i - minWindow) / windowStep * ((maxThreshold - minThreshold) / thresholdStep + 1) + (j - minThreshold) / thresholdStep] = new MeanReversionStrategy(strategy_name, i, j);
        }
    }
    return StrategySet;
}