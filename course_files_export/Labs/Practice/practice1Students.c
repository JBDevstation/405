#include <stdio.h>
#include <string.h>

typedef unsigned int uint;

struct context {
    uint regs[8];
};

enum procstate { UNUSED=0, EMBRYO, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

struct proc {
    uint sz;                     // Size of process memory (bytes)
    enum procstate state;        // Process state
    volatile int pid;            // Process ID
    struct proc *parent;         // Parent process
    struct context *context;     // swtch() here to run process
    char name[16];               // Process name (debugging)
};

void printproc(struct proc p) {
    printf("name: %s, sz: %d, state: %d, &parent: %p\n", p.name, p.sz, p.state, p.parent);
    for (int i = 0; i < 8; i++)
        printf("    context.regs[%d]: %d\n", i, p.context->regs[i]);
}

/*
Implement swapprocs so that it swaps the contents of p1 and p2.
The expected output is the following.
NOTE: &parent will be different since it is an address.
procs p1 and p2 before swapprocs()
  proc p1: name: procp1, sz: 100, state: 1, &parent: 0x7ffeecccdaa8
    context.regs[0]: 1
    context.regs[1]: 2
    context.regs[2]: 3
    context.regs[3]: 4
    context.regs[4]: 5
    context.regs[5]: 6
    context.regs[6]: 7
    context.regs[7]: 8
  proc p2: name: procp2, sz: 200, state: 2, &parent: 0x7ffeecccda78
    context.regs[0]: 8
    context.regs[1]: 7
    context.regs[2]: 6
    context.regs[3]: 5
    context.regs[4]: 4
    context.regs[5]: 3
    context.regs[6]: 2
    context.regs[7]: 1
procs p1 and p2 after swapprocs()
  proc p1: name: procp2, sz: 200, state: 2, &parent: 0x7ffeecccda78
    context.regs[0]: 8
    context.regs[1]: 7
    context.regs[2]: 6
    context.regs[3]: 5
    context.regs[4]: 4
    context.regs[5]: 3
    context.regs[6]: 2
    context.regs[7]: 1
  proc p2: name: procp1, sz: 100, state: 1, &parent: 0x7ffeecccdaa8
    context.regs[0]: 1
    context.regs[1]: 2
    context.regs[2]: 3
    context.regs[3]: 4
    context.regs[4]: 5
    context.regs[5]: 6
    context.regs[6]: 7
    context.regs[7]: 8
 */
void swapprocs(struct proc *p1, struct proc *p2) {
}

int main(int argc, char **argv) {

    struct context p1c = { {1,2,3,4,5,6,7,8} };
    struct context p2c = { {8,7,6,5,4,3,2,1} };

    struct proc parent1;
    struct proc parent2;

    struct proc p1 = {100, EMBRYO, 1, &parent1, &p1c, "procp1"};
    struct proc p2;

    p2.sz = 200;
    p2.state = SLEEPING;
    p2.pid = 2;
    p2.parent = &parent2;
    p2.context = &p2c;
    strcpy(p2.name, "procp2");

    printf("procs p1 and p2 before swapprocs()\n");
    printf("  proc p1: ");
    printproc(p1);
    printf("  proc p2: ");
    printproc(p2);

    swapprocs(&p1, &p2);

    printf("procs p1 and p2 after swapprocs()\n");
    printf("  proc p1: ");
    printproc(p1);
    printf("  proc p2: ");
    printproc(p2);
}
