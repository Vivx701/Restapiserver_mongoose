#include "restapiclient.h"
using json = nlohmann::json;
RestAPIClient::RestAPIClient()
{
}

std::vector<std::string> RestAPIClient::apis() const
{
    return m_apis;
}

RestAPIClient& RestAPIClient::instance()
{
    static RestAPIClient instance;
    return instance;
}

bool RestAPIClient::handleRoot(std::string response)
{

     std::string ul_start_tag = "<li>";
     std::string ul_end_tag = "</li>";
     size_t pos=response.find(ul_start_tag);
     if(pos == response.length())
     {
         return false;
     }
     while(pos<response.length())
     {
         std::size_t endpos = response.find(ul_end_tag, pos);
         m_apis.push_back(response.substr(pos+ul_start_tag.length(), endpos-(pos+ul_end_tag.length()-1)));
         pos = response.find(ul_start_tag, endpos);
     }
     return true;
}

std::map<std::string, std::string>  RestAPIClient::parseResponse(std::string response)
{
    std::map<std::string, std::string> result;
    json json_obj = json::parse(response);
    for (json::iterator it = json_obj.begin(); it != json_obj.end(); ++it) {
        std::string v;
        if(it->is_number())
        {
             unsigned long  value = it->get<unsigned long>();
             v = std::to_string(value);
        }
        else if(it->is_string())
        {
            v = it->get<std::string>();
        }
        result.insert({it.key(), v});
    }
    return result;
}


