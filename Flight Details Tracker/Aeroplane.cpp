#include "Aeroplane.h"

#include <iostream>

Aeroplane::Aeroplane(std::string callsign, std::string type, int level, int speed, int heading, bool landed, bool gearState)
    : Aircraft(callsign, type, level, speed, heading, landed), gearState(gearState)
{
    if (0 < level)
    {   
        this->gearState = false;
    }
}

void Aeroplane::outputDetails() const
{
    Aircraft::outputDetails();
    std::cout << "Gear state: " << (gearState ? "Extended" : "Retracted") << "\n";
}

void Aeroplane::land()
{
    if (isCrashed()) return;

    if (gearState)
    {
        Aircraft::land();
    }
    else
    {
        std::cout << "ERROR! GEAR IS NOT EXTENDED!\n";
        Aircraft::crash();
    }
}

void Aeroplane::gearup() 
{ 
    if (isCrashed()) return;

    gearState = false; 
    std::cout << "Aeroplane " << getCallsign() << "'s gear has been retracted successfully.\n";
}

void Aeroplane::geardown()
{
    if (isCrashed()) return;

    gearState = true;
    std::cout << "Aeroplane " << getCallsign() << "'s gear has been extended successfully.\n";
}
