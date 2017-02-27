/******************************************************************************/
/* Program Name: stream.c
 * Author: Kavyashree Mysore Jagadeesh (mysoreja@usc.edu)
 * Description: Generates simple stream cipher based on given passphrase and length
 */
/******************************************************************************/
// headers
#include "stream.h"

//method declarations
void stream(char* pphrase, int len_limit, int call, unsigned char* out_buf){


    // most of the code in this function is taken from http://merlot.usc.edu/cs531-s17/homeworks/hw2/#stream and enhanced
    unsigned char md5_buf[MD5_DIGEST_LENGTH];

    int len=strlen(pphrase)+2+MD5_DIGEST_LENGTH;
    char *s=malloc(len+1);
    int i=0;

    //initial 16 bytes
    MD5((const unsigned char *)pphrase, strlen(pphrase), md5_buf);

    unsigned char* ptr = out_buf;

    int k = 0;
    while(k < len_limit){ // generate based on length
        sprintf(&s[MD5_DIGEST_LENGTH], "%02d%s", i, pphrase);
        memcpy(s, md5_buf, MD5_DIGEST_LENGTH); // input for next iteration of MD5 
        MD5((const unsigned char *)s, len, md5_buf); // call MD5 func
        k = k + 8;
        if (k > len_limit){
            if (call == 1){ // call = 1, when called from another program and not cmd line
                memcpy(ptr, md5_buf, len_limit%8); // store in out_buf
                ptr += len_limit%8; // increment ptr
            }
            else
                fwrite(md5_buf, 1, len_limit%8, stdout); //write to std out when called from cmd line
        }
        else{
            if (call == 1){ // call = 1, when called from another program and not cmd line
                memcpy(ptr, md5_buf, 8); // store in out_buf
                ptr += 8; // increment ptr
            }
            else
                fwrite(md5_buf, 1, 8, stdout); //write to std out when called from cmd line
        }
        if (++i == 100) i = 0; // the 2 bytes of MD5 digest after input
    }
    free(s);

}
