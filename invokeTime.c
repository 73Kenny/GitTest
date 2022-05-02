// 此程序在Linux环境下运行
#include <stdio.h>
#include <time.h>

int main()
{
    time_t tt;          // int型数值
    struct tm *t; 
    // tt = time(NULL);
    asm volatile(
            "mov $0, %%rbx\n\t"     // 系统调用传递第一个参数使用EBX寄存器为0
            "mov $0xd, %%rax\n\t"   // 使用%eax传递传递系统调用号13，用16进制为0xd
            "int $0x80\n\t"         // 触发系统调用
            "mov %%rax, %0\n\t"     // 通过EAX寄存器返回系统调用值
            :"=m"(tt));
    t = localtime(&tt);
    printf("%d年%d月%d日 %d:%d:%d\n", (t->tm_year + 1900), t->tm_mon+1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
//  printf("当前的本地时间和日期：%s", asctime(t));
    return 0;
}

