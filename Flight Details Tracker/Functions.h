#pragma once

#include <string>
#include <string>
#include <vector>
#include <memory>
#include "Aircraft.h"

void showCommands();

bool validateCreate(const std::vector<std::unique_ptr<Aircraft>>& aircraft, const std::string& callsign, const std::string& type, const std::string& level, const std::string& heading, const std::string& speed);

std::unique_ptr<Aircraft> create(const std::string& callsign, const std::string& type, const std::string& level, const std::string& heading, const std::string& speed);

void showAircraftDetails(const std::vector<std::unique_ptr<Aircraft>>& aircraft, const std::string& callsign);

void showAllAircraftDetails(const std::vector<std::unique_ptr<Aircraft>>& aircraft);

void showAllSortedAircraftDetails(const std::vector<std::unique_ptr<Aircraft>>& aircraft, std::string& sortBy);

void setLevel(const std::vector<std::unique_ptr<Aircraft>>& aircraft, std::string& callsign, std::string& level);

void setHeading(const std::vector<std::unique_ptr<Aircraft>>& aircraft, std::string& callsign, std::string& heading);

void setSpeed(const std::vector<std::unique_ptr<Aircraft>>& aircraft, std::string& callsign, std::string& speed);

void land(std::vector<std::unique_ptr<Aircraft>>& aircraft, std::string& callsign);

void takeoff(std::vector<std::unique_ptr<Aircraft>>& aircraft, std::string& callsign, std::string level, std::string speed);

void hover(std::vector<std::unique_ptr<Aircraft>>& aircraft, std::string& callsign);

void unhover(std::vector<std::unique_ptr<Aircraft>>& aircraft, std::string& callsign);

void gearup(std::vector<std::unique_ptr<Aircraft>>& aircraft, std::string& callsign);

void geardown(std::vector<std::unique_ptr<Aircraft>>& aircraft, std::string& callsign);