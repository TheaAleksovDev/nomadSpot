#include "../include/Review.h"
#include <iostream>
using namespace std;

Review::Review(string u, double q, double w, string c)
    : username(u), quietness(q), wifi(w), comment(c) {}

string Review::getUsername() const { return username; }
double Review::getQuietness() const { return quietness; }
double Review::getWifi() const { return wifi; }
string Review::getComment() const { return comment; }
