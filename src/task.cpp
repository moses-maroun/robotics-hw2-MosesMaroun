#include "task.hpp"
 
// Higher priority should come out first from the priority_queue.
// priority_queue is a max-heap, so operator< must say "this is less
// important than other" when this->priority is lower.
bool Task::operator<(const Task& other) const {
    return priority < other.priority;
}

 