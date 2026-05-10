#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

class Prescription
{
private:
    int prescriptionId;
    int appointmentId;
    int patientId;
    int doctorId;
    char date[11];
    char medicines[500];
    char notes[300];

public:
    Prescription();
    Prescription(int newPrescriptionId, int newAppointmentId, int newPatientId, int newDoctorId, const char *newDate, const char *newMedicines, const char *newNotes);

    int getId() const;
    int getAppointmentId() const;
    int getPatientId() const;
    int getDoctorId() const;
    const char *getDate() const;
    const char *getMedicines() const;
    const char *getNotes() const;

    void setId(int value);
    void setAppointmentId(int value);
    void setPatientId(int value);
    void setDoctorId(int value);
    void setDate(const char *value);
    void setMedicines(const char *value);
    void setNotes(const char *value);
};

#endif
