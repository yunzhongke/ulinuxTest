#define _BSD_SOURCE 1   //特性测试宏，定义在包含头文件之前
#include <stdio.h>
#include <stdlib.h>
#include <gnu/libc-version.h>


extern char **environ; //外部访问环境变量，声明就可使用

void test()
{
    char **env = environ;
    while(*env)
    {
        printf("%c" , **env);
        env++;
    }
}

void test2()
{
    printf("glibc:%s\n",gnu_get_libc_version());//获取glibc的版本，该函数由 gnu/libc-version.h 提供了   
}

void test3()
{
    int num;
    num = (15 & 0)? 0 : 1; //指定位置0
    printf("num:%d\n" , num);
}


int main()
{
    test2();
    test3();
    exit(0);
}
