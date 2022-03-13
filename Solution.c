//
// Created by legitlolly on 13/03/2022.
//
/*
 * Code to implement a scheduling solution for reducing processing skew
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 * Struct for group creation
 */

typedef struct{
    int fileIndexs[10000]; //Placeholder values for a quick solution
    int groupSize;
} group;

/*
 * Struct for each file storing the absolute size of a file as we dont care about the actual processing just an indicator
 * for the scheduler to make decisions off
 */

typedef struct{
    long int fileSize;
    char* fileName[100];
} file_data;

/*
 * Function prototypes
 */

/*
 * Init functions
 */

void initialise(file_data* fileData);

/*
 * Logic and arithmatic functions for scheduling
 */

void scheduler();


/*
 * Main
 */

int main()
{
    file_data fileData[1000];
    /*
     * Memory allocation for file data struct
     * Memory for filename is allocated when initialised to account for filename length
     */
    fileData->fileSize = (long int)malloc(sizeof(long int));

    initialise(fileData);
}


