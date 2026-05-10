#include "../include/Prescription.h"
#include "../include/TextUtil.h"

Prescription::Prescription()
{
    prescriptionId = 0;
    appointmentId = 0;
    patientId = 0;
    doctorId = 0;
    TextUtil::copy(date, "", 11);
    TextUtil::copy(medicines, "", 500);
    TextUtil::copy(notes, "", 300);
}

Prescription::Prescription(int newPrescriptionId, int newAppointmentId, int newPatientId, int newDoctorId, const char *newDate, const char *newMedicines, const char *newNotes)
{
    prescriptionId = newPrescriptionId;
    appointmentId = newAppointmentId;
    patientId = newPatientId;
    doctorId = newDoctorId;
    TextUtil::copy(date, newDate, 11);
    TextUtil::copy(medicines, newMedicines, 500);
    TextUtil::copy(notes, newNotes, 300);
}

int Prescription::getId() const
{
    return prescriptionId;
}

int Prescription::getAppointmentId() const
{
    return appointmentId;
}

int Prescription::getPatientId() const
{
    return patientId;
}

int Prescription::getDoctorId() const
{
    return doctorId;
}

const char *Prescription::getDate() const
{
    return date;
}

const char *Prescription::getMedicines() const
{
    return medicines;
}

const char *Prescription::getNotes() const
{
    return notes;
}

void Prescription::setId(int value)
{
    prescriptionId = value;
}

void Prescription::setAppointmentId(int value)
{
    appointmentId = value;
}

void Prescription::setPatientId(int value)
{
    patientId = value;
}

void Prescription::setDoctorId(int value)
{
    doctorId = value;
}

void Prescription::setDate(const char *value)
{
    TextUtil::copy(date, value, 11);
}

void Prescription::setMedicines(const char *value)
{
    TextUtil::copy(medicines, value, 500);
}

void Prescription::setNotes(const char *value)
{
    TextUtil::copy(notes, value, 300);
}
