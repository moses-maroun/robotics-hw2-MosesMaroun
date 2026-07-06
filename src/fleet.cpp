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

void Fleet::assign_task(const std::string& robot_id, const Task& t) {
    auto robot = find(robot_id); // throws before anything is mutated
    Task assigned = t;
    assigned.assigned_to = robot_id;
    tasks_.push(assigned);
    robot->work(); // marks robot as busy/working via its own work() call
}