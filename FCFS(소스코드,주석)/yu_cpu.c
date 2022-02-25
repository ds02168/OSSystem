#include <linux/unistd.h>
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/sched.h>


#define IDLE '\0'

typedef struct que {
	pid_t pids;
	int jobs;
}FCFS;

FCFS queue[10];

int front = 0;
int rear = 0;
pid_t now = '\0';

int is_empty(void)
{
	if (front == rear)
		return 1;
	else
		return 0;
}

pid_t pop(void)
{
	if (front == rear)
	{
		printk("queue is empty!\n");
		return '\0';
	}
	return queue[front++].pids;
}

int is_new(pid_t pid)
{
	int i;
	for (i = front; i<rear; i++)
	{
		if (pid == queue[i].pids)
		{
			return 0;
		}
	}
	return 1;
}

void push(pid_t pid, int job)
{
	if (rear == 10)
	{
		printk("queue is full\n");
		return;
	}
	queue[rear].pids = pid;
	queue[rear].jobs = job;
	rear++;

}


asmlinkage int sys_yu_cpu(char name[4], int job)
{
	pid_t pid = current->pid;
	if (now == IDLE)
		now = pid;

	if (now == pid)
	{
		if (job == 0)
		{
			printk("Process finished: %s\n", name);
			if (is_empty())
				now = IDLE;
			else
				now = pop();
		}
		else
			printk("Working: %s\n", name);

		return 1;

	}
	else
	{
		if (is_new(pid))
			push(pid, job);

		printk("Working denied: %s\n", name);

	}

	return 0;
}
EXPORT_SYMBOL_GPL(sys_yu_cpu);