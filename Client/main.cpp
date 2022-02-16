#include <iostream>
#include <mongoose.h>
#include <restapiclient.h>

using namespace std;
bool running = true;
std::string url = "http://127.0.0.1:5001";

void signal_handler(int signal)
{
    std::cout<<" Signal receved to exit "<<std::endl;
    running = false;
}

void show_menu(struct mg_connection *c, std::vector<std::string> apis)
{
    int option = -1;
    int api_size = apis.size();
    std::cout<<" Select the API index to request "<<std::endl;
    for(int i=0; i<apis.size(); i++)
    {
        std::cout<<i<<" : "<<apis.at(i)<<std::endl;
    }
    std::cout<<api_size<<" : "<<"exit"<<std::endl;
    std::cout<<"option : ";
    std::cin>>option;
    if(option == api_size)
    {
        running = false;
        std::cout<<" Bye Bye.. "<<std::endl;
    }
    else if(option < api_size)
    {
        struct mg_str host = mg_url_host(url.c_str());
        std::string api_url = url+apis.at(option);
        mg_printf(c,
                    "GET %s HTTP/1.0\r\n"
                    "Host: %.*s\r\n"
                    "\r\n",
                    mg_url_uri(api_url.c_str()), (int) host.len, host.ptr);
    }
}

void print_output(std::map<std::string, std::string> output_values)
{
    std::cout<<"__________________________________________"<<std::endl;
    for (auto itr = output_values.begin(); itr != output_values.end(); ++itr)
    {
        std::cout<<itr->first<<"   :     "<<itr->second<<std::endl;
    }
    std::cout<<"__________________________________________"<<std::endl;
}
static void http_callback(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
    if (ev == MG_EV_CONNECT)
    {
        std::cout<<" Connected to server "<<std::endl;
    }
    else if (ev == MG_EV_HTTP_MSG) {
       struct mg_http_message *http_msg = (struct mg_http_message *) ev_data;
       std::string header_key = "Content-type";
       struct mg_str *s = mg_http_get_header(http_msg, header_key.c_str());
       std::string content_type = std::string(s->ptr).substr(0, s->len);
       if(content_type.find("text/html") < content_type.length())
       {
           RestAPIClient::instance().handleRoot(http_msg->body.ptr);
       }
       else
       {
           std::map<std::string, std::string> output_values = RestAPIClient::instance().parseResponse(http_msg->body.ptr);
           print_output(output_values);
       }
       show_menu(c, RestAPIClient::instance().apis());
     }
}


int main()
{
    cout << "Starting the client" << endl;
    struct mg_mgr mgr;
    mg_log_set("3");
    mg_mgr_init(&mgr);
    signal(SIGINT, signal_handler);
    struct mg_connection *c = mg_http_connect(&mgr, url.c_str(), http_callback, &running);
    struct mg_str host = mg_url_host(url.c_str());
    mg_printf(c,
                "GET %s HTTP/1.0\r\n"
                "Host: %.*s\r\n"
                "\r\n",
                mg_url_uri(url.c_str()), (int) host.len, host.ptr);
    cout << "Client is running : Press Ctrl+C to exit" << endl;
    do
    {
        mg_mgr_poll(&mgr, 1000);
    }while(running);
    mg_mgr_free(&mgr);
    return 0;
}
