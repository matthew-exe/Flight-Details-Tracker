#pragma once

#include "Aircraft.h"

class Aeroplane : public Aircraft
{
public:
    Aeroplane(std::string callsign, std::string type, int level = 0, int speed = 0, int heading = 0, bool landed = true, bool gearState = true);

    std::string getAircraftType() const override { return "Aeroplane"; }

    void outputDetails() const override;

    void land() override;

    void gearup() override;

    void geardown() override;

private:
    bool gearState;
};
