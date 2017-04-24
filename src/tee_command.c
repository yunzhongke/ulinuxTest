#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "../include/tlpi_hdr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 
 * 输入 ： tee file  ,然后将终端中的数据写入到文件file中
 * 输入 ： tee -a file , 如果文件存在，则在文件未尾追加数据
 *
 */ 

void writefile(int argc , char **argv)
{
    FILE *fd;
    char buf[1024];
    if (argc == 2)
    {
        printf("argc=%d,argv[1]=%s\n",argc,argv[1]);
        fd = fopen(argv[1] , "w+");
        if (fd == NULL)
            errExit("open");
    
        while(1)
        {
            memset(buf , 0 ,sizeof(buf));
            fgets(buf , sizeof(buf) , stdin);
            fputs(buf , fd);
            fflush(fd);
        }

        fclose(fd);
    }

    else if (argc == 3 && strcmp(argv[1] , "-a") == 0)
    {
        printf("argc=%d,argv[1]=%s,argv[2]=%s\n",argc,argv[1],argv[2]);
        fd = fopen(argv[2] , "a");
        if (fd == NULL)
            errExit("open");
    
        while(1)
        {
            memset(buf , 0 ,sizeof(buf));
            fgets(buf , sizeof(buf) , stdin);
            fputs(buf , fd);
            fflush(fd);
        }

        fclose(fd);
    }
    else 
    {
        printf("not support\n");
    }
}


int main(int argc , char *argv[])
{
   if (argc < 2 || strcmp(argv[0] , "--help") == 0)
       usageErr("%s [option] file ..\n " , argv[0]);

   writefile(argc , argv);
}
