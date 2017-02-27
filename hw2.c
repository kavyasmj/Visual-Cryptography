/******************************************************************************/
/* Program Name: hw2.c
 * Author: Kavyashree Mysore Jagadeesh (mysoreja@usc.edu)
 * Description: main program to run homework2
 * COntains logic for command line validation, handlign different inputs
 * and calling encrypt,stream,merge and decrypt programs
  */
/******************************************************************************/
// headers
#include "stream.h"
#include "encrypt.h"
#include "merge.h"
#include "decrypt.h"
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <openssl/md5.h>

// method declarations
// get program name for showing usage information
void print_usage(){
	// if invalid command
        fprintf(stderr, "Malformed command\n");
        fprintf(stderr,"usage1:./hw2 stream -p=pphrase -l=len\n" );
        fprintf(stderr,"usage2:./hw2 encrypt -p=pphrase -out=name [pbmfile]\n" );
        fprintf(stderr,"usage3:./hw2 merge pbmfile1 pbmfile2\n" );
        fprintf(stderr,"usage4:./hw2 decrypt [pbmfile]\n" );
        exit(1);
}

// check if file is a directory or if invalid
void check_file(char* filename){
	struct stat s;
	if( stat(filename,&s) == 0 )
	{
	    if( s.st_mode & S_IFDIR ) // check if it is directory
	    {
	    	//input file is a directory
	        fprintf(stderr, "input file: %s is a directory\n",filename);
		    exit(1);
	    }
	}
	//open input file
	FILE *file = fopen( filename, "r" );
	/* fopen on failure */
	if ( file == NULL )
	{
	    fprintf(stderr, "input file: %s ",filename); // error opening file
	    perror("");
        exit(1);
	}
	else
    	fclose( file ); //close after checking
}

//execution starts here
int main(int argc, char* argv[]){

	char* pphrase = NULL;
	char* plen = NULL;
	char* out = NULL;

	//command line validations
	if ( argc < 2 || argc > 5){
		print_usage();
	}

	// if executing command stream // TO DO cmd line options can come in any order
	if(strcmp(argv[1], "stream") == 0 ){ 
		if (argc == 4 && argv[2][0] == '-' && argv[2][1] == 'p' && argv[2][2] == '=' 
			&& argv[3][0] == '-' && argv[3][1] == 'l' && argv[3][2] == '=')
		{
			// get command options
			pphrase = malloc((strlen(argv[2])-3)*sizeof(pphrase)); 
			strncpy(pphrase, argv[2]+3, (strlen(argv[2])-3));
			plen = malloc((strlen(argv[3])-3)*sizeof(plen));
			strncpy(plen, argv[3]+3, (strlen(argv[3])-3));
			int len = atoi(plen);
			stream(pphrase,len,0,NULL);
		} 
		else{ //usage for specific command
			fprintf(stderr, "Malformed command\n");
	        fprintf(stderr,"usage:./hw2 stream -p=pphrase -l=len\n" );
	        exit(1);
		}	
	}
	// if executing command encrypt
	else if(strcmp(argv[1], "encrypt") == 0){
		if (argc > 3 && argc < 6 && argv[2][0] == '-' && argv[2][1] == 'p' && argv[2][2] == '=' 
			&& argv[3][0] == '-' && argv[3][1] == 'o'  && argv[3][2] == 'u' && argv[3][3] == 't' 
			&& argv[3][4] == '=') // get command options
		{
			pphrase = malloc((strlen(argv[2])-3)*sizeof(pphrase));
			strncpy(pphrase, argv[2]+3, (strlen(argv[2])-3));
			
			out = malloc((strlen(argv[3])-5)*sizeof(out));
			strncpy(out, argv[3]+5, (strlen(argv[3])-5));
			
			// handle input from stdin
			if (argc == 5){
				check_file(argv[4]);
				encrypt(pphrase,out,argv[4]);
			}
			else
				encrypt(pphrase,out,NULL);
		}
		else{ //usage for specific command
			fprintf(stderr, "Malformed command\n");
       	    fprintf(stderr,"usage:./hw2 encrypt -p=pphrase -out=name [pbmfile]\n" );
       	    exit(1);
		}
	}

		// if executing command merge
	else if(strcmp(argv[1], "merge") == 0 ){
		if (argc == 4){
			check_file(argv[2]); // get command options
			check_file(argv[3]);
			merge(argv[2],argv[3]);
		}
		else{ //usage for specific command
			fprintf(stderr, "Malformed command\n");
       	    fprintf(stderr,"usage:./hw2 merge pbmfile1 pbmfile2\n" );
       	    exit(1);
		}
	}
		// if executing command decrypt
	else if(strcmp(argv[1], "decrypt") == 0 ){
		if (argc == 3){ // get command options
			check_file(argv[2]);
	        decrypt(argv[2]);
		}
		else if (argc == 2)
			decrypt(NULL);
		else{ //usage for specific command
			fprintf(stderr, "Malformed command\n");
       	    fprintf(stderr,"usage4:./hw2 decrypt [pbmfile]\n" );
       	    exit(1);
		}
	}
	else{ // usage for all commands
		print_usage();
	}

	return 0;
}