#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "proc.h"
#include "split.h"

/*
 * kernel_proc is the initial process
 * kernel_proc is created by the bootstrap function
 * kernel_proc is created by the following function call
 * kernel_proc = new_proc("kernel_process", 0, 0);
 * kernel_proc has a priority of 0 and will always be the first process in the queue
 */
struct proc *kernel_proc;

/*
 * pid is used to allocate process ids.
 * The pid of kernel_process is 1024
 * pid is incremented as processes are created
 */
int pid = START_PID;

/*
 * state_to_string converts an enum procstate to a printble C string
 */
char *state_to_string(enum procstate ps) {
    switch (ps) {
        case EMBRYO:
            return "EMBRYO";
        case SLEEPING:
            return "SLEEPING";
        case RUNNABLE:
            return "RUNNABLE";
        case RUNNING:
            return "RUNNING";
        case ZOMBIE:
            return "ZOMBIE";
        case UNUSED:
            return "UNUSED";
    }
}

/*
 * find_proc searches the linked list of procs and returns the struct proc with pid
 * find_proc returns NULL is pid is not in the linked list
 */
struct proc *find_proc(int pid) {
    // design and implement this function
    return NULL;
}

/*
 * print_proc prints to stdout a struc proc pointer
 */
void print_proc(struct proc *p) {
    if (p == NULL)
        return;
    printf("pname: %s, pid: %d, ppid: %d, priority: %d, state: %s\n", p->name, p->pid, p->parent->pid, p->priority, state_to_string(p->state));
}

/*
 * print_pid prints to stdout the proc corresponding to pid
 */
void print_pid(int pid) {
    struct proc *p = find_proc(pid);
    if (p != NULL)
        print_proc(p);
    else
        printf("pid: %d not found.\n", pid);
}

/*
 * print_procs prints the entire list of procs
 */
void print_procs() {
    printf("procs in queue:\n");
    struct proc *p = kernel_proc;
    do {
        print_proc(p);
        p = p->next;
    } while (p != NULL);
    printf("\n");
}

/*
 * new_proc constructs a struc proc from the heap and returns a pointer to it
 * new_proc has to malloc a struct context and a struct proc
 * Initializing most struct proc members is straight forward.
 * For kernel_proc, p->parent points to kernel_proc.
 * For other procs, you have to search for p->parent in the list.
 */
struct proc *new_proc(char name[], uint priority, int ppid) {
    // design and implement this function
    return NULL;
}

/*
 * enqueue_proc places a proc properly within the linked list of procs based upon the priority.
 */
bool enqueue_proc(struct proc *p) {
    // design and implement this function
    return true;
}

/*
 * bootstrap is called to initialize the doubly linked list of procs
 */ 
void bootstrap() {
    kernel_proc = new_proc("kernel_process", 0, 0);
    kernel_proc->parent = kernel_proc;
    kernel_proc->state = RUNNABLE;
}

/*
 * kill removes a proc from the double linked list based upon pid
 */
bool kill(int pid) {
    // design and implement this function
    return true;
}

/*
 * get_pid returns the pid corresponding to a process name. 
 * get_pid returns 0 if the process name is not in the doubly linked list
 */
int get_pid(char name[]) {
    // design and implement this function
    return 0;

}

/*
 * fork creates a new process and enqueues it in the doubly linked list
 */
int fork(char name[], int priority, int ppid) {
    if (priority <= 0)
        return 0;
    struct proc *p = new_proc(name, priority, ppid);
    if (p != NULL)
        if (enqueue_proc(p))
            return p->pid;
    return 0;
}
