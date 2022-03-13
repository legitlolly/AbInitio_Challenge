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

int initialise(file_data* fileData);

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
    int array_size;
    /*
     * Memory allocation for file data struct
     */
    fileData->fileSize = (long int)malloc(sizeof(long int));

    for(int i = 0; i < 1000; i++)
    {
        for(int j = 0; j < 100; j++)
        {
            fileData[i].fileName[j] = (char *) malloc(sizeof(char));
        }
    }

    array_size = initialise(fileData);
}

int initialise(file_data* fileData)
{
    /*
     * Init variables needed for csv scraping
     */
    char* token;
    int index;
    char buffer[10000]; //Placeholder

    /*
     * Reading py script output to get an easy list of the paths for processing
     */
    FILE *filenames = fopen("CSVFileNames.csv", "r");

    /*
     * Error catching (read file failure)
     */
    if(!filenames)
    {
        printf("Error has occured\n");
        exit(-1);
    }

    while(fgets(buffer, sizeof(buffer), filenames))
    {
        token = strtok(buffer, ",");
        while(token != NULL)
        {
            //Read the index for indexing
            sscanf(token, "%d", &index);
            //Bump token along to relevant field
            token = strtok(NULL, ",");
            fileSizer(token, fileData, index);
            //Push token to the next line
            token = strtok(NULL, ",");
        }
    }
    fclose(filenames);

    return index;
}

void fileSizer(char* filename, file_data* fileData,int i)
{

    filename[strlen(filename)-1] = '\0'; //Removes the white space enter that causes errors on file opening
    FILE *file = fopen(filename, "r");

    /*
    * Error catch if file fails to be read i.e wrong file type
    */

    if(!file)
    {
        printf("Error Occured here\n");
        return;
    }

    /*
    * Using fseek to check the size of the file to gather an absolute size of the data
    */

    fseek(file, 0L, SEEK_END);
    long int size = ftell(file);

    /*
     * Storing the values in the struct
     */

    memcpy(fileData[i].fileName, filename, 100);
    fileData[i].fileSize = size;
    fclose(file);
    return;
}