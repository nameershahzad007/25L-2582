#ifndef HOSPITALSYSTEM_H
#define HOSPITALSYSTEM_H

#include "Admin.h"
#include "Appointment.h"
#include "Bill.h"
#include "Doctor.h"
#include "FileHandler.h"
#include "Patient.h"
#include "Prescription.h"
#include "Storage.h"
#include "Validator.h"

class HospitalSystem
{
private:
    Storage<Patient> patients;
    Storage<Doctor> doctors;
    Storage<Admin> admins;
    Storage<Appointment> appointments;
    Storage<Prescription> prescriptions;
    Storage<Bill> bills;
    FileHandler fileHandler;
    Validator validator;

    Patient *currentPatient;
    Doctor *currentDoctor;
    Admin *currentAdmin;
    int currentRole;
    int failedLoginCount;
    int failedLoginRole;
    int failedLoginId;

    char patientsFile[260];
    char doctorsFile[260];
    char adminFile[260];
    char appointmentsFile[260];
    char prescriptionsFile[260];
    char billsFile[260];
    char securityLogFile[260];
    char dischargedFile[260];

    Patient *findPatientById(int id);
    Doctor *findDoctorById(int id);
    Admin *findAdminById(int id);
    Appointment *findAppointmentById(int id);
    Bill *findBillById(int id);
    Bill *findBillByAppointmentId(int appointmentId);
    const Patient *findPatientById(int id) const;
    const Doctor *findDoctorById(int id) const;
    const Appointment *findAppointmentById(int id) const;
    bool hasPrescriptionForAppointment(int appointmentId) const;
    void getTodayDate(char *buffer, int bufferSize) const;
    void getCurrentTimestamp(char *buffer, int bufferSize) const;
    void sortAppointmentsByDate(bool ascending, Appointment *list, int count) const;
    void sortAppointmentsByTime(Appointment *list, int count) const;
    void sortBillsByDate(Bill *list, int count, bool ascending) const;
    void sortPrescriptionsByDate(Prescription *list, int count, bool ascending) const;

public:
    HospitalSystem();

    bool initialize(char *message, int messageSize);
    bool login(int role, const char *idText, const char *password, char *message, int messageSize);
    void logout(char *message, int messageSize);

    int getCurrentRole() const;
    const char *getCurrentUserName() const;
    const char *getCurrentDoctorSpecialization() const;
    float getCurrentPatientBalance() const;
    void buildWelcomeText(char *buffer, int bufferSize) const;

    void listDoctorsBySpecialization(const char *specialization, char *buffer, int bufferSize) const;
    void listAvailableSlots(int doctorId, const char *date, char *buffer, int bufferSize) const;
    void viewPendingAppointmentsForCurrentPatient(char *buffer, int bufferSize) const;
    void viewUnpaidBillsForCurrentPatient(char *buffer, int bufferSize) const;
    void viewTodayPendingAppointmentsForDoctor(char *buffer, int bufferSize) const;

    bool bookAppointment(const char *specialization, const char *doctorIdText, const char *date, const char *timeSlot, char *message, int messageSize);
    bool cancelAppointment(const char *appointmentIdText, char *message, int messageSize);
    void viewMyAppointments(char *buffer, int bufferSize) const;
    void viewMyMedicalRecords(char *buffer, int bufferSize) const;
    void viewMyBills(char *buffer, int bufferSize) const;
    bool payBill(const char *billIdText, char *message, int messageSize);
    bool topUpBalance(const char *amountText, char *message, int messageSize);

    void viewTodayAppointments(char *buffer, int bufferSize) const;
    bool markAppointmentComplete(const char *appointmentIdText, char *message, int messageSize);
    bool markAppointmentNoShow(const char *appointmentIdText, char *message, int messageSize);
    bool writePrescription(const char *appointmentIdText, const char *medicines, const char *notes, char *message, int messageSize);
    bool viewPatientMedicalHistory(const char *patientIdText, char *buffer, int bufferSize) const;

    bool addDoctor(const char *name, const char *specialization, const char *contact, const char *password, const char *feeText, char *message, int messageSize);
    bool removeDoctor(const char *doctorIdText, char *message, int messageSize);
    void viewAllPatients(char *buffer, int bufferSize) const;
    void viewAllDoctors(char *buffer, int bufferSize) const;
    void viewAllAppointments(char *buffer, int bufferSize) const;
    void viewUnpaidBills(char *buffer, int bufferSize) const;
    bool dischargePatient(const char *patientIdText, char *message, int messageSize);
    void viewSecurityLog(char *buffer, int bufferSize) const;
    void generateDailyReport(char *buffer, int bufferSize) const;
};

#endif
