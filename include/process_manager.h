#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <sys/types.h>

#define MAX_PROCESSES 10

//5 States
typedef enum {
    NEW,
    RUNNING,
    WAITING,
    READY,
    TERMINATED
} ProcessState;

//Create New DataType (ProcessInfo)
typedef struct {
    int id;
    pid_t pid;
    ProcessState state;
    unsigned long program_counter;
    int priority;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int memory_size;
    int exit_code;
} ProcessInfo;

//Setting up the Process Manager before we start using it
void initialize_process_manager(void);

//Creating a new Worker Process
int create_worker(int id);

//Waiting for Child Processes to Finish
void wait_for_all_processes(void);

//Display process information
void display_processes(void);

#endif
