#include <iostream>
#include "../include/Place.h"
using namespace std;

int main()
{
    Place cafe("Cafe", "My Freedom", 40.7128, -74.0060);
    cafe.print();
    cafe.addReview("Tea", 4.5, 4.0, "Great place to work!");
    cafe.printReviews();
    return 0;
}