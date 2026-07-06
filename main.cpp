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
 