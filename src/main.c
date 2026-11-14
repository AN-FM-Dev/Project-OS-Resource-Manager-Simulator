#include <stdio.h>
#include "process_manager.h"

int main(void) {

    printf("OS Resource Manager\n");
    printf("Phase 1: Process Management\n\n");

    initialize_process_manager();

    printf("Creating Worker Processes...\n");

    for (int i = 1; i <= 3; i++) {
        create_worker(i);
    }

    wait_for_all_processes();

    display_processes();

    return 0;
}
