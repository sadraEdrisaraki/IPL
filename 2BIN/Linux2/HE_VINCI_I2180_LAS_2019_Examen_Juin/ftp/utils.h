#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checkCond(bool cond, char* msg);

void checkNeg(int res, char* msg);

void checkNull(void* res, char* msg);

pid_t fork_and_run(void (*run)(char*), char * arg0);


//POST: The function "waitpid" is called with the parameters:
//      <pid>, <wstatus>, and <options>.
//      If an error occurs, the calling process is abruptly terminated. 
//RES:  The process ID of the terminated child
pid_t swaitpid(pid_t pid, int *wstatus, int options);


//*****************************************************************************
// FILE
//*****************************************************************************

int sopen(char* path, int flag, int mode);

void swrite(int fd, void* buff, int size);

int sread(int fd, void* buff, int size);

void sclose(int fd);


#endif