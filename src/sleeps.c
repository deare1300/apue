#include "apue.h"

static jmp_buf env_alrm;


/*
 * How to write a sleep function by yourself
 */

// register a signo but do nothing 
static void sig_alrm1(int signo) { 
	
}

static void sig_alrm2(int signo) {
	longjmp(env_alrm, 1);
}

int sleep1(int nsec) {
	if(signal(SIGALRM,sig_alrm1) == SIG_ERR) { 
		quit_err("signal SIG_ALARM register error\n");	
	}
	alarm(nsec); // 1. clear other alarm or 2. if the time is very short(such the sig_int before the pause() the never stop)
	pause(); // 3. it may interrupt by other signal such as SIGINT show below 
	return alarm(0); // alarm(0) remove all the alarm
}

//solve the problem 2 of sleep1 
int sleep2(int nsec) {
	if(signal(SIGALRM, sig_alrm2) == SIG_ERR) {
		quit_err("singal sig_alrm error\n");
	}
	if(setjmp(env_alrm) == 0) {
		alarm(nsec);
		pause();
	}
	return alarm(0);
}

void test_sleep() {
	time_t pre, after;
	if(signal(SIGINT, sig_alrm1) == SIG_ERR) { // register for the problem
		quit_err("signal SIGINT register error\n");
	}
	time(&pre);
	printf("pre  =%s", ctime(&pre));
	sleep2(5);
	time(&after);
	printf("after=%s", ctime(&after)); 
}


