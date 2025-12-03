#include "../../include/Reviews/IndoorPlaceReview.h"
#include <iostream>
using namespace std;
IndoorPlaceReview::IndoorPlaceReview(string username, double quietness, double wifi,
                                     string comment, double comfort,
                                     double price, double charging)
    : Review(username, quietness, wifi, comment),
      comfortScore(comfort),
      priceLevel(price),
      chargingAvailability(charging) {}

void IndoorPlaceReview::print() const
{
  cout << "IndoorPlaceReview by " << getUsername() << endl;
  cout << "Quietness: " << getQuietness()
       << ", WiFi: " << getWifi() << endl;
  cout << "Comment: " << getComment() << endl;
  cout << "Comfort: " << getComfortScore()
       << ", Price Level: " << getPriceLevel()
       << ", Charging Rating: " << getChargingAvailable() << endl;
}
