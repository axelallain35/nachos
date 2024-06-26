/*! \file sysdep.h 
   \brief System-dependent interface
  
        Nachos uses the routines defined
  	here, rather than directly calling the UNIX library functions, to
  	simplify porting between versions of UNIX, and even to
  	other systems, such as MSDOS and the Macintosh.

 * -----------------------------------------------------
 * This file is part of the Nachos-RiscV distribution
 * Copyright (c) 2022 University of Rennes 1.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details 
 * (see see <http://www.gnu.org/licenses/>).
 * -----------------------------------------------------

*/


#ifndef SYSDEP_H
#define SYSDEP_H

#include "kernel/copyright.h"

/* Align on a boundary (MUST be a power of 2), so that return value <= val */
#define ALIGN_INF(val,boundary)		\
  (int8_t*)(((unsigned long)val) & (~(((unsigned long)boundary)-1)))

/* Align on a boundary (MUST be a power of 2), so that return value >= val */
#define ALIGN_SUP(val,boundary)			\
  (int8_t*)(((((unsigned long)val)-1) & (~(((unsigned long)boundary)-1))) + ((unsigned long)boundary))

/* Check file to see if there are any characters to be read.
// If no characters in the file, return without waiting.
*/

extern bool PollFile(int fd);

/* File operations: open/read/write/lseek/close, and check for error
// For simulating the disk and the console devices.
*/

extern int OpenForWrite(char *name);
extern int OpenForReadWrite(char *name, bool crashOnError);
extern void Read(int fd, char *buffer, int nBytes);
extern int ReadPartial(int fd, char *buffer, int nBytes);
extern void WriteFile(int fd, char *buffer, int nBytes);
extern void Lseek(int fd, int offset, int whence);
extern int Tell(int fd);
extern void Close(int fd);
extern bool Unlink(char *name);

// Access to sockets

extern int OpenSocket();
extern void CloseSocket(int sockID);
extern void AssignNameToSocket(char *socketName, int sockID);
extern int ReadFromSocket(int sockID, char *buffer, int packetSize);
extern void SendToSocket(int sockID, char *buffer, int packetSize, char *toName);

// Process control: abort, exit, and sleep
extern void Abort();
extern void Exit(int exitCode);
extern void Delay(int seconds);

// Initialize system so that cleanUp routine is called when user hits ctl-C
extern void CallOnUserAbort(VoidNoArgFunctionPtr cleanUp);

// Initialize the pseudo random number generator
extern void RandomInit(unsigned seed);
extern int Random();

/* Allocate, de-allocate an array, such that de-referencing
// just beyond either end of the array will cause an error
*/

extern int8_t*AllocBoundedArray(size_t size);
extern void DeallocBoundedArray(int8_t *p, size_t size);

/* Other C library routines that are used by Nachos.
// These are assumed to be portable, so we don't include a wrapper.
*/
extern "C" {
#include <stdlib.h>  // atoi, atof, abs
#include <stdio.h>   // for printf, fprintf
#include <string.h>  // for DEBUG, etc.
}

#endif // SYSDEP_H
