#ifndef _CHECK_H_
#define _CHECK_H_

#include <stdbool.h>


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

#endif