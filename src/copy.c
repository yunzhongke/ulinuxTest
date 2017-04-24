#include <sys/stat.h>
#include <fcntl.h>
#include "../include/tlpi_hdr.h"


#ifndef BUF_SIZE
#define BUF_SIZE 1024
#endif
int main(int argc , char *argv[])
{
    int  inputFd , outputFd , openFlags;
    mode_t filePerms;
    ssize_t numRead;
    char buf[BUF_SIZE];

    if(argc != 3 || strcmp(argv[1] , "--help") == 0)
        usageErr("%s old-file new-file\n" , argv[0]);

    inputFd = open(argv[1] , O_RDONLY) ;
    if(inputFd == -1)
        errExit("opening file %s" , argv[2]);

    openFlags = O_CREAT | O_WRONLY | O_TRUNC;  //创建，只读,如果文件存在则清空，将长度置为0
    filePerms = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH; //rw-rw-rw , 相当于所有权限
    outputFd = open(argv[2] , openFlags , filePerms);
    if (outputFd == -1)
        errExit("opening file %s" , argv[2]);

    while( (numRead = read(inputFd , buf , BUF_SIZE)) > 0 )  //读到文件未尾退出
    {
        if(write(outputFd , buf , numRead) != numRead)    //如果文件空间不足则报错
            fatal("couldn't write whole buffer");
    }

    if(numRead == -1)  // 读取文件时，出错了
        errExit("read");

    if(close(inputFd) == -1)
        errExit("close input");
    if(close(outputFd) == -1)
        errExit("close outputFd");

    exit(EXIT_SUCCESS);
}
