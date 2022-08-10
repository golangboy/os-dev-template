#include "task.h"
#include "console.h"
struct Task task_list[MAX_TASK_NUM];
int curtask_idx = -1;
int first_task = 1;
void task_finish(int task_idx);
extern void pic_eoi();
void start_task(int func, int stack)
{
    asm volatile("cli");
    for (int i = 1; i < MAX_TASK_NUM; i++)
    {
        if (task_list[i].valid == 0)
        {
            task_list[i].valid = 1;
            *((int *)(stack)) = i;
            *((int *)(stack - 4)) = 0;
            *((int *)(stack - 8)) = task_finish;
            task_list[i].esp = stack - 8;
            task_list[i].eip = func;
            task_list[i].eax = 0;
            task_list[i].ebx = 0;
            task_list[i].ecx = 0;
            task_list[i].edx = 0;
            task_list[i].esi = 0;
            task_list[i].edi = 0;
            task_list[i].ebp = 0;
            break;
        }
    }
    asm volatile("sti");
}
void init_task()
{
    for (int i = 0; i < MAX_TASK_NUM; i++)
    {
        task_list[i].valid = 0;
    }
}
void task_finish(int task_idx)
{
    asm volatile("cli");
    task_list[task_idx].valid = 0;
    asm volatile("sti");
    while (1)
        ;
}

void schdule(int esp, int ebp, int edi, int esi, int edx, int ecx, int ebx, int eax, int eip, int cs, int eflags)
{
    asm volatile("cli");
    pic_eoi();
    if (first_task == 1)
    {
        curtask_idx = 0;
        first_task = 0;
        task_list[curtask_idx].valid = 1;
    }
    task_list[curtask_idx].eax = eax;
    task_list[curtask_idx].ebx = ebx;
    task_list[curtask_idx].ecx = ecx;
    task_list[curtask_idx].edx = edx;
    task_list[curtask_idx].esi = esi;
    task_list[curtask_idx].edi = edi;
    task_list[curtask_idx].ebp = ebp;
    task_list[curtask_idx].esp = esp;
    task_list[curtask_idx].eip = eip;
    task_list[curtask_idx].eflags = eflags;
    for (int i = 0, k = 1; i < MAX_TASK_NUM; i++, k++)
    {
        if (task_list[(k + curtask_idx) % MAX_TASK_NUM].valid == 1)
        {
            curtask_idx = (k + curtask_idx) % MAX_TASK_NUM;
            // console_printf("schdule task\n");
            break;
        }
    }
    // console_printf(" %d - %d \n", task_list[0].valid, task_list[1].valid);
    // console_printf("next task:%d\n", curtask_idx);
    switch_task(task_list[curtask_idx].esp, task_list[curtask_idx].eip, task_list[curtask_idx].eax, task_list[curtask_idx].ebx, task_list[curtask_idx].ecx, task_list[curtask_idx].edx, task_list[curtask_idx].esi, task_list[curtask_idx].edi, task_list[curtask_idx].ebp, task_list[curtask_idx].eflags);
    asm volatile("sti");
}
