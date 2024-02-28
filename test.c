#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sched.h>

int main() 
{
    pid_t pid = getpid() ;
    printf ( " The parent process has pid %d\n",pid);

    // set to aging scheduler for the current prcoess 

    int child_nice; 
    int parent_nice = 10; // Set nice value to 10 for the parent process
    
    struct sched_param param;
    param.sched_priority = 0; // This is ignores bu CFS 

    // Set scheduler
    if (sched_setscheduler(pid,9, &param) == -1) {
        perror("sched_setscheduler");
        return 1;
    }


    if (setpriority(PRIO_PROCESS, pid, parent_nice) == -1) {
        perror("setpriority");
        return 1;
    }

    printf(" The nice value for task %d before forking is %d\n",pid, getpriority(PRIO_PROCESS,pid));

    // forking a process to test if AGING_SCHEDULER WORKS 
    int new_proc = fork(); // returns

    if (new_proc < 0)
    {
        printf("Fork Error \n");
    }

    else if (new_proc == 0){
        printf("This is the child speaking\n");

        pid_t child_pid = getpid();
        child_nice = getpriority(PRIO_PROCESS,child_pid) ; 

        printf(" The child is %d with nice value %d with parent %d and nice value %d\n", child_pid, child_nice , getppid(), getpriority(PRIO_PROCESS,pid) );
    }

    else
    {

        parent_nice = getpriority(PRIO_PROCESS, pid);
        \\wait(NULL);

        printf("This is the parent speaking\n"); 
        printf(" The child is %d with nice value %d with parent %d and nice value %d\n",new_proc, getpriority(PRIO_PROCESS,new_proc), pid, parent_nice);
    
    return 0;
    }
    
}
