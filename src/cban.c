#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


/** LOGGING FUNCTIONS
 * DEBUG: info that is useful to devs.
 * ERROR: errors that crash a function.
 * FATAL: errors that force app to shutdown or crash.
 * INFO: general info about how app is running.
 * WARN: something can cause oddities in application behavior.
*/
#define DEBUG(...) fprintf(stderr, "DEBUG:\t"); fprintf(stderr, __VA_ARGS__);
#define ERROR(...) fprintf(stderr, "ERROR:\t"); fprintf(stderr, __VA_ARGS__);
#define INFO(...) fprintf(stderr, "INFO:\t"); fprintf(stderr, __VA_ARGS__);
#define WARN(...) fprintf(stderr, "WARN:\t"); fprintf(stderr, __VA_ARGS__);


#define BLOCK_SIZE_BYTES 512
#define ERROR -1
#define SUCCESS 0


enum mode {
    ONE_PASS,
    DOD_SHORT, 
    DOD_LONG
} typedef Mode;

struct buffers {
    char *zerosBuffer, *onesBuffer;
} typedef Buffers;

struct wiper {
    Buffers* buffers;       // I don't want to pass two pointers to functions.
    int fd, totalNumberOfPasses;
    mode_t mode;
} typedef Wiper;


/* FUCNTION DECLARATIONS */

Buffers* _initBuffers();
void _freeBuffers(Buffers*);
Wiper* _initWiper(Buffers*, int, mode_t);
int openDriveFS(char*);
int whileLoop(char*, int);
int writeBytesToDisk(int);


int main(void) {
    Buffers buffers = _initBuffers();

    /* Potential idea, fork process and wait for child processes to finish */

    /* Add ability for user to enter path to drive. */
    //  Simply have them enter a string in the CLI.
    //  Or, create a simple GUI app that allows them to select drives.
    char* drivePath = NULL;
    wipeDrive(drivePath);

    _freeBuffers(buffers);

    INFO("Done!\n");

    return SUCCESS;
}


Buffers* _initBuffers() {
    Buffers *buffers = (Buffers*)malloc(sizeof(Buffers));

    (*buffers).onesBuffer = (char*) malloc(BLOCK_SIZE_BYTES);
    memset((*buffers).onesBuffer, 0b0001, BLOCK_SIZE_BYTES);
    (*buffers).zerosBuffer = calloc(1, BLOCK_SIZE_BYTES);

    return buffers;
}

void _freeBuffers(Buffers *buffers) {
    free((*buffers).onesBuffer);
    free((*buffers).zerosBuffer);
    free(buffers);
}

Wiper* _initWiper(Buffers *buffers, int fd, mode_t mode) {
    Wiper *wiper = (Wiper*)malloc(sizeof(Wiper));

    (*wiper).buffers = buffers;
    (*wiper).fd = fd;

    if (mode == ONE_PASS) { 
        (*wiper).mode = ONE_PASS; 
        (*wiper).totalNumberOfPasses = 1;
    } else if (mode == DOD_SHORT) { 
        (*wiper).mode = DOD_SHORT; 
        (*wiper).totalNumberOfPasses = 3;
    } else if (mode == DOD_LONG) { 
        (*wiper).mode = DOD_LONG; 
        (*wiper).totalNumberOfPasses = 7;
    }

    return wiper;
}

int openDriveFS(char *drivePath) {
    int fd = open(drivePath, O_WRONLY);

    if (fd < 0) {
        ERROR("Unable to open the device file!\n");
        return ERROR;
    } 

    return fd;
}

int writeBytesToDisk(char* bytesToWrite, int fd) {
    // There's a reason I have this function... The bytes we want to write to the disk 
    //  have to alternate at times. Some DoD standards specify, like DoD Short, specify
    //  that there must be several pass throughs with alternating patterns.

    int bytesWritten = bytesWritten = write(fd, bytesToWrite, BLOCK_SIZE_BYTES);

    return bytesWritten;
}

int wipeDrive(char* drivePath, Buffers* buffers, mode_t mode) {
    int fd = openDriveFS(drivePath);
    if (fd == ERROR) { return ERROR; }

    Wiper *wiper = _initWiper(buffers, fd, mode);


    /* Potential idea, somehow obtain the size of the drive for progress bar. */
    //  Scan the entire drive (SLOW).
    //  See if there is function or something hardware level that could tell this.
    //  size_t sizeOfDrive = 0;


    /* Wipe the drive */
    int numberOfPasses = 0;
    while (numberOfPasses < (*wiper).totalNumberOfPasses) {
        size_t bytesWritten = 0, totalBytesWritten = 0;

        /* Add logic to switch between the 0 and 1 buffers. */

        do {
            bytesWritten = writeBytesToDisk((*buffers).zerosBuffer, fd);
            totalBytesWritten += bytesWritten;
        } while (bytesWritten == BLOCK_SIZE_BYTES);         // check if we are at the end of the disk

        INFO("Pass %d of %d.\n", (numberOfPasses + 1), (*wiper).totalNumberOfPasses);
        INFO("Total number of bytes written:\t%ld", totalBytesWritten);

        numberOfPasses++;
    }
    
    INFO("Your drive has finished wiping!\n");

    close(fd);
    free(wiper);

    return SUCCESS;
}
