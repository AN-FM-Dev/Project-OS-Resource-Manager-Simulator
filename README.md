# OS Resource Manager & Simulator

A C-based Operating Systems project that demonstrates process management
and selected OS concepts through Linux/POSIX system calls and
educational simulation components.

## Project Overview

The project is organized into four main parts:

1.  **Process Management** --- creating and managing processes.
2.  **IPC & Synchronization** --- inter-process communication and
    synchronization mechanisms.
3.  **Resource Management** --- managing and simulating system
    resources.
4.  **Integration & Testing** --- bringing the components together and
    testing the application.

The repository currently contains the implementation of **Phase 1:
Process Management**.

## Current Implementation: Phase 1

Phase 1 demonstrates a controller process that creates worker processes,
starts a separate worker executable, waits for the workers to finish,
and records their results.

The implementation uses:

-   `fork()` to create child processes.
-   `execl()` (from the `exec` family) to run the worker program in each
    child process.
-   `waitpid()` to wait for child processes and collect their
    termination status.
-   `getpid()` and `getppid()` to display process and parent process
    IDs.

Each worker prints its ID, PID, and parent PID, performs a short
demonstration task, and exits. The controller records each worker's PID,
state, and exit code.

A worker that exits with code `0` is recorded as `TERMINATED`. A worker
that exits with a non-zero code, or does not exit normally, is recorded
as `FAILED`.

## Requirements

To build and run the current project, you need:

-   A Linux environment.
-   GCC (or a compatible C compiler).
-   GNU Make.

The project uses standard C and POSIX/Linux process APIs. No additional
third-party libraries are required for the current Phase 1
implementation.

## Project Structure

``` text
OS-Resource-Manager/
├── include/
│   └── process_manager.h
├── src/
│   ├── main.c
│   ├── process_manager.c
│   └── worker.c
├── bin/                  # Generated executables; not committed
├── Makefile
└── .gitignore
```

### File Responsibilities

  -----------------------------------------------------------------------
  File                                Responsibility
  ----------------------------------- -----------------------------------
  `src/main.c`                        Entry point and controller flow.
                                      Initializes the process manager,
                                      creates workers, waits for
                                      completion, and displays the
                                      process table.

  `src/process_manager.c`             Implements worker creation, process
                                      tracking, waiting, and result
                                      display.

  `include/process_manager.h`         Defines the process state, process
                                      information structure, and process
                                      manager function declarations.

  `src/worker.c`                      Worker executable launched by child
                                      processes. Displays process
                                      information and runs the
                                      demonstration task.

  `Makefile`                          Builds the worker and controller
                                      executables.

  `.gitignore`                        Excludes generated files in `bin/`
                                      from Git.
  -----------------------------------------------------------------------

## Build and Run

Run the following commands from the project root directory.

### 1. Build

``` bash
make
```

This creates:

-   `bin/worker` --- the worker executable.
-   `bin/os_manager` --- the main OS Resource Manager executable.

### 2. Run

``` bash
./bin/os_manager
```

The controller creates three worker processes, waits for them to finish,
and prints a process table containing each worker's ID, PID, state, and
exit code.

The order in which workers print their completion messages may vary.
This is expected because the child processes execute concurrently.

### 3. Clean Build Files

To remove the generated executables:

``` bash
make clean
```

To rebuild after cleaning:

``` bash
make
```

## Example Output

The process IDs and the order of worker messages will differ between
runs. A typical run looks like this:

``` text
OS Resource Manager
Phase 1: Process Management

Creating Worker Processes...
[Worker 1] Started | PID: 3014 | Parent PID: 3013
[Worker 2] Started | PID: 3015 | Parent PID: 3013
[Worker 3] Started | PID: 3016 | Parent PID: 3013
[Worker 2] Task completed
[Worker 1] Task completed
[Worker 3] Task completed

========== PROCESS TABLE ==========
ID         PID        STATE           EXIT CODE
1          3014       TERMINATED      0
2          3015       TERMINATED      0
3          3016       TERMINATED      0
===================================
```

## Notes

-   Run `./bin/os_manager` from the repository root because the
    controller launches the worker using the relative path
    `./bin/worker`.
-   The `bin/` directory contains generated executables and is excluded
    from version control. Build the executables locally with `make`.
-   The current implementation creates three workers in `src/main.c`.
