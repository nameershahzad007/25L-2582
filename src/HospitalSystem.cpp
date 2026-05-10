#include "../include/HospitalSystem.h"
#include "../include/InsufficientFundsException.h"
#include "../include/InvalidInputException.h"
#include "../include/SlotUnavailableException.h"
#include "../include/TextUtil.h"

#include <cstdio>
#include <ctime>

HospitalSystem::HospitalSystem()
{
    currentPatient = 0;
    currentDoctor = 0;
    currentAdmin = 0;
    currentRole = 0;
    failedLoginCount = 0;
    failedLoginRole = 0;
    failedLoginId = 0;

    TextUtil::copy(patientsFile, "data/patients.txt", 260);
    TextUtil::copy(doctorsFile, "data/doctors.txt", 260);
    TextUtil::copy(adminFile, "data/admin.txt", 260);
    TextUtil::copy(appointmentsFile, "data/appointments.txt", 260);
    TextUtil::copy(prescriptionsFile, "data/prescriptions.txt", 260);
    TextUtil::copy(billsFile, "data/bills.txt", 260);
    TextUtil::copy(securityLogFile, "data/security_log.txt", 260);
    TextUtil::copy(dischargedFile, "data/discharged.txt", 260);
}

bool HospitalSystem::initialize(char *message, int messageSize)
{
    try
    {
        fileHandler.loadPatients(patientsFile, patients);
        fileHandler.loadDoctors(doctorsFile, doctors);
        fileHandler.loadAdmins(adminFile, admins);
        fileHandler.loadAppointments(appointmentsFile, appointments);
        fileHandler.loadPrescriptions(prescriptionsFile, prescriptions);
        fileHandler.loadBills(billsFile, bills);
        TextUtil::copy(message, "MediCore data loaded successfully.", messageSize);
        return true;
    }
    catch (HospitalException &exception)
    {
        TextUtil::copy(message, exception.what(), messageSize);
        return false;
    }
}

Patient *HospitalSystem::findPatientById(int id)
{
    return patients.findById(id);
}

Doctor *HospitalSystem::findDoctorById(int id)
{
    return doctors.findById(id);
}

Admin *HospitalSystem::findAdminById(int id)
{
    return admins.findById(id);
}

Appointment *HospitalSystem::findAppointmentById(int id)
{
    return appointments.findById(id);
}

Bill *HospitalSystem::findBillById(int id)
{
    return bills.findById(id);
}

Bill *HospitalSystem::findBillByAppointmentId(int appointmentId)
{
    int index = 0;
    Bill *list = bills.getAll();
    while (index < bills.size())
    {
        if (list[index].getAppointmentId() == appointmentId)
        {
            return &list[index];
        }
        index++;
    }
    return 0;
}

const Patient *HospitalSystem::findPatientById(int id) const
{
    return patients.findById(id);
}

const Doctor *HospitalSystem::findDoctorById(int id) const
{
    return doctors.findById(id);
}

const Appointment *HospitalSystem::findAppointmentById(int id) const
{
    return appointments.findById(id);
}

bool HospitalSystem::hasPrescriptionForAppointment(int appointmentId) const
{
    int index = 0;
    const Prescription *list = prescriptions.getAll();
    while (index < prescriptions.size())
    {
        if (list[index].getAppointmentId() == appointmentId)
        {
            return true;
        }
        index++;
    }
    return false;
}

void HospitalSystem::getTodayDate(char *buffer, int bufferSize) const
{
    std::time_t now = std::time(0);
    std::tm *currentTime = std::localtime(&now);
    std::strftime(buffer, bufferSize, "%d-%m-%Y", currentTime);
}

void HospitalSystem::getCurrentTimestamp(char *buffer, int bufferSize) const
{
    std::time_t now = std::time(0);
    std::tm *currentTime = std::localtime(&now);
    std::strftime(buffer, bufferSize, "%d-%m-%Y %H:%M:%S", currentTime);
}

void HospitalSystem::sortAppointmentsByDate(bool ascending, Appointment *list, int count) const
{
    int outer = 0;
    while (outer < count - 1)
    {
        int inner = 0;
        while (inner < count - outer - 1)
        {
            int compare = TextUtil::compareDateAscending(list[inner].getDate(), list[inner + 1].getDate());
            bool shouldSwap = ascending ? (compare > 0) : (compare < 0);
            if (!shouldSwap && compare == 0)
            {
                shouldSwap = TextUtil::compareTimeAscending(list[inner].getTimeSlot(), list[inner + 1].getTimeSlot()) > 0;
            }

            if (shouldSwap)
            {
                Appointment temp = list[inner];
                list[inner] = list[inner + 1];
                list[inner + 1] = temp;
            }
            inner++;
        }
        outer++;
    }
}

void HospitalSystem::sortAppointmentsByTime(Appointment *list, int count) const
{
    int outer = 0;
    while (outer < count - 1)
    {
        int inner = 0;
        while (inner < count - outer - 1)
        {
            if (TextUtil::compareTimeAscending(list[inner].getTimeSlot(), list[inner + 1].getTimeSlot()) > 0)
            {
                Appointment temp = list[inner];
                list[inner] = list[inner + 1];
                list[inner + 1] = temp;
            }
            inner++;
        }
        outer++;
    }
}

void HospitalSystem::sortBillsByDate(Bill *list, int count, bool ascending) const
{
    int outer = 0;
    while (outer < count - 1)
    {
        int inner = 0;
        while (inner < count - outer - 1)
        {
            int compare = TextUtil::compareDateAscending(list[inner].getDate(), list[inner + 1].getDate());
            bool shouldSwap = ascending ? (compare > 0) : (compare < 0);
            if (shouldSwap)
            {
                Bill temp = list[inner];
                list[inner] = list[inner + 1];
                list[inner + 1] = temp;
            }
            inner++;
        }
        outer++;
    }
}

void HospitalSystem::sortPrescriptionsByDate(Prescription *list, int count, bool ascending) const
{
    int outer = 0;
    while (outer < count - 1)
    {
        int inner = 0;
        while (inner < count - outer - 1)
        {
            int compare = TextUtil::compareDateAscending(list[inner].getDate(), list[inner + 1].getDate());
            bool shouldSwap = ascending ? (compare > 0) : (compare < 0);
            if (shouldSwap)
            {
                Prescription temp = list[inner];
                list[inner] = list[inner + 1];
                list[inner + 1] = temp;
            }
            inner++;
        }
        outer++;
    }
}

bool HospitalSystem::login(int role, const char *idText, const char *password, char *message, int messageSize)
{
    int id = TextUtil::toInt(idText);
    if (!validator.isValidId(id))
    {
        TextUtil::copy(message, "Invalid ID.", messageSize);
        return false;
    }

    currentPatient = 0;
    currentDoctor = 0;
    currentAdmin = 0;

    bool success = false;
    if (role == 1)
    {
        Patient *patient = findPatientById(id);
        if (patient != 0 && TextUtil::equals(patient->getPassword(), password))
        {
            currentPatient = patient;
            currentRole = 1;
            success = true;
        }
    }
    else if (role == 2)
    {
        Doctor *doctor = findDoctorById(id);
        if (doctor != 0 && TextUtil::equals(doctor->getPassword(), password))
        {
            currentDoctor = doctor;
            currentRole = 2;
            success = true;
        }
    }
    else if (role == 3)
    {
        Admin *admin = findAdminById(id);
        if (admin != 0 && TextUtil::equals(admin->getPassword(), password))
        {
            currentAdmin = admin;
            currentRole = 3;
            success = true;
        }
    }

    if (success)
    {
        failedLoginCount = 0;
        failedLoginRole = 0;
        failedLoginId = 0;
        TextUtil::copy(message, "Login successful.", messageSize);
        return true;
    }

    if (failedLoginRole == role && failedLoginId == id)
    {
        failedLoginCount++;
    }
    else
    {
        failedLoginRole = role;
        failedLoginId = id;
        failedLoginCount = 1;
    }

    if (failedLoginCount >= 3)
    {
        char timestamp[50];
        getCurrentTimestamp(timestamp, 50);
        const char *roleName = role == 1 ? "Patient" : (role == 2 ? "Doctor" : "Admin");
        fileHandler.appendSecurityLog(securityLogFile, timestamp, roleName, id, "FAILED");
        failedLoginCount = 0;
        TextUtil::copy(message, "Account locked. Contact admin.", messageSize);
    }
    else
    {
        TextUtil::copy(message, "Invalid ID or password.", messageSize);
    }

    currentRole = 0;
    return false;
}

void HospitalSystem::logout(char *message, int messageSize)
{
    currentPatient = 0;
    currentDoctor = 0;
    currentAdmin = 0;
    currentRole = 0;
    TextUtil::copy(message, "Logged out successfully.", messageSize);
}

int HospitalSystem::getCurrentRole() const
{
    return currentRole;
}

const char *HospitalSystem::getCurrentUserName() const
{
    if (currentRole == 1 && currentPatient != 0)
    {
        return currentPatient->getName();
    }
    if (currentRole == 2 && currentDoctor != 0)
    {
        return currentDoctor->getName();
    }
    if (currentRole == 3 && currentAdmin != 0)
    {
        return currentAdmin->getName();
    }
    return "";
}

const char *HospitalSystem::getCurrentDoctorSpecialization() const
{
    if (currentDoctor != 0)
    {
        return currentDoctor->getSpecialization();
    }
    return "";
}

float HospitalSystem::getCurrentPatientBalance() const
{
    if (currentPatient != 0)
    {
        return currentPatient->getBalance();
    }
    return 0.0f;
}

void HospitalSystem::buildWelcomeText(char *buffer, int bufferSize) const
{
    if (currentRole == 1 && currentPatient != 0)
    {
        std::snprintf(buffer, bufferSize, "Welcome, %s\nBalance: PKR %.2f", currentPatient->getName(), currentPatient->getBalance());
    }
    else if (currentRole == 2 && currentDoctor != 0)
    {
        std::snprintf(buffer, bufferSize, "Welcome, Dr. %s\nSpecialization: %s", currentDoctor->getName(), currentDoctor->getSpecialization());
    }
    else if (currentRole == 3)
    {
        std::snprintf(buffer, bufferSize, "Admin Panel - MediCore\nLogged in as: %s", currentAdmin != 0 ? currentAdmin->getName() : "Admin");
    }
    else
    {
        TextUtil::copy(buffer, "Welcome to MediCore Hospital Management System", bufferSize);
    }
}

void HospitalSystem::listDoctorsBySpecialization(const char *specialization, char *buffer, int bufferSize) const
{
    TextUtil::clear(buffer);
    if (specialization == 0 || specialization[0] == '\0')
    {
        TextUtil::copy(buffer, "Enter specialization to search.", bufferSize);
        return;
    }

    int index = 0;
    bool found = false;
    const Doctor *list = doctors.getAll();
    while (index < doctors.size())
    {
        if (TextUtil::equalsIgnoreCase(list[index].getSpecialization(), specialization))
        {
            char line[250];
            std::snprintf(line, 250, "Doctor ID: %d | Name: %s | Fee: PKR %.2f", list[index].getId(), list[index].getName(), list[index].getFee());
            TextUtil::appendLine(buffer, line, bufferSize);
            found = true;
        }
        index++;
    }

    if (!found)
    {
        TextUtil::copy(buffer, "No doctors available for that specialization.", bufferSize);
    }
}

void HospitalSystem::listAvailableSlots(int doctorId, const char *date, char *buffer, int bufferSize) const
{
    TextUtil::clear(buffer);
    if (!validator.isValidId(doctorId) || !validator.isValidDate(date))
    {
        TextUtil::copy(buffer, "Enter a valid doctor ID and date to see available slots.", bufferSize);
        return;
    }

    const char *slots[8] = {"09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00"};
    bool any = false;

    TextUtil::appendLine(buffer, "Available time slots:", bufferSize);
    int slotIndex = 0;
    while (slotIndex < 8)
    {
        bool taken = false;
        Appointment candidate(0, 0, doctorId, date, slots[slotIndex], "pending");
        int index = 0;
        const Appointment *list = appointments.getAll();
        while (index < appointments.size())
        {
            if (candidate == list[index])
            {
                taken = true;
                break;
            }
            index++;
        }

        if (!taken)
        {
            TextUtil::appendLine(buffer, slots[slotIndex], bufferSize);
            any = true;
        }
        slotIndex++;
    }

    if (!any)
    {
        TextUtil::copy(buffer, "No available slots for the selected doctor and date.", bufferSize);
    }
}

void HospitalSystem::viewPendingAppointmentsForCurrentPatient(char *buffer, int bufferSize) const
{
    TextUtil::clear(buffer);
    if (currentPatient == 0)
    {
        TextUtil::copy(buffer, "Patient is not logged in.", bufferSize);
        return;
    }

    bool found = false;
    int index = 0;
    const Appointment *list = appointments.getAll();
    while (index < appointments.size())
    {
        if (list[index].getPatientId() == currentPatient->getId() && TextUtil::equals(list[index].getStatus(), "pending"))
        {
            const Doctor *doctor = findDoctorById(list[index].getDoctorId());
            char line[250];
            std::snprintf(line, 250, "Appointment ID: %d | Doctor: %s | Date: %s | Time Slot: %s",
                          list[index].getId(),
                          doctor != 0 ? doctor->getName() : "Unknown",
                          list[index].getDate(),
                          list[index].getTimeSlot());
            TextUtil::appendLine(buffer, line, bufferSize);
            found = true;
        }
        index++;
    }

    if (!found)
    {
        TextUtil::copy(buffer, "You have no pending appointments.", bufferSize);
    }
}

void HospitalSystem::viewUnpaidBillsForCurrentPatient(char *buffer, int bufferSize) const
{
    TextUtil::clear(buffer);
    if (currentPatient == 0)
    {
        TextUtil::copy(buffer, "Patient is not logged in.", bufferSize);
        return;
    }

    bool found = false;
    int index = 0;
    const Bill *list = bills.getAll();
    while (index < bills.size())
    {
        if (list[index].getPatientId() == currentPatient->getId() && TextUtil::equals(list[index].getStatus(), "unpaid"))
        {
            char line[220];
            std::snprintf(line, 220, "Bill ID: %d | Appointment ID: %d | Amount: PKR %.2f | Date: %s",
                          list[index].getId(),
                          list[index].getAppointmentId(),
                          list[index].getAmount(),
                          list[index].getDate());
            TextUtil::appendLine(buffer, line, bufferSize);
            found = true;
        }
        index++;
    }

    if (!found)
    {
        TextUtil::copy(buffer, "No unpaid bills.", bufferSize);
    }
}

void HospitalSystem::viewTodayPendingAppointmentsForDoctor(char *buffer, int bufferSize) const
{
    TextUtil::clear(buffer);
    if (currentDoctor == 0)
    {
        TextUtil::copy(buffer, "Doctor is not logged in.", bufferSize);
        return;
    }

    char today[20];
    getTodayDate(today, 20);

    Appointment *temp = new Appointment[appointments.size()];
    int count = 0;
    int index = 0;
    const Appointment *list = appointments.getAll();
    while (index < appointments.size())
    {
        if (list[index].getDoctorId() == currentDoctor->getId() &&
            TextUtil::equals(list[index].getDate(), today) &&
            TextUtil::equals(list[index].getStatus(), "pending"))
        {
            temp[count] = list[index];
            count++;
        }
        index++;
    }

    if (count == 0)
    {
        delete[] temp;
        TextUtil::copy(buffer, "No pending appointments for today.", bufferSize);
        return;
    }

    sortAppointmentsByTime(temp, count);
    index = 0;
    while (index < count)
    {
        const Patient *patient = findPatientById(temp[index].getPatientId());
        char line[250];
        std::snprintf(line, 250, "Appointment ID: %d | Patient: %s | Time Slot: %s",
                      temp[index].getId(),
                      patient != 0 ? patient->getName() : "Unknown",
                      temp[index].getTimeSlot());
        TextUtil::appendLine(buffer, line, bufferSize);
        index++;
    }

    delete[] temp;
}

bool HospitalSystem::bookAppointment(const char *specialization, const char *doctorIdText, const char *date, const char *timeSlot, char *message, int messageSize)
{
    if (currentPatient == 0)
    {
        TextUtil::copy(message, "Patient is not logged in.", messageSize);
        return false;
    }

    int doctorId = TextUtil::toInt(doctorIdText);
    Doctor *doctor = findDoctorById(doctorId);
    if (doctor == 0)
    {
        TextUtil::copy(message, "Doctor not found.", messageSize);
        return false;
    }

    if (!TextUtil::equalsIgnoreCase(doctor->getSpecialization(), specialization))
    {
        TextUtil::copy(message, "Doctor does not match the searched specialization.", messageSize);
        return false;
    }

    if (!validator.isValidDate(date))
    {
        TextUtil::copy(message, "Invalid date. Use format DD-MM-YYYY.", messageSize);
        return false;
    }

    if (!validator.isValidTimeSlot(timeSlot))
    {
        TextUtil::copy(message, "Invalid time slot.", messageSize);
        return false;
    }

    try
    {
        Appointment candidate(0, currentPatient->getId(), doctorId, date, timeSlot, "pending");
        int index = 0;
        const Appointment *list = appointments.getAll();
        while (index < appointments.size())
        {
            if (candidate == list[index])
            {
                throw SlotUnavailableException("This slot is already taken. Please select another available slot.");
            }
            index++;
        }

        if (currentPatient->getBalance() < doctor->getFee())
        {
            throw InsufficientFundsException("Insufficient funds. Please top up your balance first.");
        }

        (*currentPatient) -= doctor->getFee();

        int appointmentId = fileHandler.getNextId(appointmentsFile);
        Appointment newAppointment(appointmentId, currentPatient->getId(), doctorId, date, timeSlot, "pending");
        appointments.add(newAppointment);
        fileHandler.appendAppointment(appointmentsFile, newAppointment);

        int billId = fileHandler.getNextId(billsFile);
        Bill newBill(billId, currentPatient->getId(), appointmentId, doctor->getFee(), "unpaid", date);
        bills.add(newBill);
        fileHandler.appendBill(billsFile, newBill);

        fileHandler.savePatients(patientsFile, patients);
        std::snprintf(message, messageSize, "Appointment booked successfully. Appointment ID: %d.", appointmentId);
        return true;
    }
    catch (HospitalException &exception)
    {
        TextUtil::copy(message, exception.what(), messageSize);
        if (TextUtil::equals(exception.what(), "This slot is already taken. Please select another available slot."))
        {
            char slotsText[4000];
            listAvailableSlots(doctorId, date, slotsText, 4000);
            TextUtil::append(message, "\n", messageSize);
            TextUtil::append(message, slotsText, messageSize);
        }
        return false;
    }
}

bool HospitalSystem::cancelAppointment(const char *appointmentIdText, char *message, int messageSize)
{
    if (currentPatient == 0)
    {
        TextUtil::copy(message, "Patient is not logged in.", messageSize);
        return false;
    }

    int appointmentId = TextUtil::toInt(appointmentIdText);
    Appointment *appointment = findAppointmentById(appointmentId);
    if (appointment == 0 || appointment->getPatientId() != currentPatient->getId() || !TextUtil::equals(appointment->getStatus(), "pending"))
    {
        TextUtil::copy(message, "Invalid appointment ID.", messageSize);
        return false;
    }

    Doctor *doctor = findDoctorById(appointment->getDoctorId());
    appointment->setStatus("cancelled");
    if (doctor != 0)
    {
        (*currentPatient) += doctor->getFee();
    }

    Bill *bill = findBillByAppointmentId(appointmentId);
    if (bill != 0)
    {
        bill->setStatus("cancelled");
    }

    fileHandler.saveAppointments(appointmentsFile, appointments);
    fileHandler.saveBills(billsFile, bills);
    fileHandler.savePatients(patientsFile, patients);

    std::snprintf(message, messageSize, "Appointment cancelled. PKR %.2f refunded to your balance.", doctor != 0 ? doctor->getFee() : 0.0f);
    return true;
}

void HospitalSystem::viewMyAppointments(char *buffer, int bufferSize) const
{
    TextUtil::clear(buffer);
    if (currentPatient == 0)
    {
        TextUtil::copy(buffer, "Patient is not logged in.", bufferSize);
        return;
    }

    Appointment *temp = new Appointment[appointments.size()];
    int count = 0;
    int index = 0;
    const Appointment *list = appointments.getAll();
    while (index < appointments.size())
    {
        if (list[index].getPatientId() == currentPatient->getId())
        {
            temp[count] = list[index];
            count++;
        }
        index++;
    }

    if (count == 0)
    {
        delete[] temp;
        TextUtil::copy(buffer, "No appointments found.", bufferSize);
        return;
    }

    sortAppointmentsByDate(true, temp, count);
    index = 0;
    while (index < count)
    {
        const Doctor *doctor = findDoctorById(temp[index].getDoctorId());
        char line[350];
        std::snprintf(line, 350, "ID: %d | Doctor: %s | Specialization: %s | Date: %s | Time Slot: %s | Status: %s",
                      temp[index].getId(),
                      doctor != 0 ? doctor->getName() : "Unknown",
                      doctor != 0 ? doctor->getSpecialization() : "Unknown",
                      temp[index].getDate(),
                      temp[index].getTimeSlot(),
                      temp[index].getStatus());
        TextUtil::appendLine(buffer, line, bufferSize);
        index++;
    }

    delete[] temp;
}

void HospitalSystem::viewMyMedicalRecords(char *buffer, int bufferSize) const
{
    TextUtil::clear(buffer);
    if (currentPatient == 0)
    {
        TextUtil::copy(buffer, "Patient is not logged in.", bufferSize);
        return;
    }

    Prescription *temp = new Prescription[prescriptions.size()];
    int count = 0;
    int index = 0;
    const Prescription *list = prescriptions.getAll();
    while (index < prescriptions.size())
    {
        if (list[index].getPatientId() == currentPatient->getId())
        {
            temp[count] = list[index];
            count++;
        }
        index++;
    }

    if (count == 0)
    {
        delete[] temp;
        TextUtil::copy(buffer, "No medical records found.", bufferSize);
        return;
    }

    sortPrescriptionsByDate(temp, count, false);
    index = 0;
    while (index < count)
    {
        const Doctor *doctor = findDoctorById(temp[index].getDoctorId());
        char line[1000];
        std::snprintf(line, 1000, "Date: %s | Doctor: %s | Medicines: %s | Notes: %s",
                      temp[index].getDate(),
                      doctor != 0 ? doctor->getName() : "Unknown",
                      temp[index].getMedicines(),
                      temp[index].getNotes());
        TextUtil::appendLine(buffer, line, bufferSize);
        index++;
    }

    delete[] temp;
}

void HospitalSystem::viewMyBills(char *buffer, int bufferSize) const
{
    TextUtil::clear(buffer);
    if (currentPatient == 0)
    {
        TextUtil::copy(buffer, "Patient is not logged in.", bufferSize);
        return;
    }

    Bill *temp = new Bill[bills.size()];
    int count = 0;
    int index = 0;
    float outstanding = 0.0f;
    const Bill *list = bills.getAll();
    while (index < bills.size())
    {
        if (list[index].getPatientId() == currentPatient->getId())
        {
            temp[count] = list[index];
            count++;
            if (TextUtil::equals(list[index].getStatus(), "unpaid"))
            {
                outstanding = outstanding + list[index].getAmount();
            }
        }
        index++;
    }

    if (count == 0)
    {
        delete[] temp;
        TextUtil::copy(buffer, "No bills found.", bufferSize);
        return;
    }

    sortBillsByDate(temp, count, true);
    index = 0;
    while (index < count)
    {
        char line[250];
        std::snprintf(line, 250, "Bill ID: %d | Appointment ID: %d | Amount (PKR): %.2f | Status: %s | Date: %s",
                      temp[index].getId(),
                      temp[index].getAppointmentId(),
                      temp[index].getAmount(),
                      temp[index].getStatus(),
                      temp[index].getDate());
        TextUtil::appendLine(buffer, line, bufferSize);
        index++;
    }

    char footer[100];
    std::snprintf(footer, 100, "Total outstanding unpaid amount: PKR %.2f", outstanding);
    TextUtil::appendLine(buffer, footer, bufferSize);
    delete[] temp;
}

bool HospitalSystem::payBill(const char *billIdText, char *message, int messageSize)
{
    if (currentPatient == 0)
    {
        TextUtil::copy(message, "Patient is not logged in.", messageSize);
        return false;
    }

    int billId = TextUtil::toInt(billIdText);
    Bill *bill = findBillById(billId);
    if (bill == 0 || bill->getPatientId() != currentPatient->getId() || !TextUtil::equals(bill->getStatus(), "unpaid"))
    {
        TextUtil::copy(message, "Invalid bill ID.", messageSize);
        return false;
    }

    try
    {
        if (currentPatient->getBalance() < bill->getAmount())
        {
            throw InsufficientFundsException("Insufficient funds. Please top up your balance first.");
        }

        (*currentPatient) -= bill->getAmount();
        bill->setStatus("paid");
        fileHandler.saveBills(billsFile, bills);
        fileHandler.savePatients(patientsFile, patients);
        std::snprintf(message, messageSize, "Bill paid successfully. Remaining balance: PKR %.2f.", currentPatient->getBalance());
        return true;
    }
    catch (HospitalException &exception)
    {
        TextUtil::copy(message, exception.what(), messageSize);
        return false;
    }
}

bool HospitalSystem::topUpBalance(const char *amountText, char *message, int messageSize)
{
    if (currentPatient == 0)
    {
        TextUtil::copy(message, "Patient is not logged in.", messageSize);
        return false;
    }

    try
    {
        if (!validator.isPositiveFloat(amountText))
        {
            throw InvalidInputException("Enter a positive amount greater than 0.");
        }

        float amount = TextUtil::toFloat(amountText);
        (*currentPatient) += amount;
        fileHandler.savePatients(patientsFile, patients);
        std::snprintf(message, messageSize, "Balance updated. New balance: PKR %.2f.", currentPatient->getBalance());
        return true;
    }
    catch (HospitalException &exception)
    {
        TextUtil::copy(message, exception.what(), messageSize);
        return false;
    }
}

void HospitalSystem::viewTodayAppointments(char *buffer, int bufferSize) const
{
    TextUtil::clear(buffer);
    if (currentDoctor == 0)
    {
        TextUtil::copy(buffer, "Doctor is not logged in.", bufferSize);
        return;
    }

    char today[20];
    getTodayDate(today, 20);

    Appointment *temp = new Appointment[appointments.size()];
    int count = 0;
    int index = 0;
    const Appointment *list = appointments.getAll();
    while (index < appointments.size())
    {
        if (list[index].getDoctorId() == currentDoctor->getId() && TextUtil::equals(list[index].getDate(), today))
        {
            temp[count] = list[index];
            count++;
        }
        index++;
    }

    if (count == 0)
    {
        delete[] temp;
        TextUtil::copy(buffer, "No appointments scheduled for today.", bufferSize);
        return;
    }

    sortAppointmentsByTime(temp, count);
    index = 0;
    while (index < count)
    {
        const Patient *patient = findPatientById(temp[index].getPatientId());
        char line[250];
        std::snprintf(line, 250, "Appointment ID: %d | Patient Name: %s | Time Slot: %s | Status: %s",
                      temp[index].getId(),
                      patient != 0 ? patient->getName() : "Unknown",
                      temp[index].getTimeSlot(),
                      temp[index].getStatus());
        TextUtil::appendLine(buffer, line, bufferSize);
        index++;
    }

    delete[] temp;
}

bool HospitalSystem::markAppointmentComplete(const char *appointmentIdText, char *message, int messageSize)
{
    if (currentDoctor == 0)
    {
        TextUtil::copy(message, "Doctor is not logged in.", messageSize);
        return false;
    }

    char today[20];
    getTodayDate(today, 20);

    int appointmentId = TextUtil::toInt(appointmentIdText);
    Appointment *appointment = findAppointmentById(appointmentId);
    if (appointment == 0 ||
        appointment->getDoctorId() != currentDoctor->getId() ||
        !TextUtil::equals(appointment->getStatus(), "pending") ||
        !TextUtil::equals(appointment->getDate(), today))
    {
        TextUtil::copy(message, "Invalid appointment ID.", messageSize);
        return false;
    }

    appointment->setStatus("completed");
    fileHandler.saveAppointments(appointmentsFile, appointments);
    TextUtil::copy(message, "Appointment marked as completed.", messageSize);
    return true;
}

bool HospitalSystem::markAppointmentNoShow(const char *appointmentIdText, char *message, int messageSize)
{
    if (currentDoctor == 0)
    {
        TextUtil::copy(message, "Doctor is not logged in.", messageSize);
        return false;
    }

    char today[20];
    getTodayDate(today, 20);

    int appointmentId = TextUtil::toInt(appointmentIdText);
    Appointment *appointment = findAppointmentById(appointmentId);
    if (appointment == 0 ||
        appointment->getDoctorId() != currentDoctor->getId() ||
        !TextUtil::equals(appointment->getStatus(), "pending") ||
        !TextUtil::equals(appointment->getDate(), today))
    {
        TextUtil::copy(message, "Invalid appointment ID.", messageSize);
        return false;
    }

    appointment->setStatus("no-show");
    Bill *bill = findBillByAppointmentId(appointmentId);
    if (bill != 0)
    {
        bill->setStatus("cancelled");
    }

    fileHandler.saveAppointments(appointmentsFile, appointments);
    fileHandler.saveBills(billsFile, bills);
    TextUtil::copy(message, "Appointment marked as no-show.", messageSize);
    return true;
}

bool HospitalSystem::writePrescription(const char *appointmentIdText, const char *medicines, const char *notes, char *message, int messageSize)
{
    if (currentDoctor == 0)
    {
        TextUtil::copy(message, "Doctor is not logged in.", messageSize);
        return false;
    }

    int appointmentId = TextUtil::toInt(appointmentIdText);
    Appointment *appointment = findAppointmentById(appointmentId);
    if (appointment == 0 || appointment->getDoctorId() != currentDoctor->getId() || !TextUtil::equals(appointment->getStatus(), "completed"))
    {
        TextUtil::copy(message, "Invalid appointment ID.", messageSize);
        return false;
    }

    if (hasPrescriptionForAppointment(appointmentId))
    {
        TextUtil::copy(message, "Prescription already written for this appointment.", messageSize);
        return false;
    }

    int prescriptionId = fileHandler.getNextId(prescriptionsFile);
    Prescription prescription(prescriptionId,
                              appointmentId,
                              appointment->getPatientId(),
                              currentDoctor->getId(),
                              appointment->getDate(),
                              medicines,
                              notes);
    prescriptions.add(prescription);
    fileHandler.appendPrescription(prescriptionsFile, prescription);
    TextUtil::copy(message, "Prescription saved.", messageSize);
    return true;
}

bool HospitalSystem::viewPatientMedicalHistory(const char *patientIdText, char *buffer, int bufferSize) const
{
    TextUtil::clear(buffer);
    if (currentDoctor == 0)
    {
        TextUtil::copy(buffer, "Doctor is not logged in.", bufferSize);
        return false;
    }

    int patientId = TextUtil::toInt(patientIdText);
    const Patient *patient = findPatientById(patientId);
    if (patient == 0)
    {
        TextUtil::copy(buffer, "Access denied. You can only view records of your own patients.", bufferSize);
        return false;
    }

    bool hasCompletedAppointment = false;
    int index = 0;
    const Appointment *appointmentList = appointments.getAll();
    while (index < appointments.size())
    {
        if (appointmentList[index].getPatientId() == patientId &&
            appointmentList[index].getDoctorId() == currentDoctor->getId() &&
            TextUtil::equals(appointmentList[index].getStatus(), "completed"))
        {
            hasCompletedAppointment = true;
            break;
        }
        index++;
    }

    if (!hasCompletedAppointment)
    {
        TextUtil::copy(buffer, "Access denied. You can only view records of your own patients.", bufferSize);
        return false;
    }

    Prescription *temp = new Prescription[prescriptions.size()];
    int count = 0;
    index = 0;
    const Prescription *list = prescriptions.getAll();
    while (index < prescriptions.size())
    {
        if (list[index].getPatientId() == patientId && list[index].getDoctorId() == currentDoctor->getId())
        {
            temp[count] = list[index];
            count++;
        }
        index++;
    }

    if (count == 0)
    {
        delete[] temp;
        TextUtil::copy(buffer, "No medical records found.", bufferSize);
        return true;
    }

    sortPrescriptionsByDate(temp, count, false);
    index = 0;
    while (index < count)
    {
        char line[1000];
        std::snprintf(line, 1000, "Date: %s | Medicines: %s | Notes: %s",
                      temp[index].getDate(),
                      temp[index].getMedicines(),
                      temp[index].getNotes());
        TextUtil::appendLine(buffer, line, bufferSize);
        index++;
    }

    delete[] temp;
    return true;
}

bool HospitalSystem::addDoctor(const char *name, const char *specialization, const char *contact, const char *password, const char *feeText, char *message, int messageSize)
{
    if (currentAdmin == 0)
    {
        TextUtil::copy(message, "Admin is not logged in.", messageSize);
        return false;
    }

    if (TextUtil::length(name) == 0 || TextUtil::length(name) > 50 ||
        TextUtil::length(specialization) == 0 || TextUtil::length(specialization) > 50 ||
        !validator.isValidContact(contact) ||
        !validator.isValidPassword(password) ||
        !validator.isPositiveFloat(feeText))
    {
        TextUtil::copy(message, "Invalid doctor data. Check contact, password and fee requirements.", messageSize);
        return false;
    }

    int doctorId = fileHandler.getNextId(doctorsFile);
    Doctor doctor(doctorId, name, specialization, contact, password, TextUtil::toFloat(feeText));
    doctors.add(doctor);
    fileHandler.saveDoctors(doctorsFile, doctors);
    std::snprintf(message, messageSize, "Doctor added successfully. ID: %d.", doctorId);
    return true;
}

bool HospitalSystem::removeDoctor(const char *doctorIdText, char *message, int messageSize)
{
    if (currentAdmin == 0)
    {
        TextUtil::copy(message, "Admin is not logged in.", messageSize);
        return false;
    }

    int doctorId = TextUtil::toInt(doctorIdText);
    Doctor *doctor = findDoctorById(doctorId);
    if (doctor == 0)
    {
        TextUtil::copy(message, "Doctor not found.", messageSize);
        return false;
    }

    int index = 0;
    const Appointment *list = appointments.getAll();
    while (index < appointments.size())
    {
        if (list[index].getDoctorId() == doctorId && TextUtil::equals(list[index].getStatus(), "pending"))
        {
            TextUtil::copy(message, "Cannot remove doctor with pending appointments. Cancel or reassign them first.", messageSize);
            return false;
        }
        index++;
    }

    doctors.removeById(doctorId);
    fileHandler.saveDoctors(doctorsFile, doctors);
    TextUtil::copy(message, "Doctor removed.", messageSize);
    return true;
}

void HospitalSystem::viewAllPatients(char *buffer, int bufferSize) const
{
    TextUtil::clear(buffer);
    if (patients.size() == 0)
    {
        TextUtil::copy(buffer, "No patients found.", bufferSize);
        return;
    }

    int index = 0;
    const Patient *list = patients.getAll();
    while (index < patients.size())
    {
        int unpaidCount = 0;
        int billIndex = 0;
        const Bill *billList = bills.getAll();
        while (billIndex < bills.size())
        {
            if (billList[billIndex].getPatientId() == list[index].getId() && TextUtil::equals(billList[billIndex].getStatus(), "unpaid"))
            {
                unpaidCount++;
            }
            billIndex++;
        }

        char line[350];
        std::snprintf(line, 350, "ID: %d | Name: %s | Age: %d | Gender: %s | Contact: %s | Balance: %.2f | Unpaid Bills: %d",
                      list[index].getId(),
                      list[index].getName(),
                      list[index].getAge(),
                      list[index].getGender(),
                      list[index].getContact(),
                      list[index].getBalance(),
                      unpaidCount);
        TextUtil::appendLine(buffer, line, bufferSize);
        index++;
    }
}

void HospitalSystem::viewAllDoctors(char *buffer, int bufferSize) const
{
    TextUtil::clear(buffer);
    if (doctors.size() == 0)
    {
        TextUtil::copy(buffer, "No doctors found.", bufferSize);
        return;
    }

    int index = 0;
    const Doctor *list = doctors.getAll();
    while (index < doctors.size())
    {
        char line[280];
        std::snprintf(line, 280, "ID: %d | Name: %s | Specialization: %s | Contact: %s | Fee: %.2f",
                      list[index].getId(),
                      list[index].getName(),
                      list[index].getSpecialization(),
                      list[index].getContact(),
                      list[index].getFee());
        TextUtil::appendLine(buffer, line, bufferSize);
        index++;
    }
}

void HospitalSystem::viewAllAppointments(char *buffer, int bufferSize) const
{
    TextUtil::clear(buffer);
    if (appointments.size() == 0)
    {
        TextUtil::copy(buffer, "No appointments found.", bufferSize);
        return;
    }

    Appointment *temp = new Appointment[appointments.size()];
    int index = 0;
    const Appointment *list = appointments.getAll();
    while (index < appointments.size())
    {
        temp[index] = list[index];
        index++;
    }

    sortAppointmentsByDate(false, temp, appointments.size());
    index = 0;
    while (index < appointments.size())
    {
        const Patient *patient = findPatientById(temp[index].getPatientId());
        const Doctor *doctor = findDoctorById(temp[index].getDoctorId());
        char line[400];
        std::snprintf(line, 400, "ID: %d | Patient: %s | Doctor: %s | Date: %s | Time Slot: %s | Status: %s",
                      temp[index].getId(),
                      patient != 0 ? patient->getName() : "Unknown",
                      doctor != 0 ? doctor->getName() : "Unknown",
                      temp[index].getDate(),
                      temp[index].getTimeSlot(),
                      temp[index].getStatus());
        TextUtil::appendLine(buffer, line, bufferSize);
        index++;
    }

    delete[] temp;
}

void HospitalSystem::viewUnpaidBills(char *buffer, int bufferSize) const
{
    TextUtil::clear(buffer);

    char today[20];
    getTodayDate(today, 20);

    bool found = false;
    int index = 0;
    const Bill *list = bills.getAll();
    while (index < bills.size())
    {
        if (TextUtil::equals(list[index].getStatus(), "unpaid"))
        {
            const Patient *patient = findPatientById(list[index].getPatientId());
            char overduePart[30];
            TextUtil::copy(overduePart, "", 30);
            if (TextUtil::daysDifference(list[index].getDate(), today) > 7)
            {
                TextUtil::copy(overduePart, " [OVERDUE]", 30);
            }

            char line[350];
            std::snprintf(line, 350, "Bill ID: %d | Patient: %s | Amount (PKR): %.2f | Date: %s%s",
                          list[index].getId(),
                          patient != 0 ? patient->getName() : "Unknown",
                          list[index].getAmount(),
                          list[index].getDate(),
                          overduePart);
            TextUtil::appendLine(buffer, line, bufferSize);
            found = true;
        }
        index++;
    }

    if (!found)
    {
        TextUtil::copy(buffer, "No unpaid bills found.", bufferSize);
    }
}

bool HospitalSystem::dischargePatient(const char *patientIdText, char *message, int messageSize)
{
    if (currentAdmin == 0)
    {
        TextUtil::copy(message, "Admin is not logged in.", messageSize);
        return false;
    }

    int patientId = TextUtil::toInt(patientIdText);
    Patient *patient = findPatientById(patientId);
    if (patient == 0)
    {
        TextUtil::copy(message, "Patient not found.", messageSize);
        return false;
    }

    int index = 0;
    const Bill *billList = bills.getAll();
    while (index < bills.size())
    {
        if (billList[index].getPatientId() == patientId && TextUtil::equals(billList[index].getStatus(), "unpaid"))
        {
            TextUtil::copy(message, "Cannot discharge patient with unpaid bills.", messageSize);
            return false;
        }
        index++;
    }

    index = 0;
    const Appointment *appointmentList = appointments.getAll();
    while (index < appointments.size())
    {
        if (appointmentList[index].getPatientId() == patientId && TextUtil::equals(appointmentList[index].getStatus(), "pending"))
        {
            TextUtil::copy(message, "Cannot discharge patient with pending appointments.", messageSize);
            return false;
        }
        index++;
    }

    char archiveLine[1200];
    std::snprintf(archiveLine, 1200, "%d,%s,%d,%s,%s,%s,%.2f", patient->getId(), patient->getName(), patient->getAge(), patient->getGender(), patient->getContact(), patient->getPassword(), patient->getBalance());
    fileHandler.appendArchiveLine(dischargedFile, archiveLine);

    index = 0;
    while (index < appointments.size())
    {
        if (appointments.getAll()[index].getPatientId() == patientId)
        {
            std::snprintf(archiveLine, 1200, "%d,%d,%d,%s,%s,%s",
                          appointments.getAll()[index].getId(),
                          appointments.getAll()[index].getPatientId(),
                          appointments.getAll()[index].getDoctorId(),
                          appointments.getAll()[index].getDate(),
                          appointments.getAll()[index].getTimeSlot(),
                          appointments.getAll()[index].getStatus());
            fileHandler.appendArchiveLine(dischargedFile, archiveLine);
        }
        index++;
    }

    index = 0;
    while (index < prescriptions.size())
    {
        if (prescriptions.getAll()[index].getPatientId() == patientId)
        {
            std::snprintf(archiveLine, 1200, "%d,%d,%d,%d,%s,%s,%s",
                          prescriptions.getAll()[index].getId(),
                          prescriptions.getAll()[index].getAppointmentId(),
                          prescriptions.getAll()[index].getPatientId(),
                          prescriptions.getAll()[index].getDoctorId(),
                          prescriptions.getAll()[index].getDate(),
                          prescriptions.getAll()[index].getMedicines(),
                          prescriptions.getAll()[index].getNotes());
            fileHandler.appendArchiveLine(dischargedFile, archiveLine);
        }
        index++;
    }

    index = 0;
    while (index < bills.size())
    {
        if (bills.getAll()[index].getPatientId() == patientId)
        {
            std::snprintf(archiveLine, 1200, "%d,%d,%d,%.2f,%s,%s",
                          bills.getAll()[index].getId(),
                          bills.getAll()[index].getPatientId(),
                          bills.getAll()[index].getAppointmentId(),
                          bills.getAll()[index].getAmount(),
                          bills.getAll()[index].getStatus(),
                          bills.getAll()[index].getDate());
            fileHandler.appendArchiveLine(dischargedFile, archiveLine);
        }
        index++;
    }

    patients.removeById(patientId);

    index = 0;
    while (index < appointments.size())
    {
        if (appointments.getAll()[index].getPatientId() == patientId)
        {
            appointments.removeById(appointments.getAll()[index].getId());
        }
        else
        {
            index++;
        }
    }

    index = 0;
    while (index < prescriptions.size())
    {
        if (prescriptions.getAll()[index].getPatientId() == patientId)
        {
            prescriptions.removeById(prescriptions.getAll()[index].getId());
        }
        else
        {
            index++;
        }
    }

    index = 0;
    while (index < bills.size())
    {
        if (bills.getAll()[index].getPatientId() == patientId)
        {
            bills.removeById(bills.getAll()[index].getId());
        }
        else
        {
            index++;
        }
    }

    fileHandler.savePatients(patientsFile, patients);
    fileHandler.saveAppointments(appointmentsFile, appointments);
    fileHandler.savePrescriptions(prescriptionsFile, prescriptions);
    fileHandler.saveBills(billsFile, bills);
    TextUtil::copy(message, "Patient discharged and archived successfully.", messageSize);
    return true;
}

void HospitalSystem::viewSecurityLog(char *buffer, int bufferSize) const
{
    try
    {
        fileHandler.readFileText(securityLogFile, buffer, bufferSize);
        if (TextUtil::length(buffer) == 0 || TextUtil::equals(buffer, "timestamp,role,entered_id,result\n"))
        {
            TextUtil::copy(buffer, "No security events logged.", bufferSize);
        }
    }
    catch (HospitalException &exception)
    {
        TextUtil::copy(buffer, exception.what(), bufferSize);
    }
}

void HospitalSystem::generateDailyReport(char *buffer, int bufferSize) const
{
    TextUtil::clear(buffer);
    char today[20];
    getTodayDate(today, 20);

    int total = 0;
    int pending = 0;
    int completed = 0;
    int noShow = 0;
    int cancelled = 0;
    float revenue = 0.0f;

    int index = 0;
    const Appointment *appointmentList = appointments.getAll();
    while (index < appointments.size())
    {
        if (TextUtil::equals(appointmentList[index].getDate(), today))
        {
            total++;
            if (TextUtil::equals(appointmentList[index].getStatus(), "pending"))
            {
                pending++;
            }
            else if (TextUtil::equals(appointmentList[index].getStatus(), "completed"))
            {
                completed++;
            }
            else if (TextUtil::equals(appointmentList[index].getStatus(), "no-show"))
            {
                noShow++;
            }
            else if (TextUtil::equals(appointmentList[index].getStatus(), "cancelled"))
            {
                cancelled++;
            }
        }
        index++;
    }

    index = 0;
    const Bill *billList = bills.getAll();
    while (index < bills.size())
    {
        if (TextUtil::equals(billList[index].getStatus(), "paid") && TextUtil::equals(billList[index].getDate(), today))
        {
            revenue = revenue + billList[index].getAmount();
        }
        index++;
    }

    char line[300];
    std::snprintf(line, 300, "Total appointments today: %d (Pending: %d Completed: %d No-show: %d Cancelled: %d)", total, pending, completed, noShow, cancelled);
    TextUtil::appendLine(buffer, line, bufferSize);
    std::snprintf(line, 300, "Revenue collected today (paid bills): PKR %.2f", revenue);
    TextUtil::appendLine(buffer, line, bufferSize);

    TextUtil::appendLine(buffer, "Patients with outstanding unpaid bills:", bufferSize);
    bool foundOutstanding = false;
    index = 0;
    const Patient *patientList = patients.getAll();
    while (index < patients.size())
    {
        float totalOwed = 0.0f;
        int billIndex = 0;
        while (billIndex < bills.size())
        {
            if (billList[billIndex].getPatientId() == patientList[index].getId() && TextUtil::equals(billList[billIndex].getStatus(), "unpaid"))
            {
                totalOwed = totalOwed + billList[billIndex].getAmount();
            }
            billIndex++;
        }
        if (totalOwed > 0.0f)
        {
            std::snprintf(line, 300, "%s | Total Owed: PKR %.2f", patientList[index].getName(), totalOwed);
            TextUtil::appendLine(buffer, line, bufferSize);
            foundOutstanding = true;
        }
        index++;
    }
    if (!foundOutstanding)
    {
        TextUtil::appendLine(buffer, "None", bufferSize);
    }

    TextUtil::appendLine(buffer, "Doctor-wise summary for today:", bufferSize);
    int doctorIndex = 0;
    const Doctor *doctorList = doctors.getAll();
    while (doctorIndex < doctors.size())
    {
        int doctorCompleted = 0;
        int doctorPending = 0;
        int doctorNoShow = 0;
        index = 0;
        while (index < appointments.size())
        {
            if (appointmentList[index].getDoctorId() == doctorList[doctorIndex].getId() && TextUtil::equals(appointmentList[index].getDate(), today))
            {
                if (TextUtil::equals(appointmentList[index].getStatus(), "completed"))
                {
                    doctorCompleted++;
                }
                else if (TextUtil::equals(appointmentList[index].getStatus(), "pending"))
                {
                    doctorPending++;
                }
                else if (TextUtil::equals(appointmentList[index].getStatus(), "no-show"))
                {
                    doctorNoShow++;
                }
            }
            index++;
        }

        std::snprintf(line, 300, "%s | Completed: %d | Pending: %d | No-show: %d",
                      doctorList[doctorIndex].getName(),
                      doctorCompleted,
                      doctorPending,
                      doctorNoShow);
        TextUtil::appendLine(buffer, line, bufferSize);
        doctorIndex++;
    }
}
