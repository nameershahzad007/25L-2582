#include "../include/Bill.h"
#include "../include/TextUtil.h"

Bill::Bill()
{
    billId = 0;
    patientId = 0;
    appointmentId = 0;
    amount = 0.0f;
    TextUtil::copy(status, "", 20);
    TextUtil::copy(date, "", 11);
}

Bill::Bill(int newBillId, int newPatientId, int newAppointmentId, float newAmount, const char *newStatus, const char *newDate)
{
    billId = newBillId;
    patientId = newPatientId;
    appointmentId = newAppointmentId;
    amount = newAmount;
    TextUtil::copy(status, newStatus, 20);
    TextUtil::copy(date, newDate, 11);
}

int Bill::getId() const
{
    return billId;
}

int Bill::getPatientId() const
{
    return patientId;
}

int Bill::getAppointmentId() const
{
    return appointmentId;
}

float Bill::getAmount() const
{
    return amount;
}

const char *Bill::getStatus() const
{
    return status;
}

const char *Bill::getDate() const
{
    return date;
}

void Bill::setId(int value)
{
    billId = value;
}

void Bill::setPatientId(int value)
{
    patientId = value;
}

void Bill::setAppointmentId(int value)
{
    appointmentId = value;
}

void Bill::setAmount(float value)
{
    amount = value;
}

void Bill::setStatus(const char *value)
{
    TextUtil::copy(status, value, 20);
}

void Bill::setDate(const char *value)
{
    TextUtil::copy(date, value, 11);
}
