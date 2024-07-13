#include "Helicopter.h"

#include "iostream"

Helicopter::Helicopter(std::string callsign, std::string type, int level, int speed, int heading, bool landed, bool hovering, int rotorSpeed)
    : Aircraft(callsign, type, level, speed, heading, landed), hovering(hovering), rotorSpeed(speed)
{
}

void Helicopter::outputDetails() const
{
    Aircraft::outputDetails();
    std::cout << "Hovering state: " << (hovering ? "Hovering" : "Not Hovering") << "\n";
    std::cout << "Rotor speed: " << rotorSpeed << "\n";
}

void Helicopter::land()
{
    if (isCrashed()) return;

    Aircraft::land();
    rotorSpeed = 0;
}

void Helicopter::takeoff(int newLevel, int newSpeed)
{
    if (isCrashed()) return;

    Aircraft::takeoff(newLevel, newSpeed);
    rotorSpeed = newSpeed;
}

void Helicopter::hover()
{
    if (isCrashed()) return;

    hovering = true;
    prevSpeed = getSpeed();
    setSpeed(0);
    std::cout << "Helicopter " << getCallsign() << " is now hovering.\n";
}

void Helicopter::unhover()
{
    if (isCrashed()) return;

    hovering = false;
    setSpeed(prevSpeed);
    std::cout << "Helicopter " << getCallsign() << " is no longer hovering with the speed returning to " << getSpeed() << ".\n";
}