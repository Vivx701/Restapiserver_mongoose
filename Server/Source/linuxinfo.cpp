#include "linuxinfo.h"

using json = nlohmann::json;

LinuxInfo::LinuxInfo()
{
}

std::string LinuxInfo::getMemInfo()
{
    struct sysinfo info;
    int res =  sysinfo(&info);
    if(res == 0)
    {
        unsigned long totalram   = info.totalram;
        unsigned long availram   = info.freeram;
        unsigned long sharedram = info.sharedram;
        unsigned long totalswap = info.totalswap;
        unsigned long freeswap  = info.freeswap;

        json json_out;
        json_out["totalram"] = totalram;
        json_out["availram"] = availram;
        json_out["sharedram"] = sharedram;
        json_out["totalswap"] = totalswap;
        json_out["freeswap"] = freeswap;
        return json_out.dump();


    }
    return std::string();
}

std::string LinuxInfo::getHostname()
{
    char hostname[HOST_NAME_MAX + 1];
    int res = gethostname(hostname, HOST_NAME_MAX + 1);
    if(res == 0)
    {
        json json_out;
        json_out["hostname"] = hostname;
        return json_out.dump();
    }
    return std::string();
}

std::string LinuxInfo::getSystemInfo()
{
   struct utsname buf1;
   if(uname(&buf1)!=0)
   {
       return std::string();
   }
   json json_out;
   json_out["systemname"] = buf1.sysname;
   json_out["nodename"] = buf1.nodename;
   json_out["version"] = buf1.version;
   json_out["release"] = buf1.release;
   json_out["version"] = buf1.version;
   json_out["machine"] = buf1.machine;
   return json_out.dump();
}
