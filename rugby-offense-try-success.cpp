#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
#include <iomanip>

using namespace std;

struct Player {
    string position;
    double weight; // in kg
    double tackleTechnique; // 0 to 1 scale
    double speed; // in m/s
    bool isLastDefender;
};

struct Runner {
    string position;
    double weight; // in kg
    double speed; // in m/s
    double offenseStat; // 0 to 1 scale, improves chances
};

// Function to generate a random double between min and max
double randomDouble(double min, double max) {
    return min + static_cast<double>(rand()) / RAND_MAX * (max - min);
}

// Function to generate the rugby team
vector<Player> generateTeam() {
    vector<Player> team;
    vector<string> forwards = {"Prop", "Hooker", "Lock", "Flanker", "Number 8"};
    vector<string> backs = {"Scrum-Half", "Fly-Half", "Inside Centre", "Outside Centre", "Wing", "Fullback"};

    // Generate forwards (weights above 90kg)
    for (int i = 0; i < 10; ++i) {
        Player forward;
        forward.position = forwards[i % forwards.size()];
        forward.weight = randomDouble(90.0, 130.0);
        forward.tackleTechnique = randomDouble(0.45, 0.95);
        forward.speed = randomDouble(5.1, 8.5);
        forward.isLastDefender = false;
        team.push_back(forward);
    }

    // Generate backs (weights between 70kg and 100kg)
    for (int i = 0; i < 4; ++i) {
        Player back;
        back.position = backs[i % (backs.size() - 1)]; // Exclude "Fullback" for now
        back.weight = randomDouble(70.0, 100.0);
        back.tackleTechnique = randomDouble(0.65, 1.0);
        back.speed = randomDouble(7.0, 10.0);
        back.isLastDefender = false;
        team.push_back(back);
    }

    // Add the Fullback as the last defender
    Player fullback;
    fullback.position = "Fullback";
    fullback.weight = randomDouble(70.0, 100.0);
    fullback.tackleTechnique = randomDouble(0.8, 1.0);
    fullback.speed = randomDouble(8.0, 10.0);
    fullback.isLastDefender = true;
    team.push_back(fullback);

    // Shuffle the team to randomize positions on the field
// ...
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(team.begin(), team.end(), g);


    return team;
}
// Function to simulate the try path
int simulateTryPath(const vector<Player>& team, const Runner& runner) {
    int attempts = 0;
    bool success = false;

    while (!success) {
        attempts++;
        int defendersToFace = rand() % 3 + 2; // Randomize 2 to 4 defenders before the fullback
        int defendersFaced = 0;

        cout << "\nAttempt " << attempts << "\n";
        cout << "Runner Stats:\n";
        cout << fixed << setprecision(2)
             << "Position: " << runner.position
             << ", Weight: " << runner.weight << " kg"
             << ", Speed: " << runner.speed << " m/s"
             << ", Offense: " << runner.offenseStat << "\n\n";

        cout << "Simulating try path...\n";

        for (const auto& player : team) {
            if (player.isLastDefender) {
                cout << "Facing the Fullback: " << player.position << "\n";
                cout << fixed << setprecision(2)
                     << "Defender Stats - Weight: " << player.weight << " kg, Speed: " << player.speed << " m/s, Tackle Technique: " << player.tackleTechnique << "\n";
                double successProbability = (runner.speed - player.speed) / 10.0 + runner.weight / player.weight - player.tackleTechnique + runner.offenseStat;
                cout << "Probability of success: " << successProbability * 100 << "%\n";
                if (randomDouble(0.0, 1.0) > successProbability) {
                    cout << "Tackled by the Fullback! No try scored." << endl;
                    success = false;
                    break;
                } else {
                    cout << "Successfully passed the Fullback! TRY!!!" << endl;
                    success = true;
                    break;
                }
            }

            if (defendersFaced < defendersToFace) {
                cout << "Facing defender: " << player.position << "\n";
                cout << fixed << setprecision(2)
                     << "Defender Stats - Weight: " << player.weight << " kg, Speed: " << player.speed << " m/s, Tackle Technique: " << player.tackleTechnique << "\n";
                double successProbability = (runner.speed - player.speed) / 10.0 + runner.weight / player.weight - player.tackleTechnique + runner.offenseStat;
                cout << "Probability of success: " << successProbability * 100 << "%\n";
                if (randomDouble(0.0, 1.0) > successProbability) {
                    cout << "Tackled by " << player.position << "! No try scored." << endl;
                    success = false;
                    break;
                } else {
                    cout << "Successfully passed " << player.position << "!\n";
                    defendersFaced++;
                }
            }
        }
    }

    return attempts;
}

// Function to display the team
void displayTeam(const vector<Player>& team) {
    cout << "Rugby Team Roster:\n";
    for (const auto& player : team) {
        cout << fixed << setprecision(2)
             << "Position: " << player.position
             << ", Weight: " << player.weight << " kg"
             << ", Tackle Technique: " << player.tackleTechnique
             << ", Speed: " << player.speed << " m/s"
             << (player.isLastDefender ? " (Last Defender)" : "") << endl;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    // Generate and display the rugby team
    vector<Player> team = generateTeam();
    displayTeam(team);

    // Generate the runner
    Runner runner;
    runner.position = "Winger";
    runner.weight = randomDouble(75.0, 90.0);
    runner.speed = randomDouble(8.0, 11.0);
    runner.offenseStat = randomDouble(0.1, 0.75); // Higher offense stat improves chances

    // Simulate the try path and count attempts
    int attempts = simulateTryPath(team, runner);
    cout << "\nTotal attempts to score a try: " << attempts << endl;

    return 0;
}
