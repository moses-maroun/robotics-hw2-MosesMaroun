#include "fleet.hpp"
#include <stdexcept>
#include <algorithm>
#include <iostream>
 
void Fleet::add(std::shared_ptr<Robot> robot) {
    if (!robot) return; // guard clause
    robots_[robot->id()] = robot;
}
 
void Fleet::remove(const std::string& id) {
    robots_.erase(id);
}