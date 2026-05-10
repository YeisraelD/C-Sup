#include <chrono>
#include <condition_variable>
#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

using namespace std;

enum class State { THINKING, HUNGRY, EATING };

// Monitor object: encapsulates synchronization primitives to enforce
// thread-safe state mutations. Eliminates race conditions and prevents circular
// wait deadlocks via strict resource ordering logic.
class DiningTable {
private:
  int N; // Total concurrency limit (node count)

  // Thread-local state cache, mapped by thread ID.
  vector<State> states;

  // Granular CVs (Condition Variables) for zero-spin blocking.
  // Using unique_ptr to bypass copy semantics and manage heap allocations.
  vector<unique_ptr<condition_variable>> conds;

  // Global monitor lock. Serializes all state checks and mutations.
  mutex table_mutex;

  // Modulo arithmetic for O(1) circular adjacency resolution.
  int left(int i) { return (i + N - 1) % N; }
  int right(int i) { return (i + 1) % N; }

  // The core invariant check. Validates if the current thread can safely
  // acquire resources. Must ONLY be called when 'table_mutex' is held.
  void test(int i) {
    // Assert: Thread is HUNGRY. Left and Right neighbors are NOT holding the
    // locks (EATING).
    if (states[i] == State::HUNGRY && states[left(i)] != State::EATING &&
        states[right(i)] != State::EATING) {

      // Atomic state transition. Resources acquired.
      states[i] = State::EATING;
      cout << "[SIM] Philosopher " << i + 1 << " is now EATING.\n";

      // Wake up the specific thread if it was parked in the CV wait queue.
      // notify_one() is sufficient here as each CV maps exactly to one thread.
      conds[i]->notify_one();
    }
  }

public:
  // Bootstraps the monitor. Initializes all nodes to idle (THINKING).
  DiningTable(int num_philosophers)
      : N(num_philosophers), states(num_philosophers, State::THINKING) {
    for (int i = 0; i < N; ++i) {
      conds.push_back(make_unique<condition_variable>());
    }
  }

  // Resource acquisition entry point.
  void pickup_forks(int i) {
    // RAII lock guard. Guarantees mutex release on scope exit or exception.
    unique_lock<mutex> lock(table_mutex);
    states[i] = State::HUNGRY;
    cout << "[SIM] Philosopher " << i + 1 << " is HUNGRY.\n";

    // Attempt greedy acquisition.
    test(i);

    // Spurious wakeup loop. If we didn't get the lock, park the thread.
    // The CV releases 'table_mutex' atomically and puts the thread to sleep,
    // re-acquiring it upon wakeup.
    while (states[i] != State::EATING) {
      conds[i]->wait(lock);
    }
  }

  // Resource release exit point.
  void putdown_forks(int i) {
    // RAII lock guard for state mutation.
    unique_lock<mutex> lock(table_mutex);

    // Release resources.
    states[i] = State::THINKING;
    cout << "[SIM] Philosopher " << i + 1 << " returned to THINKING.\n";

    // Broadcast availability to adjacent nodes.
    // If they were blocked waiting for our resources, this triggers their
    // wakeup sequence.
    test(left(i));
    test(right(i));
  }
};

// Thread payload. Simulates the infinite CPU/IO cycles of the node.
void philosopher_routine(int id, DiningTable &table) {
  while (true) {
    this_thread::sleep_for(
        chrono::seconds(1)); // Simulated IO bound task (THINKING)
    table.pickup_forks(id);  // Blocking resource request
    this_thread::sleep_for(
        chrono::seconds(1)); // Simulated CPU bound task (EATING)
    table.putdown_forks(id); // Resource deallocation
  }
}

int main() {
  int num_philosophers;

  cout << "====================================================\n";
  cout << "   DINING PHILOSOPHERS: KERNEL-LEVEL SYNCHRONIZATION\n";
  cout << "====================================================\n\n";

  cout << "Enter the number of concurrent nodes (e.g., 5): ";
  if (!(cin >> num_philosophers) || num_philosophers < 2) {
    cout << "Invalid input. Defaulting to 5 nodes.\n";
    num_philosophers = 5;
  }

  // Instantiate the Monitor object on the stack.
  DiningTable table(num_philosophers);

  // Thread pool allocation.
  vector<thread> philosophers;

  cout << "\nBootstrapping thread pool for " << num_philosophers
       << " nodes...\n\n";

  // Dispatch threads. Passing the monitor by reference to ensure shared state.
  for (int i = 0; i < num_philosophers; ++i) {
    philosophers.emplace_back(philosopher_routine, i, ref(table));
  }

  for (auto &t : philosophers) {
    t.join();
  }

  return 0;
}
