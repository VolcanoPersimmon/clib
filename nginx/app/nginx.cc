#include "ngx_c_conf.hh"
#include "ngx_global.hh"
#include "ngx_func.hh"
#include <stdio.h>
#include <unistd.h>//unix sleep, windows系统 应该是windows.h
#include <string>

char **g_os_argv = NULL; //原始命令行参数数组
char *gp_envmem = NULL; //指向自己分配的env环境变量的内存 
int g_environlen = 0; //环境变量所占内存大小

int main(int argc, char *const *argv)
{
    g_os_argv = (char **)argv;
    ngx_init_setproctitle(); //把环境变量搬家

    CConfig *p_config = CConfig::GetInstance();//单例类
    if (p_config -> Load("nginx.conf") == false)
    {
        //配置文件不对
        printf(0,"配置文件[%s]载入失败，退出!", "nginx.conf");
        exit(1);
    }

    // int port = p_config->GetIntDefault("ListenPort", 0);//0是缺省值
    // printf("port = %d\n", port);
    // char const *pDBInfo = p_config->GetString("DBInfo");
    // if (pDBInfo)
    // {
    //     printf("DBInfo = %s\n", pDBInfo);
    // }
    for(;;){
        sleep(1);
        printf("rest for 1 second\n");
    }

    //对于因为设置可执行程序标题导致的环境变量分配的内存，我们这里释放
    if (gp_envmem)
    {
        delete []gp_envmem;
        gp_envmem = NULL;
    }
    printf("Complete, Bye!\n");
    return 0;
}
// {
//     CConfig *p_config = CConfig::GetInstance();//单例类
//     if (p_config -> Load("nginx.conf") == false)
//     {
//         //配置文件不对
//         printf(0,"配置文件[%s]载入失败，退出!", "nginx.conf");
//         exit(1);
//     }

//     int port = p_config->GetIntDefault("ListenPort", 0);//0是缺省值
//     printf("port = %d\n", port);
//     char const *pDBInfo = p_config->GetString("DBInfo");
//     if (pDBInfo)
//     {
//         printf("DBInfo = %s\n", pDBInfo);
//     }
// }
