#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "../kernel/top.h"

    void clear_previous_output(int lines) {
        for (int i = 0; i < lines; i++) {
            printf("\033[F\033[K"); // Move cursor up one line and clear the line
        }
    }

void format_cpu_usage(int cpu_usage, char *buffer) {
    if (cpu_usage < 10) {
        buffer[0] = '0';
        buffer[1] = '.';
        buffer[2] = '0';
        buffer[3] = '0' + cpu_usage;
        buffer[4] = '\0';
    } else if (cpu_usage < 100) {
        buffer[0] = '0';
        buffer[1] = '.';
        buffer[2] = '0' + cpu_usage / 10;
        buffer[3] = '0' + cpu_usage % 10;
        buffer[4] = '\0';
    } else if (cpu_usage < 1000) {
        buffer[0] = '0' + cpu_usage / 100;
        buffer[1] = '.';
        int remainder = cpu_usage % 100;
        buffer[2] = '0' + remainder / 10;
        buffer[3] = '0' + remainder % 10;
        buffer[4] = '\0';
    } else {
        buffer[0] = '0' + cpu_usage / 1000;
        int remainder = cpu_usage % 1000;
        buffer[1] = '0' + remainder / 100;
        buffer[2] = '.';
        int remainder1 = remainder % 100;
        buffer[3] = '0' + remainder1 / 10;
        buffer[4] = '0' + remainder1 % 10;
        buffer[5] = '\0';
    }
}

void format_mem_usage(int mem_usage, char *buffer1) {
    if (mem_usage < 10) {
        buffer1[0] = '0';
        buffer1[1] = '.';
        buffer1[2] = '0';
        buffer1[3] = '0' + mem_usage;
        buffer1[4] = '\0';
    } else if (mem_usage < 100) {
        buffer1[0] = '0';
        buffer1[1] = '.';
        buffer1[2] = '0' + mem_usage / 10;
        buffer1[3] = '0' + mem_usage % 10;
        buffer1[4] = '\0';
    } else if (mem_usage < 1000) {
        buffer1[0] = '0' + mem_usage / 100;
        buffer1[1] = '.';
        int remainder = mem_usage % 100;
        buffer1[2] = '0' + remainder / 10;
        buffer1[3] = '0' + remainder % 10;
        buffer1[4] = '\0';
    } else {
        buffer1[0] = '0' + mem_usage / 1000;
        int remainder = mem_usage % 1000;
        buffer1[1] = '0' + remainder / 100;
        buffer1[2] = '.';
        int remainder1 = remainder % 100;
        buffer1[3] = '0' + remainder1 / 10;
        buffer1[4] = '0' + remainder1 % 10;
        buffer1[5] = '\0';
    }
}

    int main(int argc, char *argv[]) {
        struct top_system_struct *top_info = malloc(sizeof(struct top_system_struct));
        char formatted_cpu_usage[6];
        char formatted_mem_usage[6];
        int lines_to_clear = 0;

        while (1) {
            int err = top(top_info);
            if (err != 0) {
                free(top_info);
                return -1;
            }

            if (lines_to_clear > 0) {
                clear_previous_output(lines_to_clear);
            }

            printf("Uptime: %d seconds\n", top_info->uptime);
            printf("running_process: %d \n", top_info->running_process);
            printf("sleeping_process: %d \n", top_info->sleeping_process);
            printf("total_process: %d \n", top_info->total_process);
            printf("Total Memory: %d KB\n", top_info->total_memory / 1024);
            format_mem_usage((top_info->memoty_usage * 10000) / top_info->total_memory, formatted_mem_usage);
            printf("Used Memory: %s %%\n", formatted_mem_usage);
            printf("Free Memory: %d KB\n", top_info->unused / 1024);
            printf("process data:\n");
            printf("name \t PID \t PPID \t state \t\ttime \t cpu %% \t mem %%\n");
            for (int i = 0; i < top_info->total_process; ++i) {
                format_cpu_usage(top_info->p_list[i].cpu_usage, formatted_cpu_usage);
                int argum = (top_info->p_list[i].mem_usage * 10000) / top_info->total_memory;
                format_mem_usage(argum, formatted_mem_usage);
                printf("%s \t %d \t %d \t %s \t %d \t %s \t %s \n",
                       top_info->p_list[i].name, top_info->p_list[i].pid,
                       top_info->p_list[i].ppid, top_info->p_list[i].state,
                       top_info->p_list[i].time,formatted_cpu_usage, formatted_mem_usage );
            }

            // Calculate the number of lines printed
            lines_to_clear = 9 + top_info->total_process; // 9 lines for headers and additional info
            if(top_info->ticktick==1)
                exit(0);
            sleep(10);
        }

    }