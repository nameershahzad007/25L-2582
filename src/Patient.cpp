#include "../include/Patient.h"
#include "../include/TextUtil.h"

#include <cstdio>

Patient::Patient() : Person()
{
    age = 0;
    TextUtil::copy(gender, "", 10);
    balance = 0.0f;
}

Patient::Patient(int patientId, const char *patientName, int patientAge, const char *patientGender, const char *patientContact, const char *patientPassword, float patientBalance)
    : Person(patientId, patientName, patientContact, patientPassword)
{
    age = patientAge;
    TextUtil::copy(gender, patientGender, 10);
    balance = patientBalance;
}

int Patient::getAge() const
{
    return age;
}

const char *Patient::getGender() const
{
    return gender;
}

float Patient::getBalance() const
{
    return balance;
}

void Patient::setAge(int value)
{
    age = value;
}

void Patient::setGender(const char *value)
{
    TextUtil::copy(gender, value, 10);
}

void Patient::setBalance(float value)
{
    balance = value;
}

Patient &Patient::operator+=(float amount)
{
    balance = balance + amount;
    return *this;
}

Patient &Patient::operator-=(float amount)
{
    balance = balance - amount;
    return *this;
}

bool Patient::operator==(const Patient &other) const
{
    return id == other.id;
}

const char *Patient::getRole() const
{
    return "Patient";
}

void Patient::getDisplayText(char *buffer, int bufferSize) const
{
    std::snprintf(buffer, bufferSize, "Patient ID: %d | Name: %s | Age: %d | Gender: %s | Contact: %s | Balance: %.2f", id, name, age, gender, contact, balance);
}

std::ostream &operator<<(std::ostream &output, const Patient &patient)
{
    output << "Patient ID: " << patient.id
           << " | Name: " << patient.name
           << " | Age: " << patient.age
           << " | Gender: " << patient.gender
           << " | Contact: " << patient.contact
           << " | Balance: PKR " << patient.balance;
    return output;
}
