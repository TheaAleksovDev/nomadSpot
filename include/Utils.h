#include <cmath>
#include <algorithm>
#include <vector>

#include "./PlaceDeserializer.h"
#include "./PlaceSerializer.h"

#include "./Place.h"
#include <iostream>
using namespace std;

template <typename T>
vector<T> findClosestPlaces(const vector<T> &places, double userLat, double userLon, int n = 3)
{
    auto distance = [userLat, userLon](const T &p)
    {
        double dlat = p.getLatitude() - userLat;
        double dlon = p.getLongitude() - userLon;
        return sqrt(dlat * dlat + dlon * dlon);
    };

    vector<T> sortedPlaces = places;
    sort(sortedPlaces.begin(), sortedPlaces.end(),
         [&distance](const T &a, const T &b)
         {
             return distance(a) < distance(b);
         });

    if (sortedPlaces.size() > n)
        sortedPlaces.resize(n);

    return sortedPlaces;
}

template <typename T>
std::vector<std::string> getAllPlaceNames(const std::vector<T> &places)
{
    std::vector<std::string> names;
    names.reserve(places.size());

    for (const auto &p : places)
    {
        names.push_back(p.getName());
    }

    return names;
}

void addNewPlace()
{
    auto indoorPlaces = PlaceDeserializer::loadIndoorPlaces();
    auto outdoorPlaces = PlaceDeserializer::loadOutdoorPlaces();
    auto allPlacesNamesIndoor = getAllPlaceNames(indoorPlaces);
    auto allPlacesNamesOutdoor = getAllPlaceNames(outdoorPlaces);
    cout << "\n--- Existing Indoor Places ---\n";

    for (int i = 0; i < allPlacesNamesIndoor.size(); i++)
    {
        cout << i + 1 << ". " << allPlacesNamesIndoor[i] << "; ";
    }
    cout << endl;
    cout << "\n--- Existing Outdoor Places ---\n";

    for (int i = 0; i < allPlacesNamesOutdoor.size(); i++)
    {
        cout << i + 1 << ". " << allPlacesNamesOutdoor[i] << "; ";
    }
    cout << endl;

    int placeType;
    cout << "Which type of place will you add?\n1. IndoorPlace\n2. OutdoorPlace\nChoose 1 or 2: ";
    cin >> placeType;

    string type, name;
    double latitude, longitude;
    int startHour, endHour;

    cout << "Enter place type: ";
    getline(cin >> ws, type);

    cout << "Enter place name: ";
    getline(cin >> ws, name);

    cout << "Enter latitude: ";
    cin >> latitude;

    cout << "Enter longitude: ";
    cin >> longitude;

    cout << "Enter working hour start: ";
    cin >> startHour;

    cout << "Enter working hour end: ";
    cin >> endHour;

    if (placeType == 1)
    {

        IndoorPlace newPlace(type, name, latitude, longitude, startHour, endHour);
        PlaceSerializer::addIndoorPlace(newPlace);
    }
    else if (placeType == 2)
    {
        OutdoorPlace newPlace(type, name, latitude, longitude, startHour, endHour);
        PlaceSerializer::addOutdoorPlace(newPlace);
    }
    cout << "\n--- Place is added! ---\n";
}

void addReviewToPlace()
{
    int placeType;
    cout << "Which type of place will you add a review for?\n1. IndoorPlace\n2. OutdoorPlace\nChoose 1 or 2: ";
    cin >> placeType;

    if (placeType == 1)
    {
        auto indoorPlaces = PlaceDeserializer::loadIndoorPlaces();
        auto allPlacesNames = getAllPlaceNames(indoorPlaces);
        cout << "\n--- Existing Indoor Places ---\n";

        for (int i = 0; i < allPlacesNames.size(); i++)
        {
            cout << i + 1 << ". " << allPlacesNames[i] << "; ";
        }
        cout << endl;
        int id;
        cout << "Choose a place you want to add review to: ";
        cin >> id;

        string username, comment;
        double quietness, wifi, comfort, price, charging;

        cout << "Enter your username: ";
        getline(cin >> ws, username);

        cout << "Rate quietness (0-5): ";
        cin >> quietness;

        cout << "Rate wifi quality (0-5): ";
        cin >> wifi;

        cout << "Write a comment: ";
        getline(cin >> ws, comment);

        cout << "Rate comfort (0-5): ";
        cin >> comfort;

        cout << "Rate price level (0-5): ";
        cin >> price;

        cout << "Rate charging availability (0-5): ";
        cin >> charging;

        IndoorPlaceReview review(
            username,
            quietness,
            wifi,
            comment,
            comfort,
            price,
            charging);
        PlaceSerializer::addReviewToJSON(allPlacesNames[id - 1], review);
        cout << "\n--- Review for " << allPlacesNames[id - 1] << " is added !-- -\n ";
    }
    else if (placeType == 2)
    {
        auto outdoorPlaces = PlaceDeserializer::loadOutdoorPlaces();
        auto allPlacesNames = getAllPlaceNames(outdoorPlaces);
        cout << "\n--- Existing Outdoor Places ---\n";

        for (int i = 0; i < allPlacesNames.size(); i++)
        {
            cout << i + 1 << ". " << allPlacesNames[i] << "; ";
        }
        cout << endl;
        int id;
        cout << "Choose a place you want to add review to: ";
        cin >> id;

        string username, comment;
        double quietness, wifi;
        double shade, benches, charging, pets, shops, toilet;

        cout << "Enter your username: ";
        getline(cin >> ws, username);

        cout << "Write a comment: ";
        getline(cin >> ws, comment);

        cout << "Rate quietness (0-5): ";
        cin >> quietness;

        cout << "Rate wifi quality (0-5): ";
        cin >> wifi;

        cout << "Rate shade availability (0-5): ";
        cin >> shade;

        cout << "Rate benches availability (0-5): ";
        cin >> benches;

        cout << "Rate charging availability (0-5): ";
        cin >> charging;

        cout << "Rate pet friendliness (0-5): ";
        cin >> pets;

        cout << "Rate nearby shops (0-5): ";
        cin >> shops;

        cout << "Rate public toilet availability (0-5): ";
        cin >> toilet;

        OutdoorPlaceReview review(
            username,
            quietness,
            wifi,
            comment,
            shade,
            benches,
            charging,
            pets,
            shops,
            toilet);

        PlaceSerializer::addReviewToJSON(allPlacesNames[id - 1], review);
        cout << "\n--- Review for " << allPlacesNames[id - 1] << " is added !-- -\n ";
    }
}

void makePlaceUnavailable()
{
    int placeType;
    cout << "Which type of place will make unavailable?\n1. IndoorPlace\n2. OutdoorPlace\nChoose 1 or 2: ";
    cin >> placeType;

    if (placeType == 1)
    {
        auto indoorPlaces = PlaceDeserializer::loadIndoorPlaces();
        auto allPlacesNames = getAllPlaceNames(indoorPlaces);
        cout << "\n--- Existing Indoor Places ---\n";

        for (int i = 0; i < allPlacesNames.size(); i++)
        {
            cout << i + 1 << ". " << allPlacesNames[i] << "; ";
        }
        cout << endl;
        int id;
        cout << "Choose a place you want to make unavailable: ";
        cin >> id;

        IndoorPlace selectedPlace = indoorPlaces[id - 1];
        markNotAvailable(selectedPlace);
        PlaceSerializer::updatePlaceAvailability(selectedPlace);
        cout << "Place is unavailable now!";
    }
    else if (placeType == 2)
    {
        auto outdoorPlaces = PlaceDeserializer::loadOutdoorPlaces();
        auto allPlacesNames = getAllPlaceNames(outdoorPlaces);
        cout << "\n--- Existing Outdoor Places ---\n";

        for (int i = 0; i < allPlacesNames.size(); i++)
        {
            cout << i + 1 << ". " << allPlacesNames[i] << "; ";
        }
        cout << endl;
        int id;
        cout << "Choose a place you want to make unavailable: ";
        cin >> id;

        OutdoorPlace selectedPlace = outdoorPlaces[id - 1];
        markNotAvailable(selectedPlace);
        PlaceSerializer::updatePlaceAvailability(selectedPlace);
        cout << "Place is unavailable now!";
    }
}

void whichIsCloser()
{
    int placeType;
    cout << "Which type of places will you compare?\n1. IndoorPlaces\n2. OutdoorPlaces\nChoose 1 or 2: ";
    cin >> placeType;

    if (placeType == 1)
    {
        auto indoorPlaces = PlaceDeserializer::loadIndoorPlaces();
        auto allPlacesNames = getAllPlaceNames(indoorPlaces);
        cout << "\n--- Existing Indoor Places ---\n";

        for (int i = 0; i < allPlacesNames.size(); i++)
        {
            cout << i + 1 << ". " << allPlacesNames[i] << "; ";
        }

        cout << endl;
        int firstId;
        cout << "Choose first id: ";
        cin >> firstId;

        cout << endl;
        int secondId;
        cout << "Choose second id: ";
        cin >> secondId;
        double latitude, longitude;
        cout << "Enter your latitude: ";
        cin >> latitude;
        cout << "Enter your longitude: ";
        cin >> longitude;

        IndoorPlace selectedPlace1 = indoorPlaces[firstId - 1];
        IndoorPlace selectedPlace2 = indoorPlaces[secondId - 1];

        IndoorPlace closerPlace = closerTo(selectedPlace1, selectedPlace2, latitude, longitude);

        cout
            << closerPlace.getName()
            << " is closer to you";
    }
    else if (placeType == 2)
    {
        auto outdoorPlaces = PlaceDeserializer::loadOutdoorPlaces();
        auto allPlacesNames = getAllPlaceNames(outdoorPlaces);
        cout << "\n--- Existing Outdoor Places ---\n";

        for (int i = 0; i < allPlacesNames.size(); i++)
        {
            cout << i + 1 << ". " << allPlacesNames[i] << "; ";
        }
        cout << endl;
        int firstId;
        cout << "Choose first id: ";
        cin >> firstId;

        cout << endl;
        int secondId;
        cout << "Choose second id: ";
        cin >> secondId;
        double latitude, longitude;
        cout << "Enter your latitude: ";
        cin >> latitude;
        cout << "Enter your longitude: ";
        cin >> longitude;

        OutdoorPlace selectedPlace1 = outdoorPlaces[firstId - 1];
        OutdoorPlace selectedPlace2 = outdoorPlaces[secondId - 1];

        OutdoorPlace closerPlace = closerTo(selectedPlace1, selectedPlace2, latitude, longitude);

        cout
            << closerPlace.getName()
            << " is closer to you";
    }
}

void findPlace()
{
    double latitude, longitude;
    cout << "Enter your latitude: ";
    cin >> latitude;
    cout << "Enter your longitude: ";
    cin >> longitude;

    int placeType;
    cout << "Which type of place do you want?\n1. IndoorPlace\n2. OutdoorPlace\nChoose 1 or 2: ";
    cin >> placeType;

    int numPlaces;
    cout << "How many places do you want to see? ";
    cin >> numPlaces;

    cout << "\nYou chose:\n";
    cout << "Place type: " << (placeType == 1 ? "IndoorPlace" : "OutdoorPlace") << endl;
    cout << "Number of places to display: " << numPlaces << endl;
    if (placeType == 1)
    {
        auto indoorPlaces = PlaceDeserializer::loadIndoorPlaces();
        auto closestIndoor = findClosestPlaces(indoorPlaces, latitude, longitude, numPlaces);
        cout << "Your Latitude: " << latitude << ", Longitude: " << longitude << endl;
        cout << "\n--- Closest Indoor Places ---\n"
             << endl;
        for (auto &p : closestIndoor)
        {
            cout << p;
        }
    }
    else if (placeType == 2)
    {
        auto outdoorPlaces = PlaceDeserializer::loadOutdoorPlaces();
        auto closestOutdoor = findClosestPlaces(outdoorPlaces, latitude, longitude, numPlaces);
        cout << "Your Latitude: " << latitude << ", Longitude: " << longitude << endl;
        cout << "\n--- Closest Outdoor Places ---\n"
             << endl;
        for (auto &p : closestOutdoor)
        {
            cout << p;
        }
    }
}