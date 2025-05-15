#include "Strategy.h"
#include <iostream>

Strategy::Strategy()
{
    name = "";
}

Strategy::Strategy(const string &name)
{
    this->name = name;
}

double Strategy::calculateMovingAverage(Market *market, int index, int window) const
{
    double sum = 0.0;
    // if (index - window < -1) {
    //     index = 0;
    // }

    for (int i = index; i > index - window; i--) {
        if (i < 0) {
            break;
        }
        sum += market->getPrice(i);
    }
    return sum / min(index+1, window);
}

string Strategy::getName() const
{
    return name;
}
