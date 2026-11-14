#ifndef PROCESS_MANAGER_H
#define PROCESS_MANAGER_H

#include <sys/types.h>

#define MAX_PROCESSES 10

typedef enum {
    CREATED,
    RUNNING,
    TERMINATED,
    FAILED
} ProcessState;

typedef struct {
    int id;
    pid_t pid;
    ProcessState state;
    int exit_code;
} ProcessInfo;

void initialize_process_manager(void);
int create_worker(int id);
void wait_for_all_processes(void);
void display_processes(void);

#endif
