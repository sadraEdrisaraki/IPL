#ifndef _FORK_H_
#define _FORK_H_

#include <sys/types.h>

#include <unistd.h>

//POST: A new child process is created by means of the "fork" function.
//      Firstly, it executes the <run> function with <arg0> as a parameter
//      then it exits. The calling process and the child process runs 
//      concurrently. 
//      If an error occurs, the calling process is abruptly terminated. 
//RES:  The pid of the chid process
pid_t fork_and_run(void (*run)(char* ,char *), char * arg0, char *arg1);


pid_t fork_and_run_simple(void (*run)());


//POST: The function "waitpid" is called with the parameters:
//      <pid>, <wstatus>, and <options>.
//      If an error occurs, the calling process is abruptly terminated. 
//RES:  The process ID of the terminated child
pid_t swaitpid(pid_t pid, int *wstatus, int options);
#endif
