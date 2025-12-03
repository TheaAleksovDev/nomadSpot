#pragma once
#include "./json.hpp"
#include "./Locations/IndoorPlace.h"
#include "./Locations/OutdoorPlace.h"
#include "./Reviews/IndoorPlaceReview.h"
#include "./Reviews/OutdoorPlaceReview.h"
#include <fstream>
#include <vector>
#include <string>

using json = nlohmann::json;

class PlaceDeserializer
{
public:
    static json loadJson(const std::string &filename = "places.json")
    {
        std::ifstream in(filename);
        if (!in.is_open())
            return json{{"places", json::array()}};

        json data;
        in >> data;
        return data;
    }

    static std::vector<OutdoorPlace> loadOutdoorPlaces()
    {
        std::vector<OutdoorPlace> outdoorPlaces;
        json data = loadJson();

        for (auto &place : data["places"])
        {
            if (place.value("locationType", "") == "Outdoor Place")
            {
                OutdoorPlace op(
                    place.value("type", ""),
                    place.value("name", ""),
                    place.value("latitude", 0.0),
                    place.value("longitude", 0.0),
                    place.value("open", 0),
                    place.value("close", 0));

                op.setAvailable(place.value("available", true));

                for (auto &r : place.value("reviews", json::array()))
                {
                    OutdoorPlaceReview rev(
                        r.value("username", ""),
                        r.value("quietness", 0.0),
                        r.value("wifi", 0.0),
                        r.value("comment", ""),
                        r.value("shade", 0.0),
                        r.value("benches", 0.0),
                        r.value("charging", 0.0),
                        r.value("petFriendly", 0.0),
                        r.value("shopsNearby", 0.0),
                        r.value("publicToilet", 0.0));
                    op.addReview(rev);
                }

                outdoorPlaces.push_back(op);
            }
        }

        return outdoorPlaces;
    }

    static std::vector<IndoorPlace> loadIndoorPlaces()
    {
        std::vector<IndoorPlace> indoorPlaces;
        json data = loadJson();

        for (auto &place : data["places"])
        {
            if (place.value("locationType", "") == "Indoor Place")
            {
                IndoorPlace ip(
                    place.value("type", ""),
                    place.value("name", ""),
                    place.value("latitude", 0.0),
                    place.value("longitude", 0.0),
                    place.value("open", 0),
                    place.value("close", 0));
                ip.setAvailable(place.value("available", true));

                for (auto &r : place.value("reviews", json::array()))
                {
                    IndoorPlaceReview rev(
                        r.value("username", ""),
                        r.value("quietness", 0.0),
                        r.value("wifi", 0.0),
                        r.value("comment", ""),
                        r.value("comfort", 0.0),
                        r.value("price", 0.0),
                        r.value("charging", 0.0));
                    ip.addReview(rev);
                }

                indoorPlaces.push_back(ip);
            }
        }

        return indoorPlaces;
    }
};
