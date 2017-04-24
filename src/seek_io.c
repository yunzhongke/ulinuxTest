#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>
#include "../include/tlpi_hdr.h"

int main(int argc , char *argv[])
{
    size_t len;
    off_t offset;
    int fd, ap , j;
    char *buf;
    ssize_t numRead , numWritten;

    if (argc < 3 || strcmp(argv[1] , "--help") == 0)
        usageErr("%s file {r<length>|R<length>|w<string>|s<offset>}...\n" , argv[0]);
    
    fd = open(argv[1] , O_RDWR | O_CREAT , S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

    if (fd == -1)
        errExit("open");

    for (ap = 2; ap < argc ; ap++)
    {
        /*假设：命令行输入：./seek 1.txt r100 wnihao  
         *     argv[ap][0] 就表示 'r'
         */
        switch(argv[ap][0])
        {
        case 'r':  //以文本的方式显示
        case 'R':   //以十六进制显示
            len = getLong(&argv[ap][1] , GN_ANY_BASE , argv[ap]);
            buf = (char*)malloc(len);
            if (buf == NULL)
                errExit("malloc");

            numRead = read(fd , buf , len);
            if (numRead == -1)
                errExit("read");
            if (numRead == 0)
            {
                printf("%s:end-of-file\n" , argv[ap]);
            }
            else
            {
                printf("%s:" , argv[ap]);
                for (j = 0; j < numRead ; j++)
                {
                    if (argv[ap][0] == 'r')
                        printf("%c" , isprint((unsigned char)buf[j]) ? buf[j] : '?'); //文本显示
                    else
                        printf("%02x" , (unsigned int)buf[j]);  //十六进制显示
                }
                printf("\n");
            }
            free(buf);
            break;

        case 'w':  // 往文件中写入内容
            numWritten = write(fd , &argv[ap][1] , strlen(&argv[ap][1]));
            if (numWritten == -1)
                errExit("write");
            printf("%s: wrote %ld bytes\n" , argv[ap] , (long)numWritten );
            break;
            
        case 's':  // 获取当前文件的偏移量
            offset = getLong(&argv[ap][1] , GN_ANY_BASE , argv[ap]);
            if (lseek(fd , offset , SEEK_SET) == -1)
                errExit("lseek");
            printf("%s:seek succeeded\n" , argv[ap]);
            break;

        default:
            cmdLineErr("Argument must start with [rRws]: %s\n" , argv[ap]);
        }
    }
    exit(EXIT_SUCCESS);
}
