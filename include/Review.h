#pragma once
#include <string>
using namespace std;

class Review
{
private:
    string username;
    double quietness;
    double wifi;
    string comment;

public:
    Review(string u, double q, double w, string c);

    void print() const;

    string getUsername() const;
    double getQuietness() const;
    double getWifi() const;
    string getComment() const;
};
