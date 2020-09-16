#ifndef _FORK_H_
#define _FORK_H_

#include <stdbool.h>

#include <sys/types.h>

//*****************************************************************************
//Fist note to the readers of the specifiactions.
//*****************************************************************************
// All the functions are abruptly stopped when an error occurs. For example, 
// such an error could arrive when an system call is made. Usually, we do not 
// add this notice to the specifications. Nevertheless, it is an implicit part 
// of all the postconditions.
//*****************************************************************************

//*****************************************************************************
//Second note to the readers of the specifiactions.
//*****************************************************************************
// Given a function "type f (arg1, arg2, ..., argn)", a safe function of "f" is 
// a function "sf" which has the same signature and the same specifiction except
// that it is abruptly stopped when an error occurs. Such an error could occur
// when an system call is made. Usually, we do not add this notice to the 
// specifications when a a function is characterized as a safe function.
// Nevertheless, its specification is implicitly defined.
//*****************************************************************************

//*****************************************************************************
// CHECK
//*****************************************************************************

//PRE: msg != NULL
//POST: 1) If the value of "cond" is true, "msg" followed by a message 
//      describing the last error encountered during a call 
//      to a system or library function is produced 
//      on stderr. Moreover, the program is abruptly terminied.
//      2) If the value of  "cond" is false, nothing happens.
void checkCond(bool cond, char* msg);

//PRE: msg != NULL
//POST: 1) If the value of "cond" is less than 0, "msg" followed by a message 
//      describing the last error encountered during a call 
//      to a system or library function is produced 
//      on stderr. Moreover, the program is abruptly terminied.
//      2) If the value of  "cond" is greater or egal to 0, nothing happens.
void checkNeg(int res, char* msg);

//PRE: msg != NULL
//POST: 1) If the value of "res" is NULL, "msg" followed by a message 
//      describing the last error encountered during a call 
//      to a system or library function is produced 
//      on stderr. Moreover, the program is abruptly terminied.
//      2) If the value of  "res" is not NULL, nothing happens.
void checkNull(void* res, char* msg);

//*****************************************************************************
// FORK
//*****************************************************************************

//POST: A new child process is created by means of the "fork" function.
//      Firstly, it executes the <run> function with <arg0> as a parameter
//      then it exits. The calling process and the child process runs 
//      concurrently. 
//      If an error occurs, the calling process is abruptly terminated. 
//RES:  The pid of the chid process
pid_t fork_and_run(void (*run)(void *), void* arg0);


//NOTE: This is a safe version of the "waitpid" system call
pid_t swaitpid(pid_t pid, int *wstatus, int options);

//*****************************************************************************
// IO
//*****************************************************************************
//NOTE: This is a safe version of the "close" system call
int sclose(int fd);

//NOTE: This is a safe version of the "read" system call
ssize_t sread(int fd, void *buf, size_t count);

//NOTE: This is a safe version of the "write" system call
ssize_t swrite(int fd, const void *buf, size_t count);

//PRE "fd" is a valid file desciptor on which something can be written, and
//      "counf" >= 0, and 
//    "buf" points to a memory segment such that the size of this 
//     memory segment is at least "count" bytes.

//POST Exactly "count" bytes from the buffer pointed by "buf" to the file referred 
//     to the file descriptor "fd" is written.
void nwrite(int fd, const void* buf, size_t count);

//*****************************************************************************
// PIPE
//*****************************************************************************
//NOTE: Ths is a safe version of the "pipe" system call
int spipe(int pipefd[2]);
#endif