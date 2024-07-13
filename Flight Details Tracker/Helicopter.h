#pragma once

#include "Aircraft.h"

class Helicopter : public Aircraft
{
public:
    Helicopter(std::string callsign, std::string type, int level = 0, int speed = 0, int heading = 0, bool landed = true, bool hovering = false, int rotorSpeed = 0);

    std::string getAircraftType() const override { return "Helicopter"; }

    void outputDetails() const override;

    void land() override;

    void takeoff(int newLevel, int newSpeed) override;

    void hover() override;

    void unhover() override;

private:
    bool hovering;
    int rotorSpeed;
    int prevSpeed = 0;
};
