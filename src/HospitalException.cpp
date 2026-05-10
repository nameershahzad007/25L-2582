#include "../include/HospitalException.h"
#include "../include/TextUtil.h"

HospitalException::HospitalException()
{
    TextUtil::copy(message, "Hospital exception", 200);
}

HospitalException::HospitalException(const char *newMessage)
{
    TextUtil::copy(message, newMessage, 200);
}

HospitalException::~HospitalException()
{
}

const char *HospitalException::what() const
{
    return message;
}
