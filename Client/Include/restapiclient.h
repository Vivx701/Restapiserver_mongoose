#ifndef RESTAPICLIENT_H
#define RESTAPICLIENT_H

#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <json.hpp>

class RestAPIClient
{
public:
    static RestAPIClient& instance();
    bool handleRoot(std::string response);
    std::map<std::string, std::string> parseResponse(std::string response);
    std::vector<std::string> apis() const;

private:
    RestAPIClient();
    std::vector<std::string> m_apis;
};

#endif // RESTAPICLIENT_H
