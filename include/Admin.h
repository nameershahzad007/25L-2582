#ifndef ADMIN_H
#define ADMIN_H

#include "Person.h"

class Admin : public Person
{
public:
    Admin();
    Admin(int adminId, const char *adminName, const char *adminPassword);

    const char *getRole() const;
    void getDisplayText(char *buffer, int bufferSize) const;
};

#endif
