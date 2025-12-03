#pragma once
#include "./json.hpp"
#include "./Place.h"
#include "./Locations/OutdoorPlace.h"
#include "./Locations/IndoorPlace.h"
#include "./Review.h"
#include <fstream>

using json = nlohmann::json;

class PlaceSerializer
{
public:
    static json load()
    {
        std::ifstream in("places.json");
        if (!in.is_open())
            return json{{"places", json::array()}};

        json data;
        in >> data;
        return data;
    }

    template <typename T>
    static void updatePlaceAvailability(const Place<T> &place)
    {
        nlohmann::json data = load();

        for (auto &p : data["places"])
        {
            if (p["name"] == place.getName())
            {
                p["available"] = place.getAvailable();
                break;
            }
        }

        std::ofstream file("places.json");
        file << data.dump(4);
    }

    static void save(const json &data)
    {
        std::ofstream out("places.json");
        out << data.dump(4);
    }

    static void addOutdoorPlace(const OutdoorPlace &p)
    {
        json data = load();

        for (auto &place : data["places"])
            if (place["name"] == p.getName())
                return;

        json item;
        item["name"] = p.getName();
        item["locationType"] = "Outdoor Place";
        item["type"] = p.getType();
        item["latitude"] = p.getLatitude();
        item["longitude"] = p.getLongitude();
        item["open"] = p.getWorkingHoursStart();
        item["close"] = p.getWorkingHoursEnd();
        item["available"] = p.getAvailable();
        item["reviews"] = json::array();

        data["places"].push_back(item);
        save(data);
    }

    static void addIndoorPlace(const IndoorPlace &p)
    {
        json data = load();

        for (auto &place : data["places"])
            if (place["name"] == p.getName())
                return;

        json item;
        item["name"] = p.getName();
        item["locationType"] = "Indoor Place";
        item["type"] = p.getType();
        item["latitude"] = p.getLatitude();
        item["longitude"] = p.getLongitude();
        item["open"] = p.getWorkingHoursStart();
        item["close"] = p.getWorkingHoursEnd();
        item["reviews"] = json::array();
        item["available"] = p.getAvailable();

        data["places"].push_back(item);
        save(data);
    }

    static void addReviewToJSON(const std::string &placeName, const OutdoorPlaceReview &r)
    {
        json data = load();

        for (auto &place : data["places"])
        {
            if (place["name"] == placeName)
            {
                json rev;
                rev["username"] = r.getUsername();
                rev["quietness"] = r.getQuietness();
                rev["wifi"] = r.getWifi();
                rev["comment"] = r.getComment();
                rev["shade"] = r.getShadeAvailable();
                rev["benches"] = r.getBenchesAvailable();
                rev["charging"] = r.getChargingAvailable();
                rev["petFriendly"] = r.getPetFriendly();
                rev["shopsNearby"] = r.getShopsNearby();
                rev["publicToilet"] = r.getPublicToiletAvailable();

                place["reviews"].push_back(rev);

                int n = place["reviews"].size();
                double sumWifi = 0, sumQuiet = 0;
                double sumShade = 0, sumBenches = 0, sumCharging = 0, sumPet = 0, sumShops = 0, sumToilet = 0;

                for (auto &rev : place["reviews"])
                {
                    sumWifi += rev.value("wifi", 0.0);
                    sumQuiet += rev.value("quietness", 0.0);
                    sumShade += rev.value("shade", 0.0);
                    sumBenches += rev.value("benches", 0.0);
                    sumCharging += rev.value("charging", 0.0);
                    sumPet += rev.value("petFriendly", 0.0);
                    sumShops += rev.value("shopsNearby", 0.0);
                    sumToilet += rev.value("publicToilet", 0.0);
                }

                place["averageWifi"] = sumWifi / n;
                place["averageQuietness"] = sumQuiet / n;
                place["averageShade"] = sumShade / n;
                place["averageBenches"] = sumBenches / n;
                place["averageCharging"] = sumCharging / n;
                place["averagePetFriendly"] = sumPet / n;
                place["averageShopsNearby"] = sumShops / n;
                place["averagePublicToilet"] = sumToilet / n;

                save(data);
                return;
            }
        }
    }

    static void addReviewToJSON(const std::string &placeName, const IndoorPlaceReview &r)
    {
        json data = load();

        for (auto &place : data["places"])
        {
            if (place["name"] == placeName)
            {
                json rev;
                rev["username"] = r.getUsername();
                rev["quietness"] = r.getQuietness();
                rev["wifi"] = r.getWifi();
                rev["comment"] = r.getComment();
                rev["comfort"] = r.getComfortScore();
                rev["price"] = r.getPriceLevel();
                rev["charging"] = r.getChargingAvailable();

                place["reviews"].push_back(rev);

                int n = place["reviews"].size();
                double sumWifi = 0, sumQuiet = 0, sumComfort = 0, sumPrice = 0, sumCharging = 0;

                for (auto &rev : place["reviews"])
                {
                    sumWifi += rev.value("wifi", 0.0);
                    sumQuiet += rev.value("quietness", 0.0);
                    sumComfort += rev.value("comfort", 0.0);
                    sumPrice += rev.value("price", 0.0);
                    sumCharging += rev.value("charging", 0.0);
                }

                place["averageWifi"] = sumWifi / n;
                place["averageQuietness"] = sumQuiet / n;
                place["averageComfort"] = sumComfort / n;
                place["averagePrice"] = sumPrice / n;
                place["averageCharging"] = sumCharging / n;

                save(data);
                return;
            }
        }
    }
};
