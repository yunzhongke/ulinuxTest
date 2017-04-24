#include <stdio.h>
#include <fcntl.h>
#include <ctype.h>
#include "../include/tlpi_hdr.h"

#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif

int main(int argc , char *argv[])
{
    char buf[BUF_SIZE];
    ssize_t numRead;
    int fdfile1 , fdfile2;
    if (argc != 3)
        usageErr("%s file1 file2 \n" , argv[0]);

    fdfile1 = open(argv[1] , O_RDONLY);
    if (fdfile1 == -1)
        errExit("opening file %s" , argv[1]);

    fdfile2 = open(argv[2] , O_RDWR | O_CREAT | O_TRUNC , 0664);
    if (fdfile2 == -1)
        errExit("opening file %s" , argv[2]);

    while( (numRead = read(fdfile1 , buf , BUF_SIZE )) > 0)
    {
        if (write(fdfile2 , buf , numRead) != numRead)
            fatal("could't write whole buffer");
    }

    if (numRead == -1)
        errExit("read");
    if (close(fdfile1) == -1)
        errExit("close fdfile1");
    if (close(fdfile2) == -2)
        errExit("close fdfile2");

    exit(EXIT_SUCCESS);
}
