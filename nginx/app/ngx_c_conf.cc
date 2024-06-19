#include <vector>
#include <ngx_c_conf.hh>

CConfig::CConfig()
{
    //构造函数
}

CConfig::~CConfig()
{
    std::vector<LPCConfItem>::iterator pos;
    for (pos = m_ConfigItemList.begin(); pos != m_ConfigItemList.end(); ++pos)
    {
        delete (*pos);
    }
    m_ConfigItemList.clear();
}

bool CConfig::Load(const char *pconfName)
{
    FILE *fp;
    fp = fopen(pconfName,"r");
    if (fp == NULL)
    {
        return false;
    }

    //每一行配置文件读出来放在这里
    char linebuf[501];  //每行配置都不要太长，保持<500字符内，防止出现问题
    //文件打开成功
    while(!feof(fp))
    {
        if ( fgets(linebuf,500,fp) == NULL)
            continue;

        if (linebuf[0] == 0)
            continue;

        //处理注释行
        if (*linebuf == ';' || *linebuf == ' ' || *linebuf == '#' || *linebuf == '\n' || *linebuf == '\t')
            continue;
        
        lblprocstring:
        //处理换行，回车，空格
        if(strlen(linebuf) > 0)
        {
            if (linebuf[strlen(linebuf) - 1] == 10 || linebuf[strlen(linebuf) - 1] == 13 || linebuf[strlen(linebuf) - 1] == 32)
            {
                linebuf[strlen(linebuf) - 1] = 0;
                goto lblprocstring;
            }
        }

        if (linebuf[0] == 0)
            continue;
        if (*linebuf == '[')
            continue;
        
        char *ptmp = strchr(linebuf,'=');
        if (ptmp != NULL)
        {
            LPCConfItem p_confitem = new CConfItem;//前边类型带LP，后边new的是结构体
            memset(p_confitem,0,sizeof(CConfItem));
            strncpy(p_confitem->ItemName,linebuf,(int)(ptmp - linebuf));//等号左侧的拷贝到p_confitem->ItemName
            strcpy(p_confitem->ItemContent,ptmp + 1);//等号右侧的拷贝到p_confitem->ItemContent

            Rtrim(p_confitem->ItemName);
            Ltrim(p_confitem->ItemName);
            Rtrim(p_confitem->ItemContent);
            Ltrim(p_confitem->ItemContent);

            m_ConfigItemList.push_back(p_confitem);
        }
    }

    fclose(fp);
    return true;
}

const char *CConfig::GetString(const char *p_itemname)
{
    std::vector<LPCConfItem>::iterator pos;
    for (pos = m_ConfigItemList.begin(); pos != m_ConfigItemList.end(); ++pos)
    {
        if (strcasecmp((*pos)->ItemName,p_itemname) == 0)
        {
            return (*pos)->ItemContent;
        }
    }
    return NULL;
}

int CConfig::GetIntDefault(const char *p_itemname,const int def)
{
    std::vector<LPCConfItem>::iterator pos;
    for (pos = m_ConfigItemList.begin(); pos != m_ConfigItemList.end(); ++pos)
    {
        if (strcasecmp((*pos)->ItemName,p_itemname) == 0)
        {
            return atoi((*pos)->ItemContent);
        }
    }
    return def;
}