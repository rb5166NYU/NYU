#include "oslabs.h"
#include <stdio.h>

struct PCB NULLPCB = {0, 0, 0, 0, 0, 0, 0};
/*
- Below this will check if the PCB (process control block) is set to NULL (zero)
- "int test_null_pcb" delcares this is an integer and names the function "test_null_pcb"
- struct PCB specifies that the parameter is of type PCB, which is presumably a structure defined elsewhere in your code (likely in the oslabs.h header file). A structure in C is a user-defined data type that groups related variables.
- inpcb is the name of the variable representing the incoming PCB structure that the function will evaluate.
*/
int test_null_pcb(struct PCB inpcb)
{
	if(inpcb.process_id == 0 &&
	        inpcb.arrival_timestamp == 0 &&
	        inpcb.total_bursttime == 0 &&
	        inpcb.execution_starttime == 0 &&
	        inpcb.execution_endtime == 0 &&
	        inpcb.remaining_bursttime == 0 &&
	        inpcb.process_priority == 0)
		return 1; /* Is null */
	else
		return 0; /* Is not null */


}
/************************************************************************************************


 ************************************************************************************************/
struct PCB handle_process_arrival_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp)
{

	if(test_null_pcb(current_process))
	{	/* There's no current process in ready queue */
		new_process.execution_starttime = timestamp; // new processs execution start time equals current time stamp
		new_process.execution_endtime = timestamp + new_process.total_bursttime; // new processs endtime equals the current time stamp plus the total bursttime(run time)
		new_process.remaining_bursttime = new_process.total_bursttime; // new process remaining run time equals the total run time
		return new_process;
	}
	/* This is saying if the new process has a higher priority than the current process */
	else if (new_process.process_priority >= current_process.process_priority)
	{

		new_process.execution_starttime = 0; // Sets new process start time equal to 0 (meaning it hasen't started yet)
		new_process.execution_endtime = 0; // Sets new process endtime equal to zero (meaning it hasn't finished yet)
		new_process.remaining_bursttime = new_process.total_bursttime; // remaining run time is equal to total run time (meaning it hasn't executed yet)

		/* Saying current process has a higher or equal priority */
		/* ready_queue is creating an array that holds processes ready to execution_endtime
		*queue_cnt is a pointer designated by the *. This gives us a current count of the queue.
		new_process is what we want to add to the queue
		*/
		ready_queue[*queue_cnt] = new_process;
		*queue_cnt += 1; //  increments the value pointed to by queue_cnt by 1
		return current_process;
	}
	else
	{
		current_process.execution_endtime = 0; // resets end time of current process
		current_process.remaining_bursttime -= timestamp - current_process.execution_starttime; // updates remaining run time of current process by subtracting the time it has already executed (from start to current time stamp)
		ready_queue[*queue_cnt] = current_process; // Adds current process back to the ready queue, showing it's not finished and can be scheduled again later
		*queue_cnt += 1; // increments the count of proccesses in ready queue by one
		new_process.execution_starttime = timestamp; // sets start time of new process based on time stamp
		new_process.execution_endtime = timestamp + new_process.total_bursttime; // Calculates the end time for the new process based on current time and total run time
		new_process.remaining_bursttime = new_process.total_bursttime; // initializes the remaining run time to the total run time

		/* Returning new process because the priority is higher */
		return new_process;
	}

}
/***************************************
 PART 2

**************************************/

struct PCB handle_process_completion_pp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp) 
{
    if (*queue_cnt > 0) 
    {
        int top_priority = 0;

        // Find the highest priority process
        for (int i = 1; i < *queue_cnt; i++) 
        {
            if (ready_queue[top_priority].process_priority > ready_queue[i].process_priority) 
            {
                top_priority = i;
            }
        }

        // Retrieve the highest priority PCB
        struct PCB highest_priority = ready_queue[top_priority];

        // Shift the queue to remove the completed process
        for (int i = top_priority; i < *queue_cnt - 1; i++) 
        {
            ready_queue[i] = ready_queue[i + 1];
        }

        // Decrease the queue count
        (*queue_cnt)--;  // Decrement queue count

        // Set execution times
        highest_priority.execution_starttime = timestamp;
        highest_priority.execution_endtime = timestamp + highest_priority.remaining_bursttime;

        return highest_priority;
    }

    return NULLPCB; // Ensure NULLPCB is defined correctly
}

/***************************************************

PART 3

*******************************************************/

struct PCB handle_process_arrival_srtp(struct PCB ready_queue[QUEUEMAX], 
                                         int *queue_cnt, 
                                         struct PCB current_process, 
                                         struct PCB new_process, 
                                         int time_stamp) {
    // Check if there is no currently running process
    if (test_null_pcb(current_process)) {
        // Set the new process as the active one
        new_process.execution_starttime = time_stamp; 
        new_process.execution_endtime = time_stamp + new_process.total_bursttime; 
        new_process.remaining_bursttime = new_process.total_bursttime; 
        return new_process; // New process is now active
    }

    // If the new process has a shorter remaining burst time
    if (new_process.remaining_bursttime < current_process.remaining_bursttime) {
        // Preempt the current process
        // Add current process to the ready queue
        ready_queue[*queue_cnt] = current_process;
        (*queue_cnt)++; // Increment queue count

        // Update the current process state
        current_process.execution_starttime = 0;
        current_process.execution_endtime = 0;
        current_process.remaining_bursttime -= (time_stamp - current_process.execution_starttime);

        // Start the new process
        new_process.execution_starttime = time_stamp; 
        new_process.execution_endtime = time_stamp + new_process.total_bursttime; 
        new_process.remaining_bursttime = new_process.total_bursttime; 

        return new_process; // Return the new process as the active one
    }

    // Current process continues to run
    // Add the new process to the ready queue
    new_process.execution_starttime = 0; 
    new_process.execution_endtime = 0; 
    new_process.remaining_bursttime = new_process.total_bursttime; 

    ready_queue[*queue_cnt] = new_process; // Add new process to the queue
    (*queue_cnt)++; // Increment queue count

    return current_process; // Current process continues
}


/*****************************************************************
PART 4
*****************************************************************/



struct PCB handle_process_completion_srtp(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int timestamp)

{
  if (*queue_cnt > 0)
    {
      int srt = 0;
      for (int i = 1; i < *queue_cnt; i++)
        {
          if (ready_queue[srt].remaining_bursttime > ready_queue[i].remaining_bursttime)
            {
              srt = i;
            }
        }
      //we know the shortest reamining time pcb location, return it
      struct PCB highest_priority = ready_queue[srt];
      //shift all other elements up
      for (int i = srt; i < *queue_cnt; i ++)
        {
          ready_queue[i] = ready_queue[i+1];
        }
      *queue_cnt = *queue_cnt - 1;
      highest_priority.execution_starttime = timestamp;
      highest_priority.execution_endtime = timestamp + highest_priority.remaining_bursttime;
      return highest_priority;
    }
  return NULLPCB;
}

/*****************************************************************
PART 5
*****************************************************************/

struct PCB handle_process_arrival_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, struct PCB current_process, struct PCB new_process, int timestamp, int time_quantum)
{
  if (test_null_pcb(current_process))
    {
      new_process.execution_starttime = timestamp;
      if (new_process.total_bursttime > time_quantum)
        {
          new_process.execution_endtime = timestamp + time_quantum;
        }
      else
        {
          new_process.execution_endtime = timestamp + new_process.total_bursttime;
        }
      new_process.remaining_bursttime = new_process.total_bursttime;
      return new_process;
    }

  //if current process has shortest time
  else
    {
      new_process.execution_starttime = 0;
      new_process.execution_endtime = 0;
      new_process.remaining_bursttime = new_process.total_bursttime;
      ready_queue[*queue_cnt] = new_process;
      *queue_cnt = *queue_cnt + 1;
      return current_process;
    }
}


/*****************************************************************
PART 6
*****************************************************************/
struct PCB handle_process_completion_rr(struct PCB ready_queue[QUEUEMAX], int *queue_cnt, int time_stamp, int time_quantum)
{
  if (*queue_cnt > 0)
    {
      int rr = 0;
      for (int i = 1; i < *queue_cnt; i++)
        {
          if (ready_queue[rr].arrival_timestamp > ready_queue[i].arrival_timestamp)
            {
              rr = i;
            }
        }
      //we know the shortest reamining time pcb location, return it
      struct PCB highest_priority = ready_queue[rr];
      //shift all other elements up
      for (int i = rr; i < *queue_cnt; i ++)
        {
          ready_queue[i] = ready_queue[i+1];
        }
      *queue_cnt = *queue_cnt - 1;
      highest_priority.execution_starttime = time_stamp;
      if (highest_priority.total_bursttime > time_quantum)
        {
          highest_priority.execution_endtime = time_stamp + time_quantum;
        }
      else
        {
          highest_priority.execution_endtime = time_stamp + highest_priority.total_bursttime;
        }
      return highest_priority;
    }
  return NULLPCB;
}
