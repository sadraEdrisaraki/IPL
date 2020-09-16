#ifndef _UTILS_H_
#define _UTILS_H_

#include <signal.h>
#include <stdbool.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

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
//      Firstly, it executes the <run> then it exits. 
//      The calling process and the child process run concurrently. 
//      If an error occurs, the calling process is abruptly terminated. 
//RES:  The pid of the chid process
pid_t fork_and_run0(void (*run)(void));


//POST: A new child process is created by means of the "fork" function.
//      Firstly, it executes the <run> function with <arg0> as a parameter
//      then it exits. The calling process and the child process run 
//      concurrently. 
//      If an error occurs, the calling process is abruptly terminated. 
//RES:  The pid of the chid process
pid_t fork_and_run1(void (*run)(void *), void* arg0);

//POST: A new child process is created by means of the "fork" function.
//      Firstly, it executes the <run> function with <arg0> and <arg1> 
//      as parameterS then it exits. 
//      The calling process and the child process run concurrently. 
//      If an error occurs, the calling process is abruptly terminated. 
//RES:  The pid of the chid process
pid_t fork_and_run2(void (*run)(void *, void *), void* arg0, void* arg1);

//POST: A new child process is created by means of the "fork" function.
//      Firstly, it executes the <run> function with <arg0>, <arg1> and <arg2> 
//      as parameters then it exits. 
//      The calling process and the child process runs concurrently. 
//      If an error occurs, the calling process is abruptly terminated. 
//RES:  The pid of the chid process
pid_t fork_and_run3(void (*run)(void*, void*, void*), void *arg0, void *arg1, void* arg2);

//NOTE: This is a safe version of the "waitpid" system call
pid_t swaitpid(pid_t pid, int *wstatus, int options);


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

//*****************************************************************************
// SIGNAL
//*****************************************************************************

//POST: This function do nothing.
void ehandler(int signum);


//PRE:  signum represents a signal number.

//POST: The action taken by a process on receipt of the <signum> signal
//      is "handler". The <signum> signal mask includes all signals. 
//      Note that no specific options are set.
void ssigaction(int signum, void (*handler)(int));

//NOTE: Ths is a safe version of the "sigemptyset" system call
void ssigemptyset(sigset_t *set);

//NOTE: Ths is a safe version of the "sigfillset" system call
void ssigfillset(sigset_t *set);

//NOTE: Ths is a safe version of the "sigaddset" system call
void ssigaddset(sigset_t *set, int signum);

//NOTE: Ths is a safe version of the "sigdelset" system call
void ssigdelset(sigset_t *set, int signum);

//NOTE: Ths is a safe version of the "sigprocmask" system call
void ssigprocmask(int how, const sigset_t *set, sigset_t *oldset);

//NOTE: Ths is a safe version of the "kill" system call
void skill(pid_t pid, int signum);

//NOTE: Ths is a safe version of the "sigpending" system call
void ssigpending(sigset_t *set);

//******************************************************************************
// SHARED MEMORY
//******************************************************************************
void* init_shm(key_t key, size_t size, int shmflg, int *shm_id);

int sshmdt(const void *shmaddr);

void sshmdelete(int shm_id);

//******************************************************************************
//SEMAPHORES
//******************************************************************************

//cf man semctl
// This function has three or four arguments, depending on cmd.  
// When there are four, the fourth has the type union semun.  
// The  calling program must define this union as follows:
union semun {
   int              val;    /* Value for SETVAL */
   struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
   unsigned short  *array;  /* Array for GETALL, SETALL */
   struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */
};

int ssemget(key_t key, int nsems, int semflg);

void ssem_setval(int sem_id, int sem_num, int val);

void ssem_add(int sem_id, int sem_num, int val);

void sdown(int sem_id, int sem_num);

void sup(int sem_id, int sem_num);

void ssemdelete(int sem_id);
#endif