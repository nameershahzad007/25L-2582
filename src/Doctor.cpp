#include "../include/Doctor.h"
#include "../include/TextUtil.h"

#include <cstdio>

Doctor::Doctor() : Person()
{
    TextUtil::copy(specialization, "", 51);
    fee = 0.0f;
}

Doctor::Doctor(int doctorId, const char *doctorName, const char *doctorSpecialization, const char *doctorContact, const char *doctorPassword, float doctorFee)
    : Person(doctorId, doctorName, doctorContact, doctorPassword)
{
    TextUtil::copy(specialization, doctorSpecialization, 51);
    fee = doctorFee;
}

const char *Doctor::getSpecialization() const
{
    return specialization;
}

float Doctor::getFee() const
{
    return fee;
}

void Doctor::setSpecialization(const char *value)
{
    TextUtil::copy(specialization, value, 51);
}

void Doctor::setFee(float value)
{
    fee = value;
}

bool Doctor::operator==(const Doctor &other) const
{
    return id == other.id;
}

const char *Doctor::getRole() const
{
    return "Doctor";
}

void Doctor::getDisplayText(char *buffer, int bufferSize) const
{
    std::snprintf(buffer, bufferSize, "Doctor ID: %d | Name: %s | Specialization: %s | Contact: %s | Fee: %.2f", id, name, specialization, contact, fee);
}

std::ostream &operator<<(std::ostream &output, const Doctor &doctor)
{
    output << "Doctor ID: " << doctor.id
           << " | Name: " << doctor.name
           << " | Specialization: " << doctor.specialization
           << " | Contact: " << doctor.contact
           << " | Fee: PKR " << doctor.fee;
    return output;
}
