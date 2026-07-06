#include "robot.hpp"
#include "task.hpp"
#include <algorithm>
 
Robot::Robot(const std::string& id, const std::string& name, int battery)
    : id_(id), name_(name), battery_(battery), status_("idle") {
    // Guard clauses instead of nested ifs
    if (battery_ < 0) battery_ = 0;
    if (battery_ > 100) battery_ = 100;
}
 
void Robot::charge() {
    battery_ = 100;
    status_ = "charging";
}
 
std::string Robot::id() const { return id_; }
std::string Robot::name() const { return name_; }
int Robot::battery() const { return battery_; }
std::string Robot::status() const { return status_; }
 
bool Robot::operator==(const Robot& other) const {
    return id_ == other.id_;
}
 
std::string Robot::operator+(const Robot& other) const {
    return name_ + " + " + other.name_;
}
 
// friend because operator<< must be a free function: the left-hand
// operand of << is std::ostream (std::cout), not a Robot. A member
// function would require "robot << os" syntax, which is backwards.
// friend lets this free function still reach protected members.
std::ostream& operator<<(std::ostream& os, const Robot& r) {
    os << "[" << r.id_ << "] " << r.name_
       << " (" << r.type() << ") battery=" << r.battery_
       << "% status=" << r.status_;
    return os;
}