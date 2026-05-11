/*
    SWEG3106 - Operating Systems
    Assignment II - DINING PHILOSOPHERS SYNCHRONIZATION PROBLEM IMPLEMENTATION
   USING MONITOR CONCEPT (with C++11 Concurrency Features)

    Submitted to: Mr. Abdi Mulatu
    Date: 21/04/2026
    Section: D  |  Group: 2

    Group Members:
    1. SOLIYANA WASIYHUN      ETS 1304/16
    2. THOMAS ADDISU          ETS 1350/16
    3. TINSAE ZEGEYE          ETS 1359/16
    4. YEABSIRA TAYE          ETS 1439/16
    5. YEISRAEL DAWIT         ETS 1446/16
*/

#include <chrono>
#include <condition_variable>
#include <functional> // Required for std::ref
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

// ========================================================
// State machine for philosopher lifecycle
// ========================================================
enum class State { THINKING, HUNGRY, EATING };

// ========================================================
// Monitor Class: DiningTable
// This class demonstrates the MONITOR synchronization concept
// to solve the Dining Philosophers Problem.
// It ensures deadlock-free execution and mutual exclusion
// using mutex and condition variables (C++11 features).
// ========================================================
class DiningTable {
private:
  int N;                // Number of philosophers
  vector<State> states; // Current state of each philosopher
  vector<unique_ptr<condition_variable>>
      conds;         // Per-philosopher condition variables
  mutex table_mutex; // Global monitor lock

  // Circular table adjacency helpers
  int left(int i) { return (i + N - 1) % N; }
  int right(int i) { return (i + 1) % N; }

  // Core test function - checks whether philosopher can safely eat
  void test(int i) {
    if (states[i] == State::HUNGRY && states[left(i)] != State::EATING &&
        states[right(i)] != State::EATING) {

      states[i] = State::EATING;
      cout << "[SIM] Philosopher " << i + 1 << " is now EATING.\n";
      conds[i]->notify_one();
    }
  }

public:
  // Constructor: Initializes the monitor with given number of philosophers
  DiningTable(int num_philosophers)
      : N(num_philosophers), states(num_philosophers, State::THINKING) {

    for (int i = 0; i < N; ++i) {
      conds.push_back(make_unique<condition_variable>());
    }
  }

  // Acquire both forks (Left and Right)
  void pickup_forks(int i) {
    unique_lock<mutex> lock(table_mutex);
    states[i] = State::HUNGRY;
    cout << "[SIM] Philosopher " << i + 1 << " is HUNGRY.\n";

    test(i); // Attempt to acquire resources

    // Wait until both neighboring forks are available
    while (states[i] != State::EATING) {
      conds[i]->wait(lock);
    }
  }

  // Release both forks and notify neighbors
  void putdown_forks(int i) {
    unique_lock<mutex> lock(table_mutex);

    states[i] = State::THINKING;
    cout << "[SIM] Philosopher " << i + 1 << " returned to THINKING.\n";

    // Check if neighbors can now eat
    test(left(i));
    test(right(i));
  }
};

// ========================================================
// Philosopher Thread Routine
// Each philosopher follows the cycle: Think → Hungry → Eat → Repeat
// ========================================================
void philosopher_routine(int id, DiningTable &table) {
  while (true) {
    this_thread::sleep_for(chrono::seconds(1)); // Thinking phase
    table.pickup_forks(id);                     // Request for forks
    this_thread::sleep_for(chrono::seconds(1)); // Eating phase
    table.putdown_forks(id);                    // Release forks
  }
}

// ========================================================
// Main Function
// ========================================================
int main() {
  int num_philosophers;

  cout << "====================================================\n";
  cout << "   DINING PHILOSOPHERS SYNCHRONIZATION PROBLEM\n";
  cout << "        IMPLEMENTATION USING MONITOR CONCEPT\n";
  cout << "====================================================\n\n";

  cout << "Enter the number of concurrent nodes (e.g., 5): ";
  if (!(cin >> num_philosophers) || num_philosophers < 2) {
    cout << "Invalid input. Defaulting to 5 nodes.\n";
    num_philosophers = 5;
  }

  DiningTable table(num_philosophers); // Create the Monitor
  vector<thread> philosophers;

  cout << "\nBootstrapping thread pool for " << num_philosophers
       << " philosophers...\n\n";

  // Create and launch philosopher threads
  for (int i = 0; i < num_philosophers; ++i) {
    philosophers.emplace_back(philosopher_routine, i, ref(table));
  }

  // Keep main thread alive until program is terminated
  for (auto &t : philosophers) {
    t.join();
  }

  return 0;
}