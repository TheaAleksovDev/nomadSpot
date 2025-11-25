#include "../include/Place.h"
#include <iostream>
using namespace std;

Place::Place(string t, string n, double lat, double lon)
    : type(t), name(n), latitude(lat), longitude(lon) {}

void Place::print() const
{
    cout << "Place ID: " << id << ", Name: " << name << ", Type: " << type
         << ", Latitude: " << latitude << ", Longitude: " << longitude
         << ", Average Quietness: " << quietness
         << ", Average WiFi: " << wifi << endl;
}

void Place::printReviews() const
{
    for (const auto &review : reviews)
    {
        review.print();
    }
}

void Place::addReview(string username, double quietness, double wifiStrength, string comment)
{
    Review review(username, quietness, wifiStrength, comment);
    reviews.push_back(review);
}

string Place::getType() const { return type; }
string Place::getName() const { return name; }
int Place::getId() const { return id; }
double Place::getLatitude() const { return latitude; }
double Place::getLongitude() const { return longitude; }
double Place::getQuietness() const { return quietness; }
double Place::getWifi() const { return wifi; }
vector<Review> Place::getReviews() const { return reviews; }
