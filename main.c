#include <stdio.h> 
#include <stdlib.h> 

int main(int argc, char *argv[]){
	
	FILE * fileP;
    long size;
    char * buffer;
    size_t final;

    fileP= fopen ( "foo.txt" , "rb" );
    if (fileP==NULL) {fputs ("File error",stderr); 
    exit (1);
    }

    // calculating file size
    fseek (fileP, 0 , SEEK_END);
    size = ftell (fileP);
    rewind (fileP);

    // allocating mem for file
    buffer = (char*) malloc (sizeof(char)*size);
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

    // copying file into buffer
    final = fread (buffer,1,size,fileP);
    if (final != size) 
    {
        fputs ("Reading error",stderr); 
        exit (3);
    }
    // the whole file is now loaded in the memory buffer. 

    fclose (fileP);
    //free (buffer);
    //return 0;
	
	
	
	printf("size %ld %lu",size,size);
	
	FILE *f_dst = fopen("OK.txt", "wb");
	if(f_dst == NULL)
	{
		printf("ERROR - Failed to open file for writing\n");
		exit(1);
	}

	// Write Buffer
	if(fwrite(buffer, 1, size, f_dst) != size)
	{
		printf("ERROR - Failed to write %i bytes to file\n", size);
		exit(1);
	}

	// Close File
	fclose(f_dst);
	f_dst = NULL;
	
	
	return 0;
}
