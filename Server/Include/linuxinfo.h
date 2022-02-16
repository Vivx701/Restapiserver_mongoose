#ifndef LINUXINFO_H
#define LINUXINFO_H

#include <string>
#include <sys/sysinfo.h>
#include <json.hpp>
#include <unistd.h>
#include <limits.h>
#include<sys/utsname.h>

class LinuxInfo
{
public:
    LinuxInfo();
    std::string getMemInfo();
    std::string getHostname();
    std::string getSystemInfo();
};

#endif // LINUXINFO_H
