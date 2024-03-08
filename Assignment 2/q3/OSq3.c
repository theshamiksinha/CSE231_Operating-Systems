#include <linux/sched/signal.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

MODULE_AUTHOR("Shamik Sinha & Vansh Yadav");

MODULE_DESCRIPTION("LKM to count the number of currently running processes.");

MODULE_VERSION("1");

static int __init countRunning_start(void)
{

    struct task_struct *process_info;
    //struct thread_info *process_info;
    //->cpu == current_cpu

    int runCount = 0;

    printk(KERN_INFO "Custom Module Loading...\n");
    
    for_each_process(process_info){

        //if (process_info->state == TASK_RUNNING){
        //if (process_info->task->state == TASK_RUNNING){
        //if (process_info->cpu == current_cpu) {
        //if (process_info->thread_info.status == TASK_RUNNING) {
            
        if (task_is_running(process_info)){
        
            runCount++;
        }

    }

    printk(KERN_INFO "There are currently %d tasks running in the system.\n", runCount);

    return 0;
}

static void __exit countRunning_end(void)
{
    printk(KERN_INFO "Custom Module Unloading...\n");
}


module_init(countRunning_start);
module_exit(countRunning_end);