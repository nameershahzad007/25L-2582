#include "../include/FileHandler.h"
#include "../include/FileNotFoundException.h"
#include "../include/TextUtil.h"

#include <fstream>

namespace
{
    const int MAX_LINE_LENGTH = 1500;
    const int MAX_FIELD_COUNT = 10;
    const int MAX_FIELD_LENGTH = 600;

    void clearFields(char fields[MAX_FIELD_COUNT][MAX_FIELD_LENGTH])
    {
        int row = 0;
        while (row < MAX_FIELD_COUNT)
        {
            fields[row][0] = '\0';
            row++;
        }
    }

    void splitCSV(const char *line, char fields[MAX_FIELD_COUNT][MAX_FIELD_LENGTH], int fieldCount)
    {
        clearFields(fields);

        int fieldIndex = 0;
        int charIndex = 0;
        int sourceIndex = 0;

        while (line[sourceIndex] != '\0' && fieldIndex < fieldCount)
        {
            if (line[sourceIndex] == ',')
            {
                fields[fieldIndex][charIndex] = '\0';
                fieldIndex++;
                charIndex = 0;
            }
            else if (charIndex < MAX_FIELD_LENGTH - 1)
            {
                fields[fieldIndex][charIndex] = line[sourceIndex];
                charIndex++;
            }
            sourceIndex++;
        }

        if (fieldIndex < fieldCount)
        {
            fields[fieldIndex][charIndex] = '\0';
        }
    }

    bool isHeaderLine(const char *line)
    {
        if (line == 0 || line[0] == '\0')
        {
            return true;
        }

        return !(line[0] >= '0' && line[0] <= '9');
    }
}

FileHandler::FileHandler()
{
}

void FileHandler::loadPatients(const char *filePath, Storage<Patient> &patients) const
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        throw FileNotFoundException("patients.txt could not be opened on startup.");
    }

    patients.clear();
    char line[MAX_LINE_LENGTH];
    char fields[MAX_FIELD_COUNT][MAX_FIELD_LENGTH];

    while (file.getline(line, MAX_LINE_LENGTH))
    {
        TextUtil::trimLineEnd(line);
        if (line[0] == '\0' || isHeaderLine(line))
        {
            continue;
        }

        splitCSV(line, fields, 7);
        Patient patient(TextUtil::toInt(fields[0]), fields[1], TextUtil::toInt(fields[2]), fields[3], fields[4], fields[5], TextUtil::toFloat(fields[6]));
        patients.add(patient);
    }
}

void FileHandler::loadDoctors(const char *filePath, Storage<Doctor> &doctors) const
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        throw FileNotFoundException("doctors.txt could not be opened on startup.");
    }

    doctors.clear();
    char line[MAX_LINE_LENGTH];
    char fields[MAX_FIELD_COUNT][MAX_FIELD_LENGTH];

    while (file.getline(line, MAX_LINE_LENGTH))
    {
        TextUtil::trimLineEnd(line);
        if (line[0] == '\0' || isHeaderLine(line))
        {
            continue;
        }

        splitCSV(line, fields, 6);
        Doctor doctor(TextUtil::toInt(fields[0]), fields[1], fields[2], fields[3], fields[4], TextUtil::toFloat(fields[5]));
        doctors.add(doctor);
    }
}

void FileHandler::loadAdmins(const char *filePath, Storage<Admin> &admins) const
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        throw FileNotFoundException("admin.txt could not be opened on startup.");
    }

    admins.clear();
    char line[MAX_LINE_LENGTH];
    char fields[MAX_FIELD_COUNT][MAX_FIELD_LENGTH];

    while (file.getline(line, MAX_LINE_LENGTH))
    {
        TextUtil::trimLineEnd(line);
        if (line[0] == '\0' || isHeaderLine(line))
        {
            continue;
        }

        splitCSV(line, fields, 3);
        Admin admin(TextUtil::toInt(fields[0]), fields[1], fields[2]);
        admins.add(admin);
    }
}

void FileHandler::loadAppointments(const char *filePath, Storage<Appointment> &appointments) const
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        throw FileNotFoundException("appointments.txt could not be opened on startup.");
    }

    appointments.clear();
    char line[MAX_LINE_LENGTH];
    char fields[MAX_FIELD_COUNT][MAX_FIELD_LENGTH];

    while (file.getline(line, MAX_LINE_LENGTH))
    {
        TextUtil::trimLineEnd(line);
        if (line[0] == '\0' || isHeaderLine(line))
        {
            continue;
        }

        splitCSV(line, fields, 6);
        Appointment appointment(TextUtil::toInt(fields[0]), TextUtil::toInt(fields[1]), TextUtil::toInt(fields[2]), fields[3], fields[4], fields[5]);
        appointments.add(appointment);
    }
}

void FileHandler::loadPrescriptions(const char *filePath, Storage<Prescription> &prescriptions) const
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        throw FileNotFoundException("prescriptions.txt could not be opened on startup.");
    }

    prescriptions.clear();
    char line[MAX_LINE_LENGTH];
    char fields[MAX_FIELD_COUNT][MAX_FIELD_LENGTH];

    while (file.getline(line, MAX_LINE_LENGTH))
    {
        TextUtil::trimLineEnd(line);
        if (line[0] == '\0' || isHeaderLine(line))
        {
            continue;
        }

        splitCSV(line, fields, 7);
        Prescription prescription(TextUtil::toInt(fields[0]), TextUtil::toInt(fields[1]), TextUtil::toInt(fields[2]), TextUtil::toInt(fields[3]), fields[4], fields[5], fields[6]);
        prescriptions.add(prescription);
    }
}

void FileHandler::loadBills(const char *filePath, Storage<Bill> &bills) const
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        throw FileNotFoundException("bills.txt could not be opened on startup.");
    }

    bills.clear();
    char line[MAX_LINE_LENGTH];
    char fields[MAX_FIELD_COUNT][MAX_FIELD_LENGTH];

    while (file.getline(line, MAX_LINE_LENGTH))
    {
        TextUtil::trimLineEnd(line);
        if (line[0] == '\0' || isHeaderLine(line))
        {
            continue;
        }

        splitCSV(line, fields, 6);
        Bill bill(TextUtil::toInt(fields[0]), TextUtil::toInt(fields[1]), TextUtil::toInt(fields[2]), TextUtil::toFloat(fields[3]), fields[4], fields[5]);
        bills.add(bill);
    }
}

void FileHandler::savePatients(const char *filePath, const Storage<Patient> &patients) const
{
    std::ofstream file(filePath);
    file << "patient_id,name,age,gender,contact,password,balance\n";

    int index = 0;
    const Patient *list = patients.getAll();
    while (index < patients.size())
    {
        file << list[index].getId() << "," << list[index].getName() << "," << list[index].getAge() << "," << list[index].getGender() << "," << list[index].getContact() << "," << list[index].getPassword() << "," << list[index].getBalance() << "\n";
        index++;
    }
}

void FileHandler::saveDoctors(const char *filePath, const Storage<Doctor> &doctors) const
{
    std::ofstream file(filePath);
    file << "doctor_id,name,specialization,contact,password,fee\n";

    int index = 0;
    const Doctor *list = doctors.getAll();
    while (index < doctors.size())
    {
        file << list[index].getId() << "," << list[index].getName() << "," << list[index].getSpecialization() << "," << list[index].getContact() << "," << list[index].getPassword() << "," << list[index].getFee() << "\n";
        index++;
    }
}

void FileHandler::saveAdmins(const char *filePath, const Storage<Admin> &admins) const
{
    std::ofstream file(filePath);
    file << "admin_id,name,password\n";

    int index = 0;
    const Admin *list = admins.getAll();
    while (index < admins.size())
    {
        file << list[index].getId() << "," << list[index].getName() << "," << list[index].getPassword() << "\n";
        index++;
    }
}

void FileHandler::saveAppointments(const char *filePath, const Storage<Appointment> &appointments) const
{
    std::ofstream file(filePath);
    file << "appointment_id,patient_id,doctor_id,date,time_slot,status\n";

    int index = 0;
    const Appointment *list = appointments.getAll();
    while (index < appointments.size())
    {
        file << list[index].getId() << "," << list[index].getPatientId() << "," << list[index].getDoctorId() << "," << list[index].getDate() << "," << list[index].getTimeSlot() << "," << list[index].getStatus() << "\n";
        index++;
    }
}

void FileHandler::savePrescriptions(const char *filePath, const Storage<Prescription> &prescriptions) const
{
    std::ofstream file(filePath);
    file << "prescription_id,appointment_id,patient_id,doctor_id,date,medicines,notes\n";

    int index = 0;
    const Prescription *list = prescriptions.getAll();
    while (index < prescriptions.size())
    {
        file << list[index].getId() << "," << list[index].getAppointmentId() << "," << list[index].getPatientId() << "," << list[index].getDoctorId() << "," << list[index].getDate() << "," << list[index].getMedicines() << "," << list[index].getNotes() << "\n";
        index++;
    }
}

void FileHandler::saveBills(const char *filePath, const Storage<Bill> &bills) const
{
    std::ofstream file(filePath);
    file << "bill_id,patient_id,appointment_id,amount,status,date\n";

    int index = 0;
    const Bill *list = bills.getAll();
    while (index < bills.size())
    {
        file << list[index].getId() << "," << list[index].getPatientId() << "," << list[index].getAppointmentId() << "," << list[index].getAmount() << "," << list[index].getStatus() << "," << list[index].getDate() << "\n";
        index++;
    }
}

void FileHandler::appendAppointment(const char *filePath, const Appointment &appointment) const
{
    std::ofstream file(filePath, std::ios::app);
    file << appointment.getId() << "," << appointment.getPatientId() << "," << appointment.getDoctorId() << "," << appointment.getDate() << "," << appointment.getTimeSlot() << "," << appointment.getStatus() << "\n";
}

void FileHandler::appendBill(const char *filePath, const Bill &bill) const
{
    std::ofstream file(filePath, std::ios::app);
    file << bill.getId() << "," << bill.getPatientId() << "," << bill.getAppointmentId() << "," << bill.getAmount() << "," << bill.getStatus() << "," << bill.getDate() << "\n";
}

void FileHandler::appendPrescription(const char *filePath, const Prescription &prescription) const
{
    std::ofstream file(filePath, std::ios::app);
    file << prescription.getId() << "," << prescription.getAppointmentId() << "," << prescription.getPatientId() << "," << prescription.getDoctorId() << "," << prescription.getDate() << "," << prescription.getMedicines() << "," << prescription.getNotes() << "\n";
}

void FileHandler::appendSecurityLog(const char *filePath, const char *timestamp, const char *role, int enteredId, const char *result) const
{
    std::ofstream file(filePath, std::ios::app);
    file << timestamp << "," << role << "," << enteredId << "," << result << "\n";
}

void FileHandler::appendArchiveLine(const char *filePath, const char *line) const
{
    std::ofstream file(filePath, std::ios::app);
    file << line << "\n";
}

void FileHandler::readFileText(const char *filePath, char *buffer, int bufferSize) const
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        throw FileNotFoundException("The requested text file could not be opened.");
    }

    TextUtil::clear(buffer);
    char line[MAX_LINE_LENGTH];
    while (file.getline(line, MAX_LINE_LENGTH))
    {
        TextUtil::appendLine(buffer, line, bufferSize);
    }
}

int FileHandler::getNextId(const char *filePath) const
{
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        throw FileNotFoundException("Could not open file while generating next ID.");
    }

    char line[MAX_LINE_LENGTH];
    char fields[MAX_FIELD_COUNT][MAX_FIELD_LENGTH];
    int maximum = 0;

    while (file.getline(line, MAX_LINE_LENGTH))
    {
        TextUtil::trimLineEnd(line);
        if (line[0] == '\0' || isHeaderLine(line))
        {
            continue;
        }

        splitCSV(line, fields, 1);
        int current = TextUtil::toInt(fields[0]);
        if (current > maximum)
        {
            maximum = current;
        }
    }

    return maximum + 1;
}
