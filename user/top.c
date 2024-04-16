#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "../kernel/top.h"

int
main(int argc, char *argv[])
{
    struct top_system_struct *top_info = malloc(sizeof(struct top_system_struct));
    int err = top(top_info);
    if(err != 0){
        return -1;
    }
    printf("Uptime: %d seconds\n", top_info->uptime);
    printf("running_process: %d \n", top_info->running_process);
    printf("sleeping_process: %d \n", top_info->sleeping_process);
    printf("total_process: %d \n", top_info->total_process);
    printf("process data:\n");
    printf("name \t PID \t PPID \t state\n");
    for (int i = 0; i < top_info->total_process; ++i) {
        printf("%s \t %d \t %d \t %s\n",top_info->p_list[i].name, top_info->p_list[i].pid, top_info->p_list[i].ppid, top_info->p_list[i].state);
    }
    exit(0);
}