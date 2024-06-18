#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int g_mysign = 0;
void muNEfunc(int value)
{
  g_mysign = value;
}

void sig_usr(int signo)
{
  muNEfunc(22);
  if (signo == SIGUSR1)
  {
    printf("收到了SIGUSR1信号!\n");
  }
  else if (signo == SIGUSR2){
    printf("收到了SIGUSR2信号！\n");
  }
  else {
    printf("收到了未捕捉的信号%d！\n",signo);
  }
}

int main(int argc, char *const *argv)
{
  if (signal(SIGUSR1, sig_usr) == SIG_ERR)
  {
    printf("无法捕捉信号！\n");
  }
  if (signal(SIGUSR2, sig_usr)== SIG_ERR )
  {
    printf("无法捕捉SIGUSR2信号！\n");
  }
  for(;;)
  {
    sleep(1);//rest 1 second
    printf("休息1秒\n");
    muNEfunc(15);
    printf("g_mysign=%d",g_mysign);
  }
  printf("再见！\n");
  return 0;
}
