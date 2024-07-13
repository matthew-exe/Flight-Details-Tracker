
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <memory>

#include "Functions.h"
#include "Aircraft.h"
#include "Aeroplane.h"
#include "Helicopter.h"

void showCommands()
{
    std::cout << "<-------------------------------------------------------->\n";
    std::cout << "|                        COMMANDS                        |\n";
    std::cout << "<-------------------------------------------------------->\n";
    std::cout << "| create <callsign> <type> <level> <heading> <speed>     |\n";
    std::cout << "| Aeroplane Types: A319, A320, B737, C130                |\n";
    std::cout << "| Helicopter Types: B747, C130                           |\n";
    std::cout << "<-------------------------------------------------------->\n";
    std::cout << "| show <callsign>                                        |\n";
    std::cout << "| show all                                               |\n";
    std::cout << "| show all order [ callsign | level | heading | speed ]  |\n";
    std::cout << "<-------------------------------------------------------->\n";
    std::cout << "| level <callsign> <level>                               |\n";
    std::cout << "| heading <callsign> <level>                             |\n";
    std::cout << "| speed <callsign> <level>                               |\n";
    std::cout << "| land <callsign>                                        |\n";
    std::cout << "| takeoff <callsign> <level> <speed>                     |\n";
    std::cout << "<-------------------------------------------------------->\n";
    std::cout << "| HELICOPTER ONLY                                        |\n";
    std::cout << "| hover <callsign>                                       |\n";
    std::cout << "| unhover <callsign>                                     |\n";
    std::cout << "<-------------------------------------------------------->\n";
    std::cout << "| AEROPLANE ONLY                                         |\n";
    std::cout << "| gearup <callsign>                                      |\n";
    std::cout << "| geardown <callsign>                                    |\n";
    std::cout << "<-------------------------------------------------------->\n";
}

bool isNumber(const std::string& s) 
{
    return s.find_first_not_of("0123456789") == std::string::npos;
}

bool isValidType(const std::string& type) 
{
    std::vector<std::string> types = { "A319", "A320", "B737", "B747", "C130", "AH64", "A109" };

    return (std::find(types.begin(), types.end(), type) != types.end());
}

auto findAircraft(const std::vector<std::unique_ptr<Aircraft>>& aircraft, const std::string& callsign)
{
    return std::find_if(aircraft.begin(), aircraft.end(),
        [&callsign](const std::unique_ptr<Aircraft>& a) { return a->getCallsign() == callsign; });
}

bool isNotValidCallsign(const std::vector<std::unique_ptr<Aircraft>>& aircraft, const std::string& callsign)
{
    return (findAircraft(aircraft, callsign) != aircraft.end());
}

bool validateCreate(const std::vector<std::unique_ptr<Aircraft>>& aircraft, const std::string& callsign, const std::string& type, const std::string& level, const std::string& heading, const std::string& speed)
{
    if (callsign.empty() || type.empty() || level.empty() || heading.empty() || speed.empty())
    {
        std::cout << "Please input all the options!\n";
        return false;
    }
    else if (!isNumber(level) || !isNumber(speed) || !isNumber(heading))
    {
        std::cout << "Only numbers are accepted for level, heading, and speed!\n";
        return false;
    }
    else if (!isValidType(type))
    {
        std::cout << "Invalid type! Please choose between A319, A320, B737, B747, C130, AH64, A109\n";
        return false;
    }
    else if (isNotValidCallsign(aircraft, callsign))
    {
        std::cout << "Invalid callsign! An aircraft with the call sign " << callsign << " already exists!\n";
        return false;
    }

    return true;
}

std::unique_ptr<Aircraft> create(const std::string& callsign, const std::string& type, const std::string& level, const std::string& heading, const std::string& speed)
{
    std::unique_ptr<Aircraft> newAircraft;

    if (type == "A319" || type == "A320" || type == "B737" || type == "B747" || type == "C130") 
    {
        newAircraft = std::make_unique<Aeroplane>(callsign, type, std::stoi(level), std::stoi(speed), std::stoi(heading));
    }
    else if (type == "AH64" || type == "A109") 
    {
        newAircraft = std::make_unique<Helicopter>(callsign, type, std::stoi(level), std::stoi(speed), std::stoi(heading));
    }

    std::cout << "<------------------------------------->\n";
    std::cout << "Aircraft Created Successfully\n\n";
    std::cout << "Callsign: " << callsign << "\n";
    std::cout << "Type: " << type << "\n";
    std::cout << "Level: " << level << "\n";
    std::cout << "Heading: " << heading << "\n";
    std::cout << "Speed: " << speed << "\n"; 
    std::cout << "<------------------------------------->\n";

    return newAircraft;
}

void showAircraftDetails(const std::vector<std::unique_ptr<Aircraft>>& aircraft, const std::string& callsign) 
{
    auto it = std::find_if(aircraft.begin(), aircraft.end(),
        [&callsign](const std::unique_ptr<Aircraft>& a) { return a->getCallsign() == callsign; });

    // If aircraft with the callsign is found, print its details
    if (it != aircraft.end()) 
    {
        const Aircraft& a = *(*it); // Dereference the unique_ptr to access Aircraft object
        std::cout << "<------------------------------------->\n";
        a.outputDetails();
        std::cout << "<------------------------------------->\n";
    }
    else 
    {
        std::cout << "Aircraft with callsign " << callsign << " not found.\n";
    }
}

void showAllAircraftDetails(const std::vector<std::unique_ptr<Aircraft>>& aircraft) 
{
    if (!aircraft.empty())
    {
        std::cout << "<------------------------------------->\n";
        for (const auto& aircraft_ptr : aircraft)
        {
            aircraft_ptr->outputDetails();
            std::cout << "<------------------------------------->\n";
        }
    }
    else
    {
        std::cout << "No aircraft found to display!\n";
    }
}

void showAllSortedAircraftDetails(const std::vector<std::unique_ptr<Aircraft>>& aircraft, std::string& sortBy) 
{
    std::vector<Aircraft*> aircraftPointers;
    for (const auto& ptr : aircraft) {
        aircraftPointers.push_back(ptr.get());
    }


    if (sortBy == "CALLSIGN")
    {
        std::sort(aircraftPointers.begin(), aircraftPointers.end(), [](Aircraft* a1, Aircraft* a2) { return a1->getCallsign() < a2->getCallsign(); });
    }
    else if (sortBy == "LEVEL") 
    {
        std::sort(aircraftPointers.begin(), aircraftPointers.end(), [](Aircraft* a1, Aircraft* a2) { return a1->getLevel() < a2->getLevel(); });
    }
    else if (sortBy == "SPEED")
    {
        std::sort(aircraftPointers.begin(), aircraftPointers.end(), [](Aircraft* a1, Aircraft* a2) { return a1->getSpeed() < a2->getSpeed(); });
    }
    else if (sortBy == "HEADING")
    {
        std::sort(aircraftPointers.begin(), aircraftPointers.end(), [](Aircraft* a1, Aircraft* a2) { return a1->getHeading() < a2->getHeading(); });
    }
    else
    {
        std::cout << "Please input a valid sorting method: [ callsign | level | heading | speed ]\n";
        return;
    }

    if (!aircraft.empty())
    {
        std::cout << "<------------------------------------->\n";
        for (const auto aircraft : aircraftPointers) {
            aircraft->outputDetails();
            std::cout << "<------------------------------------->\n";
        }
    }
    else
    {
        std::cout << "No aircraft found to display!\n";
    }
}

void setLevel(const std::vector<std::unique_ptr<Aircraft>>& aircraft, std::string& callsign, std::string& level)
{
    if (empty(level) || empty(callsign))
    {
        std::cout << "You must enter a callsign and a level!\n";
        return;
    }

    if (!isNumber(level))
    {
        std::cout << "The inputted level must be a whole number!\n";
        return;
    }

    auto it = findAircraft(aircraft, callsign);

    // If aircraft with the callsign is found, print its details
    if (it != aircraft.end())
    {
        Aircraft& a = *(*it); // Dereference the unique_ptr to access Aircraft object
        a.setLevel(stoi(level));
    }
    else
    {
        std::cout << "Aircraft with callsign " << callsign << " not found.\n";
    }
}

void setHeading(const std::vector<std::unique_ptr<Aircraft>>& aircraft, std::string& callsign, std::string& heading)
{
    if (empty(heading) || empty(callsign))
    {
        std::cout << "You must enter a callsign and a heading!\n";
        return;
    }

    if (!isNumber(heading))
    {
        std::cout << "The inputted level must be a whole number!\n";
        return;
    }

    auto it = findAircraft(aircraft, callsign);

    // If aircraft with the callsign is found, print its details
    if (it != aircraft.end())
    {
        Aircraft& a = *(*it); // Dereference the unique_ptr to access Aircraft object
        a.setHeading(stoi(heading));
    }
    else
    {
        std::cout << "Aircraft with callsign " << callsign << " not found.\n";
    }
}

void setSpeed(const std::vector<std::unique_ptr<Aircraft>>& aircraft, std::string& callsign, std::string& speed)
{
    if (empty(speed) || empty(callsign))
    {
        std::cout << "You must enter a callsign and a speed!\n";
        return;
    }

    if (!isNumber(speed))
    {
        std::cout << "The inputted speed must be a whole number!\n";
        return;
    }

    auto it = findAircraft(aircraft, callsign);

    // If aircraft with the callsign is found, print its details
    if (it != aircraft.end())
    {
        Aircraft& a = *(*it); // Dereference the unique_ptr to access Aircraft object
        a.setSpeed(stoi(speed));
    }
    else
    {
        std::cout << "Aircraft with callsign " << callsign << " not found.\n";
    }
}

void land(std::vector<std::unique_ptr<Aircraft>>& aircraft, std::string& callsign)
{
    auto it = findAircraft(aircraft, callsign);

    // If aircraft if found try to land it
    if (it != aircraft.end())
    {
        Aircraft& a = *(*it); // Dereference the unique_ptr to access Aircraft 
        a.land();
    }
    else
    {
        std::cout << "Aircraft with callsign " << callsign << " not found.\n";
    }
}

void takeoff(std::vector<std::unique_ptr<Aircraft>>& aircraft, std::string& callsign, std::string level, std::string speed)
{
    if (empty(level) || empty(speed))
    {
        std::cout << "You must enter a level and a speed!\n";
        return;
    }

    if (!isNumber(level) || !isNumber(speed))
    {
        std::cout << "The inputted level and speed must be a whole number!\n";
        return;
    }

    auto it = findAircraft(aircraft, callsign);

    // If aircraft if found take off
    if (it != aircraft.end())
    {
        Aircraft& a = *(*it); // Dereference the unique_ptr to access Aircraft 
        a.takeoff(stoi(level), stoi(speed));
    }
    else
    {
        std::cout << "Aircraft with callsign " << callsign << " not found.\n";
    }
}

void hover(std::vector<std::unique_ptr<Aircraft>>& aircraft, std::string& callsign)
{
    auto it = findAircraft(aircraft, callsign);

    // If aircraft if found try to hover it
    if (it != aircraft.end())
    {
        Aircraft& a = *(*it); // Dereference the unique_ptr to access Aircraft object
        a.hover();
    }
    else
    {
        std::cout << "Aircraft with callsign " << callsign << " not found.\n";
    }
}

void unhover(std::vector<std::unique_ptr<Aircraft>>& aircraft, std::string& callsign)
{
    auto it = findAircraft(aircraft, callsign);

    // If aircraft if found try to unhover it
    if (it != aircraft.end())
    {
        Aircraft& a = *(*it); // Dereference the unique_ptr to access Aircraft object
        a.unhover();
    }
    else
    {
        std::cout << "Aircraft with callsign " << callsign << " not found.\n";
    }
}

void gearup(std::vector<std::unique_ptr<Aircraft>>& aircraft, std::string& callsign)
{
    auto it = findAircraft(aircraft, callsign);

    // If aircraft if found try to hover it
    if (it != aircraft.end())
    {
        Aircraft& a = *(*it); // Dereference the unique_ptr to access Aircraft object
        a.gearup();
    }
    else
    {
        std::cout << "Aircraft with callsign " << callsign << " not found.\n";
    }
}

void geardown(std::vector<std::unique_ptr<Aircraft>>& aircraft, std::string& callsign)
{
    auto it = findAircraft(aircraft, callsign);

    // If aircraft if found try to hover it
    if (it != aircraft.end())
    {
        Aircraft& a = *(*it); // Dereference the unique_ptr to access Aircraft object
        a.geardown();
    }
    else
    {
        std::cout << "Aircraft with callsign " << callsign << " not found.\n";
    }
}
