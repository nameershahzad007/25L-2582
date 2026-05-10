#ifndef BILL_H
#define BILL_H

class Bill
{
private:
    int billId;
    int patientId;
    int appointmentId;
    float amount;
    char status[20];
    char date[11];

public:
    Bill();
    Bill(int newBillId, int newPatientId, int newAppointmentId, float newAmount, const char *newStatus, const char *newDate);

    int getId() const;
    int getPatientId() const;
    int getAppointmentId() const;
    float getAmount() const;
    const char *getStatus() const;
    const char *getDate() const;

    void setId(int value);
    void setPatientId(int value);
    void setAppointmentId(int value);
    void setAmount(float value);
    void setStatus(const char *value);
    void setDate(const char *value);
};

#endif
