#ifndef __NEX_GLOBAL_HH__
#define __NEX_GLOBAL_HH__

//一些比较通用的定义放在这里

//结构定义

typedef struct
{
    char ItemName[50];  //配置项名称
    char ItemContent[500]; //配置项内容
}CConfItem,*LPCConfItem;

//外部全局变量声明
extern char **g_os_argv;
extern char *gp_envmem;
extern int g_environlen;

#endif
