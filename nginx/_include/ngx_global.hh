#ifndef __NEX_GLOBAL_HH__
#define __NEX_GLOBAL_HH__

//一些比较通用的定义放在这里

//结构定义

typedef struct
{
    char ItemName[50];  //配置项名称
    char ItemContent[500]; //配置项内容
}CConfItem,*LPCConfItem;

//和运行日志相关 
typedef struct
{
	int    log_level;   //日志级别 或者日志类型，ngx_macro.h里分0-8共9个级别
	int    fd;          //日志文件描述符

}ngx_log_t;

//外部全局变量声明
extern char **g_os_argv;
extern char *gp_envmem;
extern int g_environlen;

extern pid_t ngx_pid;
extern ngx_log_t ngx_log;

#endif
