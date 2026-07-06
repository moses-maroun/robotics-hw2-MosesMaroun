#include "robot.hpp"
#include "mobile_robot.hpp"
#include "fleet.hpp"
#include <iostream>
#include <memory>
#include <limits>
 
void print_menu() {
    std::cout << "\n=== Robot Fleet Manager ===\n"
              << "1. Add robot\n"
              << "2. Remove robot\n"
              << "3. Show all robots\n"
              << "4. Work (single robot)\n"
              << "5. Work all\n"
              << "6. Charge all\n"
              << "7. Assign task to robot\n"
              << "8. Show task queue\n"
              << "9. Start timed work on a robot\n"
              << "0. Exit\n"
              << "Choice: ";
}

int main() {
    Fleet fleet;
    int choice = -1;
    do{
        print_menu();
        if (!(std::cin >> choice)) {
            // guard clause: bad input (e.g. letters) doesn't crash the program
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: invalid input.\n";
            continue;
        }
 
        if (choice == 0) break;
        try {
            if (choice == 1) {
                std::string id, name;
                int battery;
                double speed;
                std::cout << "id name battery speed: ";
                std::cin >> id >> name >> battery >> speed;
 
                if (battery < 0 || battery > 100)
                    throw std::runtime_error("battery must be between 0 and 100");
 
                fleet += std::make_shared<MobileRobot>(id, name, battery, speed);
                std::cout << "Robot added.\n";
 
            } else if (choice == 2) {
                std::string id;
                std::cout << "id to remove: ";
                std::cin >> id;
                fleet -= id;
                std::cout << "Robot removed.\n";
 
            } else if (choice == 3) {
                std::cout << fleet;
 
            } else if (choice == 4) {
                std::string id;
                std::cout << "id to work: ";
                std::cin >> id;
                auto robot = fleet.find(id);
                robot->work();
                std::cout << *robot << "\n";
 
            } else if (choice == 5) {
                fleet.work_all();
 
            } else if (choice == 6) {
                fleet.charge_all();
                std::cout << "All robots charged.\n";
 
            } else if (choice == 7) {
                std::string id, taskName;
                int priority;
                std::cout << "robot id, task name, priority(1-5): ";
                std::cin >> id >> taskName >> priority;
 
                if (priority < 1 || priority > 5)
                    throw std::runtime_error("priority must be between 1 and 5");
 
                Task t{taskName, priority, id};
                fleet.assign_task(id, t);
                std::cout << "Task assigned.\n";
 
            } else if (choice == 8) {
                fleet.show_tasks();
 
            } else if (choice == 9) {
                std::string id;
                int seconds;
                std::cout << "id, seconds: ";
                std::cin >> id >> seconds;
 
                if (seconds < 0)
                    throw std::runtime_error("seconds cannot be negative");
 
                auto robot = fleet.find(id);
                auto mobile = std::dynamic_pointer_cast<MobileRobot>(robot);
                if (!mobile)
                    throw std::runtime_error("robot is not a MobileRobot");
 
                mobile->start_work(seconds);
 
            } else {
                std::cout << "Unknown choice.\n";
            }
        } catch (const std::runtime_error& e) {
            std::cout << "Error: " << e.what() << "\n";
        }

    }while(choice != 0);
    
    return 0;
}