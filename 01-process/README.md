# Process Experiment: Understanding `fork()` and `exec()` in C++ & Python

This experiment contains two equivalent implementations (one in **C++** and one in **Python**) demonstrating core Unix/Linux systems programming fundamentals: process creation, asynchronous scheduling, memory isolation, and process image replacement.

---

## 📝 Key Concepts & Observations

### 1. Process Concurrency & CPU Scheduling
When running either the C++ binary or the Python script multiple times, the output logs before the "waiting" phase interleave differently. 
* **The Reason:** `fork()` clones the execution into two independent branches (Parent and Child) running concurrently. 
* **The Result:** The Operating System's CPU scheduler handles both processes in parallel. Unless synchronized, the exact order of print/stdout statements is non-deterministic (a race condition).

### 2. The Mechanics of the `pid` Variable
The variable assigned by `fork()` returns different values depending on **which** process memory space is inspecting it:
* **In the Parent Process:** `pid` holds the actual system Process ID of the child. This allows the parent to track its child.
* **In the Child Process:** `pid` is exactly `0`. This is a sentinel value returned by the kernel so the child can programmatically branch into its own logic blocks.
* Despite `pid == 0` evaluating to true inside the child block, calling `getpid()` (C++) or `os.getpid()` (Python) queries the OS kernel directly and returns the child's true, unique system identifier.

### 3. Strict Memory Isolation
* When a process forks, the OS creates a **complete duplicate copy** of the parent's memory address space for the child.
* Modifying a variable (e.g., setting `value = 20` in the child) has **zero effect** on the parent's scope, where `value` remains `30`. The two processes share no memory state.

### 4. Process Synchronization via Waiting
* The parent process explicitly pauses its execution using synchronization functions (`waitpid` / `os.wait`). 
* This forces the parent to block and sleep until the child process terminates, ensuring that the final cleanup logs and post-execution value tracking always run last.

### 5. Overwriting the Image with `execl()`
* The child invokes `execl` to execute the system `/bin/echo` command.
* **Behavior:** `execl` completely replaces the child process's entire memory image, code section, heap, and stack with the `echo` binary. 
* Because `execl` executes successfully, the child process transitions entirely into `echo`. Any lines of code directly below `execl` are wiped out and never reached unless the system call fails.

---

## 🚀 How to Run

Both programs perform the exact same operational steps under the hood.

### C++ Version
Compile and run using a POSIX compiler (Linux or WSL):
```bash
g++ process_experiment.cpp -o process_experiment
./process_experiment
```

### Python Version
Run using Python 3:
```bash
python3 process_experiment.py
```
