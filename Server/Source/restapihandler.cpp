#include "restapihandler.h"


RestAPIHandler::RestAPIHandler()
{
    m_responseMap["/meminfo"] = [this]() { return  m_sysinfo.getMemInfo();};
    m_responseMap["/hostname"] = [this]() { return  m_sysinfo.getHostname();};
    m_responseMap["/systeminfo"] = [this]() { return  m_sysinfo.getSystemInfo();};
}

APIResponse RestAPIHandler::getRootResonse()
{
    APIResponse response;
    response.staus = 200;
    response.type = "Content-Type: text/html; charset=UTF-8\r\n";
    std::string html = "<html><body><h1>Avaiable Apis</h1><br/><ul>";

    for ( const auto &keypair : m_responseMap ) {
            html += "<li>"+keypair.first+"</li>";
    }
    html += "</ul>";
    html +=  "</body></html>";
    response.content = html;
    return response;
}


APIResponse RestAPIHandler::handleRequest(std::string path)
{
    std::cout<<path<<std::endl;
    if(path == "/")
    {
        return getRootResonse();
    }

    APIResponse response;
    response.type = "Content-Type: application/json\r\n";
    if(m_responseMap.count(path) > 0)
    {
        std::string output = m_responseMap[path]();
        std::cout<<output<<std::endl;
        response.staus = 200;
        response.content = output;
    }
    else
    {
        response.staus = 404;
        response.content = "{\"message\": \" No Content\"}";
    }
    return response;
}


