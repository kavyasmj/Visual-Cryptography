/******************************************************************************/
/* Program Name: stream.h
 * Author: Kavyashree Mysore Jagadeesh (mysoreja@usc.edu)
 * Description: Contains libaries needed to generate simple stream cipher 
 * and source code file's shared method definitions
 */
/******************************************************************************/
// headers
#include <sys/types.h>
#include <openssl/md5.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

 //method definitions
void stream(char*, int,int, unsigned char*);