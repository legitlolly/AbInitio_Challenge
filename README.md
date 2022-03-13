# AbInitio_Challenge
This is my submission for the Ab Initio coding test

[Description]

The code provided has a few utilities to create the environment for the scheduling code. Firstly the python script that lists all the file paths for the CSVs stored in the Data/ directory, secondly the initialise() function within the c program that takes this information and creates actionable data about each file for the scheduling algorithm (Absolute file size which correlates to the amount of data a thread will have to process). 

The code for scheduling takes all the files and lists them in order of size. It then initialises each threads group of files by assigning each one the biggest file available to start with. From here the scheduler() recursively goes through each file and assigns it to the smallest thread group this means some thread groups will have a different amount of files to process than other groups as some files can be particularly larger than others. This keeps processing skew to a minimum as the amount of data processed by a single thread will be as close to the average as possible which is where other simpler sorting methods like snake draft would be more influenced by high data variance.
