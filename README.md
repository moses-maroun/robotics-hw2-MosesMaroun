# robotics-hw2-MosesMaroun
# Robot Fleet Manager
 
A C++ command-line program that manages a fleet of robots. Robots can work,
charge, and be assigned tasks that are processed in priority order.
 
## What it does
 
- Add/remove robots from a fleet (`Robot` base class, `MobileRobot` subclass)
- Each robot has a battery (clamped 0–100), a status, and can perform `work()`
- Tasks are assigned to robots and stored in a priority queue (highest
  priority comes out first)
- `MobileRobot` supports timed background work using a separate thread
- Bad input and missing robots are handled with exceptions instead of
  crashing the program
## How to compile and run
 
```bash
chmod +x compile.sh
./compile.sh
./fleet_app
```
 
Or manually:
 
```bash
g++ -std=c++17 -Wall -Wextra -pthread src/*.cpp main.cpp -I include -o fleet_app
./fleet_app
```
 
## Problems I ran into
 
1. **Non-numeric menu input caused an infinite loop.** When the user typed a
   letter instead of a number, `std::cin` entered a fail state and kept
   re-reading the same bad input forever, spamming the error message. Fixed
   by calling `std::cin.clear()` and `std::cin.ignore(...)` to reset the
   stream before continuing the loop and by setting the choice again to -1.