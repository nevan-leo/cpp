#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <iomanip>
#include <cmath>

using namespace std;

// Function to generate a random double between min and max
inline double randomDouble(double min, double max) {
    return min + static_cast<double>(rand()) / RAND_MAX * (max - min);
}

// Function to calculate the effect of wind on the kick distance
double calculateWindEffect(double distance, double windSpeed, double windAngle) {
    // Convert wind angle to radians
    double radianAngle = windAngle * M_PI / 180.0;

    // Wind effect components (simplified model)
    double windFactor = windSpeed * cos(radianAngle); // Headwind or tailwind

    // Adjust distance based on wind factor
    return distance + windFactor * 0.1 * distance; // 10% adjustment for wind effect
}

// Function to calculate the kick distance
double calculateKickDistance(double power, double angle, double windSpeed, double windAngle) {
    const double gravity = 9.8; // Acceleration due to gravity (m/s^2)

    // Convert angle to radians
    double radianAngle = angle * M_PI / 180.0;

    // Calculate initial distance without wind
    double distance = (pow(power, 2) * sin(2 * radianAngle)) / gravity;

    // Adjust for wind effect
    distance = calculateWindEffect(distance, windSpeed, windAngle);

    return distance;
}


int main() {
    srand(static_cast<unsigned int>(time(0)));

    double power, angle;

    while (true) {
        // Input kick parameters
        cout << "Welcome to the Rugby Kick Calculator with Wind Variance!\n";
        cout << "Enter the kick power (m/s): ";
        cin >> power;
        cout << "Enter the kick angle (degrees): ";
        cin >> angle;

        // Validate input
        if (power > 0 && angle >= 0 && angle <= 90) {
            break;
        } else {
            cout << "Invalid input. Power must be positive and angle must be between 0 and 90 degrees. Please try again.\n";
        }
    }
    // Generate random wind conditions with a maximum of 10 m/s
    double windSpeed = randomDouble(0.0, 10.0); // Wind speed in m/s (max 10 m/s)
    double windAngle = randomDouble(0.0, 360.0); // Wind angle in degrees (0 = tailwind, 180 = headwind)

    cout << fixed << setprecision(2);
    cout << "Wind conditions: \n";
    cout << "  Speed: " << windSpeed << " m/s\n";
    cout << "  Angle: " << windAngle << " degrees\n";

    // Calculate and display the kick distance
    double distance = calculateKickDistance(power, angle, windSpeed, windAngle);

    cout << "The ball will travel approximately " << distance << " meters." << endl;

    return 0;
}
