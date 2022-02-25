#include <linux/unistd.h>
#include <stdio.h>
#include <string.h>

#define YU_CPU 385

int main(int argc, char **argv)
{
    int job;
    int delay;
    char name[4];
    int wait = 0;

    if (argc != 4)
    {
        printf("Insufficient arguments.\n");
        return 1;
    }

    job = atoi(argv[1]);
    delay = atoi(argv[2]);
    strcpy(name, argv[3]);

    sleep(delay);
    printf("\nProcess-%s : I will use CPU by %ds", name, job);
    job *= 10;

	if (job < 0)
	{
		printf("Insufficiend job\n");
		return 1;
	}

    while(job)
    {
        if(syscall(YU_CPU, name, job))
            job--;
        else
            wait++;
        usleep(100000);
    }
    syscall(YU_CPU, name, 0);
	printf("\nProcess-%s : Finished! My total wait time is %ds\n", name, (wait + 5) / 10);
    return 0;
}
