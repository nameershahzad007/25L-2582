#include "../include/InsufficientFundsException.h"

InsufficientFundsException::InsufficientFundsException() : HospitalException("Insufficient funds.")
{
}

InsufficientFundsException::InsufficientFundsException(const char *newMessage) : HospitalException(newMessage)
{
}
