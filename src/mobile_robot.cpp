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

void MobileRobot::start_work(int seconds) {
    // if a previous worker thread is still joinable, clean it up first
    if (worker_.joinable()) {
        stop_ = true;
        worker_.join();
    }
 
    stop_ = false;
    worker_ = std::thread([this, seconds]() {
        for (int i = 0; i < seconds && !stop_; ++i) {
            try {
                work();
            } catch (const std::runtime_error& e) {
                std::cout << "Error: " << e.what() << "\n";
                break;
            }
            std::cout << *this << "\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });
    worker_.join(); // joined here so main stays simple and predictable
}
 