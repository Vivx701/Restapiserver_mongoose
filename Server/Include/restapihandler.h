#ifndef RESTAPIHANDLER_H
#define RESTAPIHANDLER_H

#include <string>
#include <iostream>
#include <map>
#include <functional>
#include <linuxinfo.h>

struct APIResponse
{
    std::string content;
    int staus;
    std::string type;
};


class RestAPIHandler
{
public:
    static RestAPIHandler& instance()
    {
        static RestAPIHandler instance;
        return instance;
    }

    APIResponse handleRequest(std::string path);

private:
    RestAPIHandler();
    APIResponse getRootResonse();
    std::map<std::string, std::function<std::string()>> m_responseMap;
    LinuxInfo m_sysinfo;

};

#endif // RESTAPIHANDLER_H
