#ifndef DOCTOR_H
#define DOCTOR_H

#include "Person.h"
#include <iostream>

class Doctor : public Person
{
private:
    char specialization[51];
    float fee;

public:
    Doctor();
    Doctor(int doctorId, const char *doctorName, const char *doctorSpecialization, const char *doctorContact, const char *doctorPassword, float doctorFee);

    const char *getSpecialization() const;
    float getFee() const;

    void setSpecialization(const char *value);
    void setFee(float value);

    bool operator==(const Doctor &other) const;

    const char *getRole() const;
    void getDisplayText(char *buffer, int bufferSize) const;

    friend std::ostream &operator<<(std::ostream &output, const Doctor &doctor);
};

#endif
