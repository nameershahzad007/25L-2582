#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "Admin.h"
#include "Appointment.h"
#include "Bill.h"
#include "Doctor.h"
#include "Patient.h"
#include "Prescription.h"
#include "Storage.h"

class FileHandler
{
public:
    FileHandler();

    void loadPatients(const char *filePath, Storage<Patient> &patients) const;
    void loadDoctors(const char *filePath, Storage<Doctor> &doctors) const;
    void loadAdmins(const char *filePath, Storage<Admin> &admins) const;
    void loadAppointments(const char *filePath, Storage<Appointment> &appointments) const;
    void loadPrescriptions(const char *filePath, Storage<Prescription> &prescriptions) const;
    void loadBills(const char *filePath, Storage<Bill> &bills) const;

    void savePatients(const char *filePath, const Storage<Patient> &patients) const;
    void saveDoctors(const char *filePath, const Storage<Doctor> &doctors) const;
    void saveAdmins(const char *filePath, const Storage<Admin> &admins) const;
    void saveAppointments(const char *filePath, const Storage<Appointment> &appointments) const;
    void savePrescriptions(const char *filePath, const Storage<Prescription> &prescriptions) const;
    void saveBills(const char *filePath, const Storage<Bill> &bills) const;

    void appendAppointment(const char *filePath, const Appointment &appointment) const;
    void appendBill(const char *filePath, const Bill &bill) const;
    void appendPrescription(const char *filePath, const Prescription &prescription) const;
    void appendSecurityLog(const char *filePath, const char *timestamp, const char *role, int enteredId, const char *result) const;
    void appendArchiveLine(const char *filePath, const char *line) const;
    void readFileText(const char *filePath, char *buffer, int bufferSize) const;
    int getNextId(const char *filePath) const;
};

#endif
