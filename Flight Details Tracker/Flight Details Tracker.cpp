// Flight Details Tracker.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <memory>

#include "Functions.h"
#include "Aircraft.h"
#include "Aeroplane.h"
#include "Helicopter.h"

int main()
{
    std::vector<std::unique_ptr<Aircraft>> aircraft;

    showCommands();

    while (true) 
    {
        std::string input;
        std::cout << "Enter your command choice or \"quit\" to exit: ";
        std::getline(std::cin, input);


        for (auto& c : input)
        {
            c = toupper(c);
        }

        // Split the input string into a vector of strings
        std::vector<std::string> command;
        std::istringstream iss(input);

        while (iss >> input) 
        {
            command.push_back(input);
        }

        // Check the size of the user input compared to the maximum ammount of command inputs, needs changing to be more optimal
        if (command.size() < 7) command.resize(7);

        // Find command that has been ran

        if (command.at(0) == "CREATE" && empty(command.at(6)))
        {
            // <callsign> <aircraft type> <level> <heading> <speed>
            if (validateCreate(aircraft, command.at(1), command.at(2), command.at(3), command.at(4), command.at(5)))
            {
                aircraft.push_back(create(command.at(1), command.at(2), command.at(3), command.at(4), command.at(5)));
            }
        }
        else if (command.at(0) == "SHOW" && command.at(1) == "ALL" && command.at(2) == "ORDER" && empty(command.at(4)))
        {
            // <orderby> [callsign|level|heading|speed]
            showAllSortedAircraftDetails(aircraft, command.at(3));
        }
        else if (command.at(0) == "SHOW" && command.at(1) == "ALL" && empty(command.at(2)))
        {
            // no params
            showAllAircraftDetails(aircraft);
        }
        else if (command.at(0) == "SHOW" && empty(command.at(2)))
        {
            // <callsign> 
            showAircraftDetails(aircraft, command.at(1));
        }
        else if (command.at(0) == "LEVEL" && empty(command.at(3)))
        {
            // <callsign> <level>
            setLevel(aircraft, command.at(1), command.at(2));
        }
        else if (command.at(0) == "HEADING" && empty(command.at(3)))
        {
            // <callsign> <heading>
            setHeading(aircraft, command.at(1), command.at(2));
        }
        else if (command.at(0) == "SPEED" && empty(command.at(3)))
        {
            // <callsign> <heading>
            setSpeed(aircraft, command.at(1), command.at(2));
        }
        else if (command.at(0) == "LAND" && empty(command.at(2)))
        {
            // <callsign>
            land(aircraft, command.at(1));
        }
        else if (command.at(0) == "TAKEOFF" && empty(command.at(4)))
        {
            // <callsign>  <level> < speed>
            takeoff(aircraft, command.at(1), command.at(2), command.at(3));
        }
        else if (command.at(0) == "HOVER" && empty(command.at(2)))
        {
            // <callsign> 
            hover(aircraft, command.at(1));
        }
        else if (command.at(0) == "UNHOVER" && empty(command.at(2)))
        {
            // <callsign>
            unhover(aircraft, command.at(1));
        }
        else if (command.at(0) == "GEARUP" && empty(command.at(2)))
        {
            // <callsign> 
            gearup(aircraft, command.at(1));
        }
        else if (command.at(0) == "GEARDOWN" && empty(command.at(2)))
        {
            // <callsign>
            geardown(aircraft, command.at(1));
        }
        else if (command.at(0) == "HELP" && empty(command.at(1)))
        {
            showCommands();
        }
        else if (command.at(0) == "QUIT" || command.at(0) == "Q")
        {
            // no params
            std::cout << "Exiting!\n";
            break;
        }
        else
        {
            std::cout << "Invalid command! Type \"help\" to see commands\n";
        }
    }
}
