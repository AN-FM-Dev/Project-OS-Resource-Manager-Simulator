#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "process_manager.h"

static ProcessInfo processes[MAX_PROCESSES];
static int process_count = 0;

void initialize_process_manager(void) {
    process_count = 0;
}

int create_worker(int id) {

    if (process_count >= MAX_PROCESSES)
        return -1;

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return -1;
    }

    if (pid == 0) {

        char id_text[20];
        snprintf(id_text, sizeof(id_text), "%d", id);

        execl("./bin/worker", "worker", id_text, NULL);

        perror("exec failed");
        _exit(127);
    }

    processes[process_count].id = id;
    processes[process_count].pid = pid;
    processes[process_count].state = RUNNING;
    processes[process_count].exit_code = -1;

    process_count++;

    return pid;
}

void wait_for_all_processes(void) {

    int completed = 0;

    while (completed < process_count) {

        int status;
        pid_t pid = waitpid(-1, &status, 0);

        if (pid < 0) {
            if (errno == EINTR)
                continue;

            perror("waitpid failed");
            break;
        }

        for (int i = 0; i < process_count; i++) {

            if (processes[i].pid == pid) {

                if (WIFEXITED(status)) {
	 	    processes[i].exit_code = WEXITSTATUS(status);
    		    processes[i].state = processes[i].exit_code == 0 ? TERMINATED : FAILED;
		}
		else {
    		    processes[i].state = FAILED;
		}

                completed++;
                break;
            }
        }
    }
}

void display_processes(void) {

    printf("\n========== PROCESS TABLE ==========\n");

    printf("%-10s %-10s %-15s %-10s\n",
           "ID", "PID", "STATE", "EXIT CODE");

    for (int i = 0; i < process_count; i++) {

        char *state;

        switch (processes[i].state) {

            case CREATED:
                state = "CREATED";
                break;

            case RUNNING:
                state = "RUNNING";
                break;

            case TERMINATED:
                state = "TERMINATED";
                break;

            default:
                state = "FAILED";
        }

        printf("%-10d %-10d %-15s %-10d\n",
               processes[i].id,
               processes[i].pid,
               state,
               processes[i].exit_code);
    }

    printf("===================================\n");
}
