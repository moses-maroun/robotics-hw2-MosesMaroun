#include "mobile_robot.hpp"
#include <stdexcept>
#include <iostream>
#include <chrono>
 
MobileRobot::MobileRobot(const std::string& id, const std::string& name,
                          int battery, double speed)
    : Robot(id, name, battery), speed_(speed) {
}


std::string MobileRobot::type() const {
    return "MobileRobot";
}