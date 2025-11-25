#pragma once
#include <iostream>
#include <vector>
#include "./Review.h"
using namespace std;

class Place
{
private:
    string type;
    string name;
    int id;
    double latitude;
    double longitude;
    double quietness = 0.0;
    double wifi = 0.0;
    vector<Review> reviews;

public:
    Place(string t, string n, double lat, double lon);

    void print() const;
    void printReviews() const;

    void addReview(string username, double quietness, double wifiStrength, string comment);

    string getType() const;
    string getName() const;
    int getId() const;
    double getLatitude() const;
    double getLongitude() const;
    double getQuietness() const;
    double getWifi() const;
    vector<Review> getReviews() const;
};
