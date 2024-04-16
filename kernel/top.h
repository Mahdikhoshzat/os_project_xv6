#include "param.h"

#ifndef XV6_RISCV_TOP_H
#define XV6_RISCV_TOP_H

struct proc_info {
    char name[16];
    int pid;
    int ppid;
    char state[10];
};

struct top_system_struct {
    long uptime;
    int total_process;
    int running_process;
    int sleeping_process;
    struct proc_info p_list[NPROC];
};


#endif //XV6_RISCV_TOP_H
