#include "TradingBot.h"
#include <limits>

TradingBot::TradingBot(Market *market, int initialCapacity)
{
    this->market = market;
    this->strategyCount = 0;
    this->strategyCapacity = initialCapacity;
    availableStrategies = new Strategy *[strategyCapacity];
    for (int i = 0; i < strategyCapacity; i++) {
        availableStrategies[i] = nullptr;
    }
}

TradingBot::~TradingBot()
{
    for (int i = 0; i < strategyCount; i++) {
        delete availableStrategies[i];
    }
    delete[] availableStrategies;
}

void TradingBot::addStrategy(Strategy *strategy)
{
    if (strategyCount == strategyCapacity) {
        Strategy **temp = availableStrategies;
        int temp_capacity = strategyCapacity;
        strategyCapacity *= 2;
        availableStrategies = new Strategy *[strategyCapacity];
        for (int i = 0; i < strategyCapacity; i++) {
            if (i < temp_capacity) {
                availableStrategies[i] = temp[i];
            } else {
                availableStrategies[i] = nullptr;
            }
        }
        delete[] temp;
    }

    availableStrategies[strategyCount++] = strategy;
}

SimulationResult TradingBot::runSimulation()
{
    // market->simulate();
    SimulationResult best_result;
    // cout << best_result.totalReturn << endl;
    for (int s = 0; s < strategyCount; s++) {
        // cout << s << ":" << strategyCount << endl;
        double cum_profit = 0.0;
        double purchase_price = 0.0;
        // double purchase_price = market->getPrice(market->getNumTradingDays() - 101);
        // cout << "purchase_price:" << purchase_price << endl;
        double holding = 0;
        // double holding = 1;
        for (int d = market->getNumTradingDays() - 101; d < market->getNumTradingDays(); d++) {
            // cout << d << ":" << market->getNumTradingDays() << endl;
            // cout << availableStrategies[s]->getName() << endl;
            // if (availableStrategies[s]->getName() == "Trend_5_30") {
            Action action = availableStrategies[s]->decideAction(market, d, holding);
            switch(action) {
                case(BUY):
                    purchase_price = market->getPrice(d);
                    holding = 1;
                    break;
                case(SELL):
                    cum_profit += market->getPrice(d) - purchase_price;
                    // cout << "SELL:" << cum_profit << endl;
                    holding = 0;
                    break;
                default:
                    break;
            }
        }
        // cout << availableStrategies[s]->getName() << endl;
        
        if (holding) {
            cum_profit += market->getLastPrice() - purchase_price;
        }
        // cout << cum_profit << endl;
        
        if (cum_profit > best_result.totalReturn) {
            best_result.bestStrategy = availableStrategies[s];
            best_result.totalReturn = cum_profit;
        }
    }
    return best_result;
}
