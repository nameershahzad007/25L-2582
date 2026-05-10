#include "../include/FileNotFoundException.h"

FileNotFoundException::FileNotFoundException() : HospitalException("Required file could not be opened.")
{
}

FileNotFoundException::FileNotFoundException(const char *newMessage) : HospitalException(newMessage)
{
}
