//
// Created by LENOVO on 7/4/2024.
//

#ifndef XV6_RISCV_KALLOC_H
#define XV6_RISCV_KALLOC_H


typedef struct {
    int total_pages;
} kmemHelp;

extern kmemHelp* kmemHelpSharedStructPtr;


#endif //XV6_RISCV_KALLOC_H
