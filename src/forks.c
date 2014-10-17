#include "apue.h"

static void write_low_char(int fd) {
	for(char i = 'a'; i <= 'z'; ++i) {
		write(fd, &i, sizeof(i)); 
		sleep(1);
	}
}

static void write_up_char(int fd) {
	for(char i = 'A'; i <= 'Z'; ++i) {
		write(fd, &i, sizeof(i));
		sleep(1);
	}
}


/* fork share the same file link */
static void fork_file(const char *filename) {
	int fd = open(filename, O_RDWR|O_CREAT);
	write(fd, "fork\n", 5);
	pid_t pid;
	if((pid=fork()) == 0) {
		write_low_char(fd);
		exit(0);
	}
	write_up_char(fd);
	wait(NULL);
}

static void vfork_file(const char *filename) {
	int fd = open(filename, O_RDWR|O_CREAT);
	write(fd, "vfork\n", 6);
	pid_t pid;
	if((pid=vfork()) == 0) {
		write_low_char(fd);
		exit(0);
	}
	write_up_char(fd);
	wait(NULL);
}

void test_fork() {
	char *filename = "./fork_file";
	printf("%s", filename);
	fork_file(filename);
	vfork_file(filename);
}
