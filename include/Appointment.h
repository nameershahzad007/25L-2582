#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <iostream>

class Appointment
{
private:
    int appointmentId;
    int patientId;
    int doctorId;
    char date[11];
    char timeSlot[6];
    char status[20];

public:
    Appointment();
    Appointment(int newAppointmentId, int newPatientId, int newDoctorId, const char *newDate, const char *newTimeSlot, const char *newStatus);

    int getId() const;
    int getPatientId() const;
    int getDoctorId() const;
    const char *getDate() const;
    const char *getTimeSlot() const;
    const char *getStatus() const;

    void setId(int value);
    void setPatientId(int value);
    void setDoctorId(int value);
    void setDate(const char *value);
    void setTimeSlot(const char *value);
    void setStatus(const char *value);

    bool operator==(const Appointment &other) const;

    friend std::ostream &operator<<(std::ostream &output, const Appointment &appointment);
};

#endif
