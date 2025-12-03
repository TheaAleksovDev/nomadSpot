#pragma once
#include "../Review.h"
#include <string>
using namespace std;
class OutdoorPlaceReview : public Review
{
private:
    double shadeAvailability;
    double benchesAvailability;
    double chargingAvailability;
    double petFriendly;
    double shopsNearby;
    double publicToiletAvailable;

public:
    OutdoorPlaceReview(string username,
                       double quietness,
                       double wifi,
                       string comment,
                       double shade,
                       double benches,
                       double charging,
                       double pets,
                       double shops,
                       double toilet);

    void print() const override;

    double getShadeAvailable() const { return shadeAvailability; }
    double getBenchesAvailable() const { return benchesAvailability; }
    double getChargingAvailable() const { return chargingAvailability; }
    double getPetFriendly() const { return petFriendly; }
    double getShopsNearby() const { return shopsNearby; }
    double getPublicToiletAvailable() const { return publicToiletAvailable; }

    void setShadeAvailability(double val) { shadeAvailability = val; }
    void setBnchesAvailability(double val) { benchesAvailability = val; }
    void setChargingAvailability(double val) { chargingAvailability = val; }
    void setPetFriendly(double val) { petFriendly = val; }
    void setShopsNearby(double val) { shopsNearby = val; }
    void getPublicToiletAvailable(double val) { publicToiletAvailable = val; }
};
