#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sysinfo.h>
#include <pthread.h>

//Number of processors
#define PROCS get_nprocs_conf()

//Global general purpose iterator
int i;

//High CPU load function
void consume_cpu() {
    for (;;) {}
}

//High CPU load function for the thread
void *consume_cpu_thread(void *threadid) {
    for (;;) {}
}

//Function with high CPU use and memory allocation
void consume_memory() {
    //A thread uses CPU...
    pthread_t thread;
	pthread_create(&thread, NULL, consume_cpu_thread, (void *)1);
    
    //While the process alocates memory
	for (;;) {
		malloc(1024);
		usleep(100);
	}
}

//Returns a double with the CPU percentage used by the children process
double get_cpu_usage(int pid) {    
	char command[50];
	FILE *fp; //Pointer to the file reading returned by popen
	double percentage;

    //Mount the command used to get cpu usage with sprintf()
    //ps -p <PID> -o pcpu | sed 1d | tr -d ' '
	sprintf(command, "%s%d%s", "ps -p ", pid, " -o pcpu | sed 1d | tr -d ' '");
    
	fp = popen(command, "r");

	fscanf(fp, "%lf", &percentage);
	fclose(fp);

	return percentage/PROCS;
}

/*
    Returns a int with the memory used by the children process in kilobytes
    It works just like get_cpu_usage()
*/
int get_memory_usage(int pid) {
	char command[50];
	FILE *fp;
	int memory;

    //pmap <PID> -x | grep total | awk '{print $4}'
	sprintf(command, "%s%d%s", "pmap ", pid, " -x | grep total | awk '{print $4}'");
    
	fp = popen(command, "r");
    
	fscanf(fp, "%d", &memory);
	fclose(fp);

	return memory;
}

int main (int argc, char *argv[], char *envp[]) {

	system("clear");

    //Creates a children process and gets its PID
	int pid = fork();

    //If the PID returned by the fork() function is less than 0, something went wrong on creating the children process and the error message is shown and the program is terminated with code -1
	if (pid < 0) {
		perror ("Error: ");
		exit (-1);
	} else if (pid > 0) {
        //The PID is bigger than 0 if it is not the children proccess
        
		struct sysinfo info;
		sysinfo(&info);

		FILE *logFile, *plotFile; //Pointers to log.txt and plot.txt files
        
		logFile = fopen("log.txt", "w"); //Opening log.txt with write permission
		plotFile = fopen("plot.txt", "w"); //Opening plot.txt with write permission

		printf("PID: %d\n", pid); //PID of the child process
		printf("Processors numbers: %d\n", PROCS);
		printf("Total memory: %lu MB\n\n", ((size_t)info.totalram * (size_t)info.mem_unit)/(1024*1024)); //Total primary memory

		printf("Time\tCPU\tMemory\n");

		for (i = 0; i <= 10; i++) {
			double cpuUsage = get_cpu_usage(pid);
			int memoryUsage = get_memory_usage(pid);

			printf("%ds\t%.2lf%%\t%d kB\n", i, cpuUsage, memoryUsage);

			fprintf(logFile, "%ds\t%.2lf%%\t%d kB\n", i, cpuUsage, memoryUsage); //Writing the data in log.txt
			fprintf(plotFile, "%d %.2lf %d \n", i, cpuUsage, memoryUsage); //Writing the data in plot.txt

			sleep(1);
		}
		//Closing the opened files
		fclose(logFile);
		fclose(plotFile);

		kill(pid, SIGKILL); //Kill the child process
	}
	else {
        //PID is 0 if it is the children proccess
        
		if (strcmp(argv[1], "cpu") == 0) 
			consume_cpu();
		else if (strcmp(argv[1], "cpu-mem") == 0)
			consume_memory();
		
        //Invalid parameter code error
		fprintf(stderr, "Error: %s\n", strerror(22));
		exit(22);
	}

    /* 
        Extra parameter: plot
        It generates, shows and saves the chart with the execution values
    */
	if (argc == 3)
		if (strcmp(argv[2], "plot") == 0 ) {
			printf("\nGenerating chart\n");
			system("julia plot.jl");
	}

	exit(0); /* Terminates the process successfully (code 0) */

}
