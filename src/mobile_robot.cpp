#include "mobile_robot.hpp"
#include <stdexcept>
#include <iostream>
#include <chrono>
 
MobileRobot::MobileRobot(const std::string& id, const std::string& name,
                          int battery, double speed)
    : Robot(id, name, battery), speed_(speed) {
}

void MobileRobot::work() {
    if (battery_ == 0)
        throw std::runtime_error(name_ + " cannot work: battery is empty");
 
    status_ = "working";
    battery_ -= 20;
    if (battery_ < 0) battery_ = 0;
}


std::string MobileRobot::type() const {
    return "MobileRobot";
}