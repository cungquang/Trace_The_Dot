#include <time.h>
#include "../include/general_helper.h"

static double weighted_newData = 0.15;

void runCommand(char* command)
{
    // Execute the shell command (output into pipe)
    FILE *pipe = popen(command, "r");

    // Ignore output of the command; but consume it
    // so we don't get an error when closing the pipe.
    char buffer[1024];
    while (!feof(pipe) && !ferror(pipe)) {
        if (fgets(buffer, sizeof(buffer), pipe) == NULL)
            break;
            // printf("--> %s", buffer); // Uncomment for debugging
    }
    // Get the exit code from the pipe; non-zero is an error:
    int exitCode = WEXITSTATUS(pclose(pipe));
    if (exitCode != 0) {
        perror("Unable to execute command:");
        printf(" command: %s\n", command);
        printf(" exit code: %d\n", exitCode);
    }
}

//Sleep for miliseconds
void sleepForMs(long long delayInMs)
{
    const long long NS_PER_MS = 1000 * 1000;
    const long long NS_PER_SECOND = 1000000000;
    long long delayNs = delayInMs * NS_PER_MS;
    int seconds = delayNs / NS_PER_SECOND;
    int nanoseconds = delayNs % NS_PER_SECOND;
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *) NULL);
}

long long getTimeInMs(void)
{
    struct timespec spec;
    clock_gettime(CLOCK_REALTIME, &spec);
    long long seconds = spec.tv_sec;
    long long nanoSeconds = spec.tv_nsec;
    long long milliSeconds = seconds * 1000 + nanoSeconds / 1000000;
    return milliSeconds;
}

int folderExists(const char *folderPath) {
    struct stat info;

    // Folder does not exist
    if (stat(folderPath, &info) != 0) return 0; 

    //Folder exist
    return S_ISDIR(info.st_mode);
}

//Read from file to screen
void readFromFileToBuffer(char *fileName, char *buff, int maxLength)
{
    FILE *pFile = fopen(fileName, "r");
    if (pFile == NULL) {
        printf("ERROR: Unable to open file (%s) for read\n", fileName);
        exit(-1);
    }
    // Read string (line)
    fgets(buff, maxLength, pFile);
    
    // Close
    fclose(pFile);
}


void writeToFile(char * fileName)
{
    // Use fopen() to open the file for write access.
    //FILE *pFile = fopen("/sys/class/gpio/export", "w");
    FILE *pFile = fopen(fileName, "w");
    if (pFile == NULL) {
        printf("ERROR: Unable to open export file.\n");
        exit(1);
    }
    // Write to data to the file using fprintf():
    fprintf(pFile, "%d", 30);

    // Close the file using fclose():
    fclose(pFile);
    // Call nanosleep() to sleep for ~300ms before use.
}


int convertTempoIntoTime(int tempo) 
{
    float timeToSleep = ((60.0f / tempo) / 2.0f) * 1000.0f;
    return (int)timeToSleep;
}

//Source: ChatGPT
void trimString(char* input)
{
    char *start = input;
    char *end = input + strlen(input) - 1;

    while(end > start && isspace(*end)) {
        end--;
    }

    //set to null
    *(end + 1) = '\0';

    // Shift the non-trailing space to the head of the string (remove leading trailing)
    if (start != input) {
        memmove(input, start, end - start + 2);
    }
}

double exponentialAvg(double current_avg, double previous_avg)
{
    return current_avg*weighted_newData + previous_avg*(1-weighted_newData);
}

double regularAvg(long current_size, double current_sum) 
{
    return current_sum/current_size;
}