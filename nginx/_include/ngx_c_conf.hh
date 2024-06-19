#ifndef __NEX_C_CONF_HH__
#define __NEX_C_CONF_HH__

#include <vector>
#include "ngx_func.hh"
 //字符串处理相关函数
#include "ngx_global.hh"  //一些全局/通用定义

//CConfig类
class CConfig
{
//单例设计模式

private:
    CConfig();
public:
    ~CConfig();
private:
    static CConfig *m_instance;
public:
    static CConfig* GetInstance() 
    {
        if(m_instance == NULL)
        {
            //锁
            if(m_instance == NULL)
            {
                m_instance = new CConfig();
                static CGarhuishou cl; 
            }
            //放锁
        }
        return m_instance;
    }
    class CGarhuishou  //类中套类，用于释放对象
    {
    public:
        ~CGarhuishou()
        {
            if (CConfig::m_instance)
            {
                delete CConfig::m_instance;
                CConfig::m_instance = NULL;
            }
        }
    };
public:
    bool Load(const char *pconfName); //装载配置文件
    const char *GetString(const char *p_itemname);
    int  GetIntDefault(const char *p_itemname,const int def);
    void  PrintConfig(); //打印配置项，调试用
public:
    std::vector<LPCConfItem> m_ConfigItemList; //存储配置信息的列表
};

#endif
