#ifndef HOSPITALEXCEPTION_H
#define HOSPITALEXCEPTION_H

class HospitalException
{
protected:
    char message[200];

public:
    HospitalException();
    HospitalException(const char *newMessage);
    virtual ~HospitalException();
    virtual const char *what() const;
};

#endif
