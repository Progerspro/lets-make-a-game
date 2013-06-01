#pragma once
#include "velocity.h"
#include "coord.h"
#include <string>

struct Body
{
    std::string name;
    double mass;
    double radius;
    Coord coord;
    Velocity velocity;
};
