#include <iostream>
#include <cmath>
using namespace std;

// Function to calculate kick distance
double calculateKickDistance(double power, double angle) {
    const double gravity = 9.8; // Acceleration due to gravity (m/s^2)
    double radianAngle = angle * M_PI / 180.0; // Convert angle to radians

    // Using physics formula: distance = (v^2 * sin(2 * angle)) / g
    double distance = (pow(power, 2) * sin(2 * radianAngle)) / gravity;
    return distance;
}

int main() {
    double power, angle;

    cout << "Welcome to the Rugby Kick Distance Calculator!" << endl;
    cout << "Enter the kick power (m/s): ";
    cin >> power;
    cout << "Enter the kick angle (degrees): ";
    cin >> angle;

    // Validate input
    if (power <= 0 || angle < 0 || angle > 90) {
        cout << "Invalid input. Power must be positive and angle between 0 and 90 degrees." << endl;
        return 1;
    }

    // Calculate the distance
    double distance = calculateKickDistance(power, angle);

    cout << "The ball will travel approximately " << distance << " meters." << endl;
    return 0;
}
