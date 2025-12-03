#pragma once
#include "../Review.h"
#include <string>
using namespace std;
class IndoorPlaceReview : public Review
{
private:
    double comfortScore;
    double priceLevel;
    double chargingAvailability;

public:
    IndoorPlaceReview(string username,
                      double quietness,
                      double wifi,
                      string comment,
                      double comfort,
                      double price,
                      double charging);

    void print() const override;

    double getComfortScore() const { return comfortScore; }
    double getPriceLevel() const { return priceLevel; }
    double getChargingAvailable() const { return chargingAvailability; }

    void setComfortScore(double comfort) { comfortScore = comfort; }
    void setPriceLevel(double price) { priceLevel = price; }
    void setChargingAvailable(double charging) { chargingAvailability = charging; }
};
