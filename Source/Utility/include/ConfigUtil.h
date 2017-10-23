#pragma once
#ifndef CONFIG_UTIL_H
#define CONFIG_UTIL_H

#include "exio.h"

namespace ConfigUtil
{
    //-------------------------------------------------------------------
    // need refactor . something with the string compare.
    //-------------------------------------------------------------------
    template<typename T>
    T getProfileNumber(const std::string& section,
        const std::string& key, T defaultValue,
        const std::string& path)
    {
        //reg
        //read by line
        std::ifstream is;
        is.open(path.c_str(), std::ios::in|std::ios::binary);
        if (!is.is_open())
        {
            return defaultValue;
        }
        std::string buf;
        bool bSectionFind = false;
        std::string strSection("[");
        strSection += section;
        strSection += "]";
        while (std::getline(is, buf))
        {
            stlu::trim(buf);
            if (buf == strSection)
            {
                bSectionFind = true;
                continue;
            }

            if (bSectionFind)
            {
                //buf 格式为[***] 跳出
                std::string::iterator beg = buf.begin();
                std::string::iterator tail = buf.end();
                --tail;
                if (*beg == '[' && *tail == ']')
                {
                    break;
                }
            }

            if (bSectionFind)
            {
                std::vector<std::string> v = stlu::split(buf, "=");
                if (v.size() != 2)
                {
                    continue;
                }
                stlu::trim(v[0]);
                if (0 == strncmp(key.c_str(), v[0].c_str(), key.length()))
                {
                    is.close();
                    return stlu::stringTo<T>(stlu::trim(v[1]));
                }
            }
        }//end loop
        is.close();
        return defaultValue;        
    }
    //---------------------------------------------
    //
    //---------------------------------------------
    inline std::string getProfileString(const std::string& section,
        const std::string& key, const std::string& defaultValue,
        const std::string& path)
    {
        std::ifstream is;
        is.open(path.c_str(), std::ios::in|std::ios::binary);
        if (!is.is_open())
        {
            return defaultValue;
        }
        std::string buf;
        bool bSectionFind = false;
        std::string strSection("[");
        strSection += section;
        strSection += "]";
        while (std::getline(is, buf))
        {
            stlu::trim(buf);
            if (buf == strSection)
            {
                bSectionFind = true;
                continue;
            }

            if (bSectionFind)
            {
                //buf 格式为[***] 跳出
                std::string::iterator beg = buf.begin();
                std::string::iterator tail = buf.end();
                --tail;
                if (*beg == _TX('[') && *tail == _TX(']'))
                {
                    break;
                }
            }

            if (bSectionFind)
            {
                std::vector<std::string> v = stlu::split(buf, "=");
                if (v.size() != 2)
                {
                    continue;
                }
                stlu::trim(v[0]);
                //if (0 == strncmp(key, v[0].c_str(), strlen(key)))
                if (key == v[0])
                {
                    is.close();
                    return stlu::trimC(v[1]);
                }
            }
        }//end loop
        is.close();
        return defaultValue;  
    }
    //---------------------------------------------
    //write info to the <path> , ini config file.
    //---------------------------------------------
    inline int writeProfileString(const std::string& section,
        const std::string& key, const std::string& value, const std::string& path)
    {
        //open input stream
        std::map<const std::string, std::set<std::string> > allInfo;
        std::ifstream is;
        is.open(path.c_str(), std::ios::binary | std::ios::in);
        if (is.fail())
        {
            std::ofstream crtos;
            crtos.open(path.c_str(), std::ios::binary | std::ios::out);
            crtos.close();
            is.open(path.c_str(), std::ios::binary | std::ios::in);
            if (is.fail())
            {
                return -1;
            }
        }

        //read all information
        std::string buf;
        std::set<std::string>* refSection = NULL;
        while(std::getline(is, buf))
        {
            stlu::trim(buf);
            if (buf[0] == '[' && buf[buf.length() - 1] == ']')
            {
                std::map<const std::string, std::set<std::string> >::iterator it = allInfo.find(buf);
                if (it == allInfo.end())
                {
                    allInfo.insert(std::make_pair(buf, std::set<std::string>()));
                }
                refSection = &(allInfo[buf]);
                continue;
            }
            if (NULL != refSection)
            {
                refSection->insert(buf);  
            }        
        }
        is.close();

        //modify
        std::string sec = "[";
        sec += section;
        sec += "]";
        std::string res = std::string(key) + std::string("=") + std::string(value);
        std::map<const std::string, std::set<std::string> >::iterator it = allInfo.find(sec);
        if (it == allInfo.end())
        {
            std::set<std::string> lst;
            lst.insert(res);
            allInfo.insert(std::make_pair(sec, lst));
        }else
        {
            //if (it->second.find(res) == it->second.end())
            //{
            it->second.insert(res);
            //}
        }

        //output
        std::ofstream os;
        os.open(path.c_str(), std::ios::binary | std::ios::out | std::ios::ate);
        if (os.fail())
        {
            return -1;
        }

        for (std::map<const std::string, std::set<std::string> >::iterator it = allInfo.begin();
            it != allInfo.end(); ++it)
        {
            os<<it->first<<"\r\n";
            for (std::set<std::string>::iterator itor = it->second.begin();
                itor != it->second.end(); ++itor)
            {
                os<<*itor<<"\r\n";
            }
        }
        os.close();

        return 1;
    }
}

#endif
