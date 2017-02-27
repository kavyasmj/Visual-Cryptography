/******************************************************************************/
/* Program Name: decrypt.c
 * Author: Kavyashree Mysore Jagadeesh (mysoreja@usc.edu)
 * Description: decrypts given pbl file or input from stdin and outputs the decrypted file
 */
/******************************************************************************/
// headers
#include "decrypt.h"

//method declarations
void decrypt(char* pbmfile){
	FILE *file = NULL;
	char buf[1024] = {0};  
	char one_char_buf[1];

	if (pbmfile != NULL)
		//open input file
	    file = fopen(pbmfile, "rb" );
	else
   	/*code to handle stdin */
		file = stdin;

	//for width and height of pbm file
	long width = 0;
	long height = 0;

	int i = 0;
	char *endptr = NULL;

	char new_width[10] = {0};
	char new_height[10] = {0};
	char line2[20] = {0};
	char* out_buf = NULL;
	int row_length_bytes =0;
	int row_length_bits =0;

	//check if file 1 is P4 format\n
	fread(buf, 1, 3, file );
	if(strcmp((const char*)buf, "P4\n") != 0){
		fprintf(stderr,"pbm is not p4 format\n" );
		exit(1);
	}

	//get width and height of file1
	while(one_char_buf[0] != '\n'){
		fread(one_char_buf, 1, 1, file );
		buf[i++] = one_char_buf[0];

		if (one_char_buf[0] == ' ')
		{
			width = strtol((const char*)buf, &endptr, 10);
			if (strcmp((const char*)buf, endptr) == 0){
				exit(1);
			}
			memset(buf, 0, 1024); //empty the buffer
			i = 0;
		}
	}
	endptr = NULL;
	height = strtol((const char*)buf, &endptr, 10); // convert string to integer
	if (strcmp((const char*)buf, endptr) == 0)
		exit(1);
	memset(buf, 0, 1024); //empty the buffer

	if (width % 8 == 0){		
		row_length_bits = width;
	}
	else{
		row_length_bits = (((width/8)+1)*8);
	}
	row_length_bytes = row_length_bits/8;

	// write first 2 lines into the output file, that it P4 format and the height & width
	sprintf(new_width, "%ld", (width/2)); //convert integer to string
	sprintf(new_height, "%ld", (height/2));
	strcat(line2,new_width);
	strcat(line2," ");
	strcat(line2,new_height);
	strcat(line2,"\n");

	// create space for buffer in heap
	out_buf = malloc((5+strlen(new_height)+strlen(new_width)) * sizeof(out_buf)); 
	int n = 0;

	strcat(out_buf,"P4\n");
	strcat(out_buf,line2);

	fwrite(out_buf, 1, (5+strlen(new_height)+strlen(new_width)), stdout);
    free(out_buf); // free allocated memory

	one_char_buf[0] = 0;

	//decryption logic - consider only one line out of 2 lines
	// consider 2 bytes, if both are black then output decrypted pixel is black
	// if not then output white pixel
	while (fread(buf, 1, row_length_bytes, file) != 0) {

  		for (n=0; n < row_length_bytes; n++)
  		{
  			one_char_buf[0] = 0;
			one_char_buf[0] = (one_char_buf[0] | ((buf[n] & 0x80) & (buf[n] & 0x40) << 1));
			one_char_buf[0] = (one_char_buf[0] | (((buf[n] & 0x20) << 1) & (buf[n] & 0x10) << 2));
			one_char_buf[0] = (one_char_buf[0] | (((buf[n] & 0x08) << 2) & (buf[n] & 0x04) << 3));
			one_char_buf[0] = (one_char_buf[0] | (((buf[n] & 0x02) << 3) & (buf[n] & 0x01) << 4));
			n++;
			one_char_buf[0] = (one_char_buf[0] | (((buf[n] & 0x80) >> 4) & (buf[n] & 0x40) >> 3));
			one_char_buf[0] = (one_char_buf[0] | (((buf[n] & 0x20) >> 3) & (buf[n] & 0x10) >> 2));
			one_char_buf[0] = (one_char_buf[0] | (((buf[n] & 0x08) >> 2) & (buf[n] & 0x04) >> 1));
			one_char_buf[0] = (one_char_buf[0] | (((buf[n] & 0x02) >> 1) & (buf[n] & 0x01)));

			fwrite(one_char_buf, 1, 1, stdout);
  		}
  		fread(buf, 1, row_length_bytes, file); //skip next row 
	}

	fclose( file );
}
