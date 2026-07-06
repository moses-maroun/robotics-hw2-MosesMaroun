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

std::shared_ptr<Robot> Fleet::find(const std::string& id) const {
    auto it = robots_.find(id);
    if (it == robots_.end())
        throw std::runtime_error("Robot not found: " + id);
    return it->second;
}