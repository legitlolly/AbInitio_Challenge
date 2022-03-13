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
void fileSizer(char* filename, file_data* fileData, int i);

/*
 * Logic and arithmatic functions for scheduling
 */

void scheduler(file_data* fileData, int array_size);
void sortDatabySize(file_data* fileData, int low, int high);
int partition(file_data* fileData, int low, int high);
void swapFileData(file_data* x, file_data* y);
void fileStackCreator(file_data* fileData, int threads, group* indexGroups, int array_size);
int smallestGroup(file_data* fileData, group* indexGroups, int threads);
int sumSize(file_data* fileData, int groupSizeBreakdown[], int groupSize);

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
    scheduler(fileData, array_size);
}


/*
 * Uses utility functions and logic to "assign" threads a list of paths that point to csv files to "process"
 */
void scheduler(file_data* fileData, int array_size)
{
    /*
     * Init
     */

    int threads = 10;
    group indexGroups[threads];

    /*
     * Memory allocation
     * fileIndex is huge simply for convenience as efficiency isn't necessary
     */
    for(int z = 0; z < threads; z++)
    {
        indexGroups[z].groupSize = (size_t)malloc(sizeof(int) * array_size);
        for(int y = 0; y < 10000; y++)
        {
            indexGroups[z].fileIndexs[y] = (size_t)malloc(sizeof(int));
        }
    }

    //Sorts the data in order of size biggest first as it's easier to match a big file with smaller files (Quicksort)
    sortDatabySize(fileData, 0, array_size);

    //organise the data into stacks = amount of threads these will be the assignments of the threads
    fileStackCreator(fileData, threads, indexGroups, array_size);


    /*
     * Printing the path allocations for visuals as not actually assigning them to anything
     */

    int total_files = 0;
    for(int i = 0; i < threads; i++)
    {
        printf("Thread %d has group size %d and works on the following file paths : \n", i, indexGroups[i].groupSize);
        for(int j = 0; j < indexGroups[i].groupSize; j++)
        {
            printf("%s\n", fileData[indexGroups[i].fileIndexs[j]].fileName);
        }
        total_files += indexGroups[i].groupSize;
    }
    printf("The total paths allocated is : %d\n", total_files);

}

/*
 * File stack creator goes through the sorted file_data struct and allocates files biggest to smallest. To do this it
 * uses a utility function that returns the current smallest thread grouping using the fileSizes.
 */

void fileStackCreator(file_data* fileData, int threads, group* indexGroups, int array_size)
{
    /*
     * First we initialise the thread groupings biggest files are found at the end of the sort hence line 165
     */
    int smallestGroupIndex;
    for(int i = 0; i < threads; i++)
    {
        indexGroups[i].fileIndexs[0] = array_size - i;
        indexGroups[i].groupSize = 1;
    }
    /*
     * We then loop through each index in the file_data struct and assign it to the current smallest group this group
     * then becomes larger due to the added file and potentially a different group becomes the smallest
     */
    for(int j = array_size - threads; j > -1; j--)
    {
        smallestGroupIndex = smallestGroup(fileData, indexGroups, threads);
        indexGroups[smallestGroupIndex].fileIndexs[indexGroups[smallestGroupIndex].groupSize] = j;
        indexGroups[smallestGroupIndex].groupSize++;
    }

    return;
}

/*
 * Goes through the assigned groups given and returns which one has the smallest absolute size
 */

int smallestGroup(file_data* fileData, group* indexGroups, int threads)
{
    int groupSumSizes[threads];
    int smallestGroup = 0;
    for(int i = 0; i < threads; i++)
    {
        groupSumSizes[i] = sumSize(fileData, indexGroups[i].fileIndexs, indexGroups[i].groupSize);
        if(groupSumSizes[i] < groupSumSizes[smallestGroup])
        {
            smallestGroup = i;
        }
    }
    return smallestGroup;
}

/*
 * Utility function for smallestGroup sums the size of all the files in a given grouping
 */

int sumSize(file_data* fileData, int groupSizeBreakdown[], int groupSize)
{
    int size = 0;
    for(int i = 0; i < groupSize; i++)
    {
        int index = groupSizeBreakdown[i];
        size = size + fileData[index].fileSize;
    }
    return size;
}


/*
 * Quicksort algorithm to sort the file_data struct conveniently
 */

void sortDatabySize(file_data* fileData, int low, int high)
{
    if(low < high)
    {
        int index = partition(fileData, low, high);
        sortDatabySize(fileData, low, index - 1);
        sortDatabySize(fileData, index + 1, high);
    }
}

/*
 * Quicksort utility
 */

int partition(file_data* fileData, int low, int high)
{
    int pivot = fileData[high].fileSize;
    int i = (low - 1);

    for(int j = low; j < high; j++)
    {
        if(fileData[j].fileSize < pivot)
        {
            i++;
            swapFileData(&fileData[i], &fileData[j]);
        }
    }
    swapFileData(&fileData[i+1], &fileData[high]);
    return(i + 1);
}

/*
 * Quicksort utility
 */

void swapFileData(file_data* x, file_data* y)
{
    file_data z = *x;
    *x = *y;
    *y = z;
    return;
}


/*
 * Initialises the CSV data into the file_data struct
 */

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

/*
 * Takes a filename and assigns it to its own instance of file_data struct also takes its size for .fileSize
 */

void fileSizer(char* filename, file_data* fileData, int i)
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