#include <stdio.h>
#include <unistd.h>

int main(int argc, char *const *argv)
{
    pid_t pid; 
    printf("test\n");
    //系统函数，设置某个信号来的时候处理程序
    //signal(SIGHUP, SIG_IGN);//SIG_IGN标志：要求忽略这个信号
    pid = fork();
    if (pid < 0){
	    printf("fork()error\n");
    }
    else if(pid == 0){
	    printf("son process working! \n");
	    setsid();
	    for(;;){
		    sleep(1);
		    printf("Son process rest 1 second\n");
	    }
	    return 0;
    }
    else {
	    for(;;){
		    sleep(1);
		    printf("father process rest for 1 second\n");
	    }
	    return 0;
    }
}
