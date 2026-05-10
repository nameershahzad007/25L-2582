#ifndef PATIENT_H
#define PATIENT_H

#include "Person.h"
#include <iostream>

class Patient : public Person
{
private:
    int age;
    char gender[10];
    float balance;

public:
    Patient();
    Patient(int patientId, const char *patientName, int patientAge, const char *patientGender, const char *patientContact, const char *patientPassword, float patientBalance);

    int getAge() const;
    const char *getGender() const;
    float getBalance() const;

    void setAge(int value);
    void setGender(const char *value);
    void setBalance(float value);

    Patient &operator+=(float amount);
    Patient &operator-=(float amount);
    bool operator==(const Patient &other) const;

    const char *getRole() const;
    void getDisplayText(char *buffer, int bufferSize) const;

    friend std::ostream &operator<<(std::ostream &output, const Patient &patient);
};

#endif
