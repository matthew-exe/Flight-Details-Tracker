#include "Aircraft.h"

#include <iostream>

Aircraft::Aircraft(std::string callsign, std::string type, int level, int speed, int heading, bool landed, bool crashed)
    : callsign(callsign), type(type), level(level), speed(speed), heading(heading), landed(landed), crashed(crashed)
{
    if (0 < level)
    {
        this->landed = false;
    }
}

void Aircraft::outputDetails() const
{
    if (crashed)
    {
        std::cout << "This aircraft has crashed and will be unresponsive to commands!\n";
    }

    std::cout << "Callsign: " << callsign << "\n";
    std::cout << "Type: " << type << "\n";
    std::cout << "Level: " << level << "\n";
    std::cout << "Heading: " << heading << "\n";
    std::cout << "Speed: " << speed << "\n";
    std::cout << "Landed state: " << (landed ? "Landed" : "Airborne") << "\n";
}

void Aircraft::land()
{
    if (crashed) return;

    landed = true;
    level = 0;
    speed = 0;
    std::cout << "Aircraft " << callsign << " landed succesfully.\n";
}

void Aircraft::takeoff(int newLevel, int newSpeed)
{
    if (crashed) return;

    landed = false;
    level = newLevel;
    speed = newSpeed;
    std::cout << "Aircraft " << callsign << " has taken off with a level of " << level << " and a speed of " << speed << ".\n";
}


void Aircraft::crash()
{
    crashed = true;
    std::cout << "Aircraft " << callsign << " has CRASHED!\n";
}

bool Aircraft::isCrashed() const
{
    if (crashed)
    {
        std::cout << "Aircraft " << callsign << " is crashed so cannot recieve commands!\n";
        return true;
    }
    else
    {
        return false;
    }
}

void Aircraft::gearup() 
{ 
    if (isCrashed()) return;

    std::cout << getAircraftType() << "s do not have gears!\n"; 
}

void Aircraft::geardown() 
{ 
    if (isCrashed()) return;

    std::cout << getAircraftType() << "s do not have gears!\n"; 
}

void Aircraft::hover() 
{ 
    if (isCrashed()) return;

    std::cout << getAircraftType() << "s cannot hover!\n"; 
}

void Aircraft::unhover() 
{ 
    if (isCrashed()) return;
    
    std::cout << getAircraftType() << "s cannot hover!\n"; 
}

void Aircraft::setLevel(int newLevel) 
{ 
    if (isCrashed()) return;

    std::cout << "Updated " << callsign << "'s level from " << level << " to " << newLevel << ".\n";

    level = newLevel; 
}

void Aircraft::setSpeed(int newSpeed) 
{ 
    if (isCrashed()) return;

    std::cout << "Updated " << callsign << "'s speed from " << speed << " to " << newSpeed << ".\n";

    speed = newSpeed; 
}

void Aircraft::setHeading(int newHeading) 
{ 
    if (isCrashed()) return;

    std::cout << "Updated " << callsign << "'s heading from " << heading << " to " << newHeading << ".\n";

    heading = newHeading; 
}
