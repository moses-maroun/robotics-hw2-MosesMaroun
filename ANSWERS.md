# Answers
 
**1. Why `shared_ptr` in Fleet and not `unique_ptr`? What would break if you switched?**
 
`shared_ptr` allows more than one owner of the same Robot object at once,
with the object only destroyed once every owner has released it. If Fleet
used `unique_ptr`, only Fleet could ever own a Robot — you couldn't also
hold a separate reference to that same robot outside the fleet (e.g. a
local variable in `main` pointing at a robot while it's still stored in the
fleet). Switching to `unique_ptr` would break any code that tries to copy
or share a robot pointer, since `unique_ptr` cannot be copied, only moved.
 
**2. What container did you use for `robots_`? Why — what is its lookup cost?**
 
`std::unordered_map<std::string, std::shared_ptr<Robot>>`. It's a hash map,
so looking up a robot by id is O(1) on average, versus O(n) for a vector
where you'd have to scan every element to find a matching id.
 
**3. What container did you use for the task queue? What data structure is it built on, and why is it the right fit for "highest priority first"?**
 
`std::priority_queue<Task>`. It's built on a binary heap (internally stored
as a vector kept in heap order). `top()` always returns the highest-priority
element in O(1), and `push`/`pop` are O(log n). This matches exactly what
was needed — tasks always come out in highest-priority order without ever
manually sorting the queue.
 
**4. `operator<<` is declared `friend` inside Robot. What does `friend` give it that a regular method does not? Why can it not be a regular member function?**
 
`operator<<` has to be a free function because of the syntax `std::cout <<
robot` — the left-hand operand is `std::cout`, not the Robot. If it were a
member function, the syntax would have to be `robot << std::cout`, which is
backwards from how output streaming normally reads. But as a free function,
it has no automatic access to Robot's protected members. Declaring it
`friend` inside the class grants that one specific function permission to
access protected/private members, without making it an actual member
function.
 
**5. You used `std::find_if` with a lambda. What does that communicate compared to a hand-written loop?**
 
It communicates intent directly — "find the first element matching this
condition" — instead of making the reader parse a manual loop with an
if-check and a break statement to figure out what it's doing. It also
reduces the chance of an off-by-one or forgotten-break bug since the STL
algorithm handles the iteration itself.
 
**6. `work()` throws if battery is 0. Why use an exception rather than returning false or printing an error?**
 
A boolean return value or a printed message can be silently ignored by the
caller — the program would continue as if nothing went wrong. An exception
forces the problem to be handled somewhere up the call stack; if it isn't
caught, the program stops instead of continuing in a broken state. It also
keeps the return type of `work()` as `void`, which matches what a "robot
performs an action" method should look like.
 
**7. An exception is thrown inside `assign_task` when the robot is not found. Is the fleet's state consistent afterwards?**
 
Yes. `assign_task` calls `find(robot_id)` first, and `find` throws before
anything else in `assign_task` runs. Since the task is only pushed onto the
queue after `find` succeeds, a failed lookup never leaves a partially
created task in the queue or a robot in a half-updated state.
 
**8. `start_work` uses a background thread. What did you do with `stop_` and `worker_`, and why?**
 
`worker_` holds the `std::thread` that runs the timed work loop.
`stop_` is an `std::atomic<bool>` flag checked at the start of each loop
iteration inside the thread; setting it to `true` lets the loop end early
instead of running the full duration. It has to be atomic because it's
written from outside the thread and read from inside the thread
concurrently — a plain `bool` isn't guaranteed to be safe to access from two
threads at once.
 
**9. Diamond inheritance**
 
The code does not compile because `MaintenanceRobot` inherits from both
`MobileRobot` and `CookingRobot`, and each of those independently inherits
its own separate copy of `Robot`. That means `MaintenanceRobot` ends up
containing **two full copies of `Robot`** — one through the `MobileRobot`
path and one through the `CookingRobot` path. When you write `m.name_`, the
compiler doesn't know which copy of `name_` you mean, so it's ambiguous and
refuses to compile.
 
C++ solves this with **virtual inheritance**. Declaring the inheritance from
`Robot` as `virtual` in both `MobileRobot` and `CookingRobot` tells the
compiler to share a single common `Robot` subobject between them, instead of
each keeping its own copy:
 
```cpp
class Robot { public: std::string name_ = "base"; };
class MobileRobot      : public virtual Robot {};
class CookingRobot     : public virtual Robot {};
class MaintenanceRobot : public MobileRobot, public CookingRobot {};
 
int main() {
    MaintenanceRobot m;
    std::cout << m.name_;   // now unambiguous — only one Robot subobject exists
}
```
 
With `virtual` inheritance, both `MobileRobot` and `CookingRobot` point to
the same single `Robot` base subobject, so `MaintenanceRobot` only contains
one `name_`, and `m.name_` is no longer ambiguous.
 