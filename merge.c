/******************************************************************************/
/* Program Name: merge.c
 * Author: Kavyashree Mysore Jagadeesh (mysoreja@usc.edu)
 * Description: merges given 2 pbfiles into 1 pbmfile and outputs it
 */
/******************************************************************************/
// headers
#include "merge.h"

//method declarations
void merge( char* pbmfile1, char* pbmfile2){

	// for the 2 pbm files, fd and buffers to store information
	FILE *file1,*file2 = NULL;
	char buf1[1024] = {0};  
	char buf2[1024] = {0};
	char one_char_buf[1];

	//for width and height of pbm files
	long width = 0;
	long height = 0;
	long width2 = 0;
	long height2 = 0;

	int i = 0;
	char *endptr = NULL;

	char new_width[10] = {0};
	char new_height[10] = {0};
	char line2[20] = {0};
	char* out_buf1 = NULL;

	//open both the files
	file1 = fopen(pbmfile1, "rb" );
	file2 = fopen(pbmfile2, "rb" );

	//check if file 1 is P4 format\n
	fread(buf1, 1, 3, file1 );
	if(strcmp((const char*)buf1, "P4\n") != 0){
		fprintf(stderr,"1.pbm is not p4 format\n" );
		exit(1);
	}

	//check if file 2 is P4 format\n
	fread(buf2, 1, 3, file2 );
	if(strcmp((const char*)buf2, "P4\n") != 0){
		fprintf(stderr,"2.pbm is not p4 format\n" );
		exit(1);
	}

	//get width and height of file1
	while(one_char_buf[0] != '\n'){
		fread(one_char_buf, 1, 1, file1 );
		buf1[i++] = one_char_buf[0];

		if (one_char_buf[0] == ' ')
		{
			width = strtol((const char*)buf1, &endptr, 10);
			if (strcmp((const char*)buf1, endptr) == 0){
				exit(1);
			}
			memset(buf1, 0, 1024); //empty the buffer
			i = 0;
		}
	}
	endptr = NULL;
	height = strtol((const char*)buf1, &endptr, 10); // convert string to integer
	if (strcmp((const char*)buf1, endptr) == 0)
		exit(1);
	memset(buf1, 0, 1024); //empty the buffer

	i=0;
	one_char_buf[0] = 0;
	endptr = NULL;
	//get width and height file2
	while(one_char_buf[0] != '\n'){
		fread(one_char_buf, 1, 1, file2 );
		buf2[i++] = one_char_buf[0];

		if (one_char_buf[0] == ' ')
		{
			width2 = strtol((const char*)buf2, &endptr, 10); // convert string to integer
			if (strcmp((const char*)buf2, endptr) == 0){
				exit(1);
			}
			memset(buf2, 0, 1024); //empty the buffer
			i = 0;
		}
	}
	endptr = NULL;
	height2 = strtol((const char*)buf2, &endptr, 10);
	if (strcmp((const char*)buf2, endptr) == 0)
		exit(1);
	memset(buf2, 0, 1024); //empty the buffer


	// check if both files have same width and height for merge
	if (width != width2 || height != height2)
	{
		fprintf(stderr,"both files have different width and heights\n" );
		exit(1);
	}
	//determine bytes to follow
	int bytes_to_follow = 0;
	if (width % 8 == 0)
	{
		bytes_to_follow = (width/8)*height;
	}
	else{
		bytes_to_follow = ((width/8)+1)*height;
	}

	// write first 2 lines into the merged file, that it P4 format and the height & width
	sprintf(new_width, "%ld", width); //convert integer to string
	sprintf(new_height, "%ld", height);
	strcat(line2,new_width);
	strcat(line2," ");
	strcat(line2,new_height);
	strcat(line2,"\n");

	// create space for buffer in heap
	out_buf1 = malloc((bytes_to_follow+5+strlen(new_height)+strlen(new_width))
	 * sizeof(out_buf1)); 

	strcat(out_buf1,"P4\n");
	strcat(out_buf1,line2);
    one_char_buf[0] = 0;
	//start processing files, bit by bit
    while (fread(buf1, 1, 1, file1) != 0) {
    	fread(buf2, 1, 1, file2);
    	one_char_buf[0] = (buf1[0] | buf2[0]); 
    	// black +transparent, transp + transp = black, transp+transp = transp
    	strncat(out_buf1,one_char_buf, 1); // save in output buffer
    }
    //stdout the buffer
    fwrite(out_buf1, 1, (bytes_to_follow+5+strlen(new_height)+strlen(new_width)), stdout);
    free(out_buf1); // free allocated memory
	fclose(file1);	// close both files
	fclose(file2);
}