#include "../../include/Reviews/OutdoorPlaceReview.h"
#include <iostream>
using namespace std;

OutdoorPlaceReview::OutdoorPlaceReview(string username, double quietness, double wifi,
                                       string comment, double shade, double benches,
                                       double charging, double pets, double shops, double toilet)
    : Review(username, quietness, wifi, comment),
      shadeAvailability(shade),
      benchesAvailability(benches),
      chargingAvailability(charging),
      petFriendly(pets),
      shopsNearby(shops),
      publicToiletAvailable(toilet) {}

void OutdoorPlaceReview::print() const
{
  cout << "OutdoorPlaceReview by " << getUsername() << endl;
  cout << "Quietness: " << getQuietness()
       << ", WiFi: " << getWifi() << endl;
  cout << "Comment: " << getComment() << endl;
  cout << "Shade: " << getShadeAvailable()
       << ", Benches: " << getBenchesAvailable()
       << ", Charging Rating: " << getChargingAvailable() << endl;
  cout << "Pet Friendly: " << getPetFriendly()
       << ", Shops Nearby: " << getShopsNearby();
  cout << ", Public Toilet: " << getPublicToiletAvailable() << endl;
}
