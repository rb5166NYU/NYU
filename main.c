#include "oslabs.h"

/*
- The function setup_pcb initializes a Process Control Block (PCB) structure, which holds information about a process in an operating system.
Parameters:
- struct PCB *inpcb: A pointer to a PCB structure that will be initialized.
- int process_id: The unique identifier for the process.
- int arrival_timestamp: The time when the process arrived in the system.
- int total_bursttime: The total CPU time required by the process.
- int execution_starttime: The time when the process begins execution.
- int execution_endtime: The time when the process finishes execution.
- int remaining_bursttime: The remaining time required for the process to complete.
- int process_priority: The priority level of the process.

Summary
- The setup_pcb function initializes a PCB with specific details of a process, allowing the operating system to manage and schedule it appropriately. Each parameter directly corresponds to a field within the PCB structure, ensuring all relevant process information is captured.

*/

void setup_pcb(struct PCB *inpcb,
    int process_id, int arrival_timestamp, int total_bursttime, int execution_starttime, int execution_endtime, int remaining_bursttime, int process_priority)   
{
    (*inpcb).process_id = process_id;
    (*inpcb).arrival_timestamp = arrival_timestamp;
    (*inpcb).total_bursttime = total_bursttime;
    (*inpcb).execution_starttime = execution_starttime;
    (*inpcb).execution_endtime = execution_endtime;
    (*inpcb).remaining_bursttime = remaining_bursttime;
    (*inpcb).process_priority = process_priority;

}

int main(int argc, char** argv) //allows for command line usage

{
    struct PCB current_process;
    struct PCB new_process;
    struct PCB returned_pcb;
    struct PCB ready_queue[QUEUEMAX];
    int queue_cnt =0;
    setup_pcb(&current_process,1,1,4,1,5,4,8);
    setup_pcb(&new_process,2,2,3,0,0,3,6);
    returned_pcb = handle_process_arrival_pp(ready_queue,&queue_cnt,current_process,new_process,2);
}




