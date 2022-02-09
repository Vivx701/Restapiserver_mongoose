#ifndef LINUXINFO_H
#define LINUXINFO_H

#include <string>
#include <sys/sysinfo.h>
#include <json.hpp>
#include <unistd.h>
#include <limits.h>

class LinuxInfo
{
public:
    LinuxInfo();
    std::string getMemInfo();
    std::string getHostname();
};

#endif // LINUXINFO_H
