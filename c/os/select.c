// #include <stdio.h>
// #include <unistd.h>
// #include <string.h>
#include <sys/select.h>

fd_set rdfds; /* 先申明一个 fd_set 集合来保存我们要检测的 socket句柄 */

FD_ZERO(&rdfds); /* 用select函数之前先把集合清零 */

struct timeval tv; /* 申明一个时间变量来保存时间 */

int ret; /* 保存返回值 */

// FD_SET(socket, &rdfds); /* 把要检测的句柄socket加入到集合里 */

// tv.tv_sec = 1;

// tv.tv_usec = 500; /* 设置select等待的最大时间为1秒加500微秒 */

int main(int argc, char ** argv){
    char buf[10] = "";

    // read(0, buf, 9); /* 从标准输入 0 读入字符 */

    // fprintf(stdout, "%s/n", buf); /* 向标准输出 stdout 写字符 */

    return 0;
}
