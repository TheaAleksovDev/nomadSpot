#include "../include/PlaceDeserializer.h"
#include "../include/PlaceSerializer.h"

#include "../include/Utils.h"
#include "../include/Place.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int role;
    cout << "Would you like to: ";
    cout << "\n1. Find Nearby Place to Work\n2. Change/add data\nChoose 1 or 2: ";

    cin >> role;

    if (role == 1)
    {

        int operation;
        cout << "Would you like to:?\n1. Find closest places\n2. Compare two places and see which is closer to you\nChoose 1 or 2: ";
        cin >> operation;
        if (operation == 1)
        {
            findPlace();
        }
        else if (operation == 2)
        {
            whichIsCloser();
        }
    }
    else if (role == 2)
    {
        int operation;
        cout << "Would you like to:?\n1. Add a new place\n2. Add a review of existing place\n3. Make an existing place unavailable\nChoose 1, 2 or 3: ";
        cin >> operation;
        if (operation == 1)
        {
            addNewPlace();
        }
        else if (operation == 2)
        {
            addReviewToPlace();
        }

        else if (operation == 3)
        {
            makePlaceUnavailable();
        }
    }

    else
    {
        cout << "Invalid role! Please restart the program and choose admin or user." << endl;
    }

    return 0;
}