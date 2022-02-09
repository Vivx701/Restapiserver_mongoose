//system libs
#include <iostream>
#include <signal.h>

//local includes
#include <mongoose.h>
#include <restapihandler.h>

bool running = true;
void signal_handler(int signal)
{
    std::cout<<" Signal receved to exit "<<std::endl;
    running = false;
}

static void http_callback(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{

    if(ev == MG_EV_HTTP_MSG)
    {
        struct mg_http_message *http_msg = (struct mg_http_message *) ev_data;
        std::string uri = std::string(http_msg->uri.ptr).substr(0, http_msg->uri.len);
        APIResponse res = RestAPIHandler::instance().handleRequest(uri);
        mg_http_reply(c, res.staus, res.type.c_str(), res.content.c_str());
    }

}

int main()
{
    signal(SIGINT, signal_handler);
    std::string htp_address = "http://0.0.0.0:5001";
    std::cout<<" Starting the webserver "<<htp_address<<std::endl;
    struct mg_mgr mgr;
    mg_log_set("2");
    mg_mgr_init(&mgr);
    mg_http_listen(&mgr, htp_address.c_str(), http_callback, NULL);
    do
    {
        mg_mgr_poll(&mgr, 1000);
        std::cout<<"polling"<<std::endl;
    }while(running);
    mg_mgr_free(&mgr);
    return 0;
}
