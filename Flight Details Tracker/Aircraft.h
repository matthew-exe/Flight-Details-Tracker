#pragma once

#include <string>
#include <iostream>

class Aircraft
{
public:
    Aircraft(std::string callsign, std::string type, int level = 0, int speed = 0, int heading = 0, bool landed = true, bool crashed = false);

    virtual ~Aircraft() = default;

    virtual void outputDetails() const;

    virtual void land();

    virtual void takeoff(int newLevel, int newSpeed);

    void crash();

    bool isCrashed() const;

    virtual void gearup();

    virtual void geardown();

    virtual void hover();

    virtual void unhover();

    virtual std::string getAircraftType() const { return "Aircraft"; }

    std::string getCallsign() const { return callsign; }

    std::string getType() const { return type; }

    int getLevel() const { return level; }

    int getSpeed() const { return speed; }

    int getHeading() const { return heading; }

    void setLevel(int newLevel);

    void setSpeed(int newSpeed);

    void setHeading(int newHeading);

private:
    std::string callsign;
    std::string type;
    int level;
    int speed;
    int heading;
    bool landed;
    bool crashed;
};
