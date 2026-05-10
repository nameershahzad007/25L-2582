#include "../include/Admin.h"

#include <cstdio>

Admin::Admin() : Person()
{
}

Admin::Admin(int adminId, const char *adminName, const char *adminPassword)
    : Person(adminId, adminName, "", adminPassword)
{
}

const char *Admin::getRole() const
{
    return "Admin";
}

void Admin::getDisplayText(char *buffer, int bufferSize) const
{
    std::snprintf(buffer, bufferSize, "Admin ID: %d | Name: %s", id, name);
}
