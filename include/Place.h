#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "./Review.h"
using namespace std;

template <typename T>
class Place;

template <typename PlaceType>
const PlaceType &closerTo(const PlaceType &a, const PlaceType &b, double refLat, double refLon);

template <typename T>
class Place
{
private:
    string type;
    string name;
    double latitude;
    double longitude;
    double quietness = 0.0;
    double wifi = 0.0;
    int workingHoursStart = 0;
    int workingHoursEnd = 0;
    bool available = true;
    vector<T> reviews;

public:
    Place(string t, string n, double lat, double lon, int start, int end)
        : type(t), name(n), latitude(lat), longitude(lon), workingHoursStart(start), workingHoursEnd(end) {}

    template <typename PlaceType>
    friend const PlaceType &closerTo(const PlaceType &a, const PlaceType &b, double refLat, double refLon);

    virtual void print() const = 0;

    virtual void updateGeneralReviews()
    {
        if (reviews.empty())
        {
            wifi = 0.0;
            quietness = 0.0;
            return;
        }

        double totalWifi = 0.0;
        double totalQuietness = 0.0;

        for (const auto &review : reviews)
        {
            totalWifi += review.getWifi();
            totalQuietness += review.getQuietness();
        }

        wifi = totalWifi / reviews.size();
        quietness = totalQuietness / reviews.size();
    }

    void addReview(const T &review)
    {
        reviews.push_back(review);
        updateGeneralReviews();
    }

    void setType(const string &t) { type = t; }
    void setName(const string &n) { name = n; }
    void setLatitude(double lat) { latitude = lat; }
    void setLongitude(double lon) { longitude = lon; }
    void setQuietness(double q) { quietness = q; }
    void setWifi(double w) { wifi = w; }
    void setAvailable(bool a) { available = a; }
    void setWorkingHoursStart(int h) { workingHoursStart = h; }
    void setWorkingHoursEnd(int h) { workingHoursEnd = h; }

    bool getAvailable() const { return available; }
    string getType() const { return type; }
    string getName() const { return name; }
    int getId() const { return id; }
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }
    double getQuietnessRating() const { return quietness; }
    double getWifiRating() const { return wifi; }
    int getWorkingHoursStart() const { return workingHoursStart; }
    int getWorkingHoursEnd() const { return workingHoursEnd; }
    const vector<T> &getReviews() const { return reviews; }
};

template <typename T>
double dist(double lat1, double lon1, double lat2, double lon2)
{
    return sqrt(pow(lat1 - lat2, 2) + pow(lon1 - lon2, 2));
}

template <typename PlaceType>
const PlaceType &closerTo(const PlaceType &a, const PlaceType &b, double refLat, double refLon)
{
    auto dist = [](double lat1, double lon1, double lat2, double lon2)
    {
        double dx = lat1 - lat2;
        double dy = lon1 - lon2;
        return dx * dx + dy * dy;
    };

    double d1 = dist(a.getLatitude(), a.getLongitude(), refLat, refLon);
    double d2 = dist(b.getLatitude(), b.getLongitude(), refLat, refLon);

    return (d1 < d2) ? a : b;
}
template <typename T>
void markNotAvailable(Place<T> &p)
{
    p.setAvailable(false);
}
