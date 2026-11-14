#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    if (argc != 2)
        return 1;

    int id = atoi(argv[1]);

    printf("[Worker %d] Started | PID: %d | Parent PID: %d\n",
           id, getpid(), getppid());

    sleep(2);

    printf("[Worker %d] Task completed\n", id);

    return 0;
}
