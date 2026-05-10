#include "../include/Appointment.h"
#include "../include/TextUtil.h"

Appointment::Appointment()
{
    appointmentId = 0;
    patientId = 0;
    doctorId = 0;
    TextUtil::copy(date, "", 11);
    TextUtil::copy(timeSlot, "", 6);
    TextUtil::copy(status, "", 20);
}

Appointment::Appointment(int newAppointmentId, int newPatientId, int newDoctorId, const char *newDate, const char *newTimeSlot, const char *newStatus)
{
    appointmentId = newAppointmentId;
    patientId = newPatientId;
    doctorId = newDoctorId;
    TextUtil::copy(date, newDate, 11);
    TextUtil::copy(timeSlot, newTimeSlot, 6);
    TextUtil::copy(status, newStatus, 20);
}

int Appointment::getId() const
{
    return appointmentId;
}

int Appointment::getPatientId() const
{
    return patientId;
}

int Appointment::getDoctorId() const
{
    return doctorId;
}

const char *Appointment::getDate() const
{
    return date;
}

const char *Appointment::getTimeSlot() const
{
    return timeSlot;
}

const char *Appointment::getStatus() const
{
    return status;
}

void Appointment::setId(int value)
{
    appointmentId = value;
}

void Appointment::setPatientId(int value)
{
    patientId = value;
}

void Appointment::setDoctorId(int value)
{
    doctorId = value;
}

void Appointment::setDate(const char *value)
{
    TextUtil::copy(date, value, 11);
}

void Appointment::setTimeSlot(const char *value)
{
    TextUtil::copy(timeSlot, value, 6);
}

void Appointment::setStatus(const char *value)
{
    TextUtil::copy(status, value, 20);
}

bool Appointment::operator==(const Appointment &other) const
{
    if (doctorId != other.doctorId)
    {
        return false;
    }

    if (!TextUtil::equals(date, other.date))
    {
        return false;
    }

    if (!TextUtil::equals(timeSlot, other.timeSlot))
    {
        return false;
    }

    if (TextUtil::equals(status, "cancelled") || TextUtil::equals(other.status, "cancelled"))
    {
        return false;
    }

    return true;
}

std::ostream &operator<<(std::ostream &output, const Appointment &appointment)
{
    output << "Appointment ID: " << appointment.appointmentId
           << " | Patient ID: " << appointment.patientId
           << " | Doctor ID: " << appointment.doctorId
           << " | Date: " << appointment.date
           << " | Time Slot: " << appointment.timeSlot
           << " | Status: " << appointment.status;
    return output;
}
