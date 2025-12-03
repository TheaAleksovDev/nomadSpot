#pragma once
#include "../Place.h"
#include "../Reviews/IndoorPlaceReview.h"
#include <iostream>
using namespace std;

class IndoorPlace : public Place<IndoorPlaceReview>
{
private:
    double comfortScore = 0.0;
    double priceLevel = 0.0;
    double chargingAvailability = 0.0;

public:
    IndoorPlace() : Place<IndoorPlaceReview>("", "", 0.0, 0.0, 0, 0) {};
    IndoorPlace(string t, string n, double lat, double lon,
                int startHour, int endHour)
        : Place<IndoorPlaceReview>(t, n, lat, lon, startHour, endHour) {}

    void print() const override
    {
        cout << "IndoorPlace: " << getName() << " (" << getType() << ")\n";
        cout << "Location: " << getLatitude() << ", " << getLongitude() << endl;
        cout << "Wifi Rating: " << getWifiRating() << endl;
        cout << "Quietness: " << getQuietnessRating() << endl;
        cout << "Comfort: " << getComfortScore() << endl;
        cout << "Price Level: " << getPriceLevel() << endl;
        cout << "Charging Rating: " << getChargingAvailable() << endl;
        cout << "Working Hours: " << getWorkingHoursStart() << " to "
             << getWorkingHoursEnd() << endl;
        cout << "-----------------------------------------------\n";
    }

    void updateGeneralReviews() override
    {
        Place<IndoorPlaceReview>::updateGeneralReviews();

        if (getReviews().empty())
        {
            comfortScore = 0.0;
            priceLevel = 0.0;
            chargingAvailability = 0.0;
            return;
        }

        double totalComfort = 0.0;
        double totalPrice = 0.0;
        double totalChargingAvailability = 0.0;

        for (const auto &review : getReviews())
        {
            totalComfort += review.getComfortScore();
            totalPrice += review.getPriceLevel();
            totalChargingAvailability += review.getChargingAvailable();
        }

        comfortScore = totalComfort / getReviews().size();
        priceLevel = totalPrice / getReviews().size();
        chargingAvailability = totalChargingAvailability / getReviews().size();
    }

    double getComfortScore() const { return comfortScore; }
    double getPriceLevel() const { return priceLevel; }
    double getChargingAvailable() const { return chargingAvailability; }

    void setComfortScore(double val) { comfortScore = val; }
    void setPriceLevel(double val) { priceLevel = val; }
    void setChargingAvailability(double val) { chargingAvailability = val; }
};

ostream &operator<<(ostream &os, const IndoorPlace &place)
{
    place.print();
    return os;
}