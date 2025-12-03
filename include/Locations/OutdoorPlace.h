#pragma once
#include "../Place.h"
#include "../Reviews/OutdoorPlaceReview.h"
#include <iostream>
using namespace std;

class OutdoorPlace : public Place<OutdoorPlaceReview>
{
private:
    double shadeAvailability = 0.0;
    double benchesAvailability = 0.0;
    double chargingAvailability = 0.0;
    double petFriendly = 0.0;
    double shopsNearby = 0.0;
    double publicToiletAvailable = 0.0;

public:
    OutdoorPlace() : Place<OutdoorPlaceReview>("", "", 0.0, 0.0, 0, 0) {};
    OutdoorPlace(string t, string n, double lat, double lon, int startHour = 0, int endHour = 24)
        : Place<OutdoorPlaceReview>(t, n, lat, lon, startHour, endHour) {}

    void print() const override
    {
        cout << "OutdoorPlace: " << getName() << " (" << getType() << ")\n";
        cout << "Location: " << getLatitude() << ", " << getLongitude() << endl;
        cout << "Wifi Rating: " << getWifiRating() << endl;
        cout << "Quietness: " << getQuietnessRating() << endl;
        cout << "Shade: " << getShadeAvailable() << endl;
        ;
        cout << "Benches: " << getBenchesAvailable() << endl;
        cout << "Charging Rating: " << getChargingAvailable() << endl;
        cout
            << "Pet Friendly: " << getPetFriendly() << endl;
        cout << "Shops Nearby: " << getShopsNearby() << endl;
        cout << "Working Hours: " << getWorkingHoursStart() << " to "
             << getWorkingHoursEnd() << endl;
        cout << "Public Toilet: " << getPublicToiletAvailable() << endl;
        cout << "-----------------------------------------------\n";
    }

    void updateGeneralReviews() override
    {
        Place<OutdoorPlaceReview>::updateGeneralReviews();

        if (getReviews().empty())
        {
            shadeAvailability = 0.0;
            benchesAvailability = 0.0;
            chargingAvailability = 0.0;
            petFriendly = 0.0;
            shopsNearby = 0.0;
            publicToiletAvailable = 0.0;
            return;
        }

        double totalShade = 0.0;
        double totalBenches = 0.0;
        double totalCharging = 0.0;
        double totalPets = 0.0;
        double totalShops = 0.0;
        double totalToilet = 0.0;

        for (const auto &review : getReviews())
        {
            totalShade += review.getShadeAvailable();
            totalBenches += review.getBenchesAvailable();
            totalCharging += review.getChargingAvailable();
            totalPets += review.getPetFriendly();
            totalShops += review.getShopsNearby();
            totalToilet += review.getPublicToiletAvailable();
        }

        shadeAvailability = totalShade / getReviews().size();
        benchesAvailability = totalBenches / getReviews().size();
        chargingAvailability = totalCharging / getReviews().size();
        petFriendly = totalPets / getReviews().size();
        shopsNearby = totalShops / getReviews().size();
        publicToiletAvailable = totalToilet / getReviews().size();
    }
    double getShadeAvailable() const { return shadeAvailability; }
    double getBenchesAvailable() const { return benchesAvailability; }
    double getChargingAvailable() const { return chargingAvailability; }
    double getPetFriendly() const { return petFriendly; }
    double getShopsNearby() const { return shopsNearby; }
    double getPublicToiletAvailable() const { return publicToiletAvailable; }

    void setShadeAvailability(double val) { shadeAvailability = val; }
    void setBenchesAvailability(double val) { benchesAvailability = val; }
    void setChargingAvailability(double val) { chargingAvailability = val; }
    void setPetFriendly(double val) { petFriendly = val; }
    void setShopsNearby(double val) { shopsNearby = val; }
    void setPublicToiletAvailable(double val) { publicToiletAvailable = val; }
};

ostream &operator<<(ostream &os, const OutdoorPlace &place)
{
    place.print();
    return os;
}