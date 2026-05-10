#include "../include/Gui.h"
#include "../include/TextUtil.h"

#include <cstdio>

namespace
{
    const int ACTION_PATIENT_BOOK = 101;
    const int ACTION_PATIENT_CANCEL = 102;
    const int ACTION_PATIENT_VIEW_APPOINTMENTS = 103;
    const int ACTION_PATIENT_VIEW_RECORDS = 104;
    const int ACTION_PATIENT_VIEW_BILLS = 105;
    const int ACTION_PATIENT_PAY_BILL = 106;
    const int ACTION_PATIENT_TOP_UP = 107;
    const int ACTION_PATIENT_LOGOUT = 108;

    const int ACTION_DOCTOR_VIEW_TODAY = 201;
    const int ACTION_DOCTOR_MARK_COMPLETE = 202;
    const int ACTION_DOCTOR_MARK_NO_SHOW = 203;
    const int ACTION_DOCTOR_WRITE_PRESCRIPTION = 204;
    const int ACTION_DOCTOR_VIEW_HISTORY = 205;
    const int ACTION_DOCTOR_LOGOUT = 206;

    const int ACTION_ADMIN_ADD_DOCTOR = 301;
    const int ACTION_ADMIN_REMOVE_DOCTOR = 302;
    const int ACTION_ADMIN_VIEW_PATIENTS = 303;
    const int ACTION_ADMIN_VIEW_DOCTORS = 304;
    const int ACTION_ADMIN_VIEW_APPOINTMENTS = 305;
    const int ACTION_ADMIN_VIEW_UNPAID_BILLS = 306;
    const int ACTION_ADMIN_DISCHARGE_PATIENT = 307;
    const int ACTION_ADMIN_VIEW_SECURITY_LOG = 308;
    const int ACTION_ADMIN_DAILY_REPORT = 309;
    const int ACTION_ADMIN_LOGOUT = 310;
}

Gui::Gui()
{
    system = 0;
    loginRole = 1;
    TextUtil::copy(loginId, "", 30);
    TextUtil::copy(loginPassword, "", 50);
    loginActiveField = 0;
    currentAction = 0;
    formActiveField = -1;
    fieldCount = 0;
    menuButtonCount = 0;
    TextUtil::copy(infoText, "", 20000);
    invalidDateAttempts = 0;
    invalidTopUpAttempts = 0;
}

bool Gui::loadFont()
{
    if (font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        return true;
    }

    if (font.loadFromFile("C:/Windows/Fonts/segoeui.ttf"))
    {
        return true;
    }

    return false;
}

bool Gui::initialize(HospitalSystem *hospitalSystem)
{
    system = hospitalSystem;
    window.create(sf::VideoMode(1320, 820), "MediCore Hospital Management System");
    window.setFramerateLimit(60);
    uiView = sf::View(sf::FloatRect(0.0f, 0.0f, 1320.0f, 820.0f));
    updateView(1320, 820);
    TextUtil::copy(infoText, "Choose a role, enter ID and password, then click Login.", 20000);
    return loadFont();
}

void Gui::run()
{
    while (window.isOpen())
    {
        processEvents();
        render();
    }
}

void Gui::configureMenuButtons()
{
    menuButtonCount = 0;
    int role = system->getCurrentRole();

    if (role == 1)
    {
        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 180.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_PATIENT_BOOK;
        TextUtil::copy(menuButtons[menuButtonCount].label, "Book Appointment", 60);
        menuButtonCount++;

        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 232.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_PATIENT_CANCEL;
        TextUtil::copy(menuButtons[menuButtonCount].label, "Cancel Appointment", 60);
        menuButtonCount++;

        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 284.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_PATIENT_VIEW_APPOINTMENTS;
        TextUtil::copy(menuButtons[menuButtonCount].label, "View My Appointments", 60);
        menuButtonCount++;

        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 336.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_PATIENT_VIEW_RECORDS;
        TextUtil::copy(menuButtons[menuButtonCount].label, "View Medical Records", 60);
        menuButtonCount++;

        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 388.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_PATIENT_VIEW_BILLS;
        TextUtil::copy(menuButtons[menuButtonCount].label, "View My Bills", 60);
        menuButtonCount++;

        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 440.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_PATIENT_PAY_BILL;
        TextUtil::copy(menuButtons[menuButtonCount].label, "Pay Bill", 60);
        menuButtonCount++;

        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 492.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_PATIENT_TOP_UP;
        TextUtil::copy(menuButtons[menuButtonCount].label, "Top Up Balance", 60);
        menuButtonCount++;

        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 544.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_PATIENT_LOGOUT;
        TextUtil::copy(menuButtons[menuButtonCount].label, "Logout", 60);
        menuButtonCount++;
    }
    else if (role == 2)
    {
        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 180.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_DOCTOR_VIEW_TODAY;
        TextUtil::copy(menuButtons[menuButtonCount].label, "View Today's Appointments", 60);
        menuButtonCount++;

        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 232.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_DOCTOR_MARK_COMPLETE;
        TextUtil::copy(menuButtons[menuButtonCount].label, "Mark Complete", 60);
        menuButtonCount++;

        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 284.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_DOCTOR_MARK_NO_SHOW;
        TextUtil::copy(menuButtons[menuButtonCount].label, "Mark No-Show", 60);
        menuButtonCount++;

        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 336.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_DOCTOR_WRITE_PRESCRIPTION;
        TextUtil::copy(menuButtons[menuButtonCount].label, "Write Prescription", 60);
        menuButtonCount++;

        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 388.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_DOCTOR_VIEW_HISTORY;
        TextUtil::copy(menuButtons[menuButtonCount].label, "View Patient History", 60);
        menuButtonCount++;

        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 440.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_DOCTOR_LOGOUT;
        TextUtil::copy(menuButtons[menuButtonCount].label, "Logout", 60);
        menuButtonCount++;
    }
    else if (role == 3)
    {
        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 180.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_ADMIN_ADD_DOCTOR;
        TextUtil::copy(menuButtons[menuButtonCount].label, "Add Doctor", 60);
        menuButtonCount++;

        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 232.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_ADMIN_REMOVE_DOCTOR;
        TextUtil::copy(menuButtons[menuButtonCount].label, "Remove Doctor", 60);
        menuButtonCount++;

        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 284.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_ADMIN_VIEW_PATIENTS;
        TextUtil::copy(menuButtons[menuButtonCount].label, "View All Patients", 60);
        menuButtonCount++;

        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 336.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_ADMIN_VIEW_DOCTORS;
        TextUtil::copy(menuButtons[menuButtonCount].label, "View All Doctors", 60);
        menuButtonCount++;

        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 388.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_ADMIN_VIEW_APPOINTMENTS;
        TextUtil::copy(menuButtons[menuButtonCount].label, "View Appointments", 60);
        menuButtonCount++;

        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 440.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_ADMIN_VIEW_UNPAID_BILLS;
        TextUtil::copy(menuButtons[menuButtonCount].label, "View Unpaid Bills", 60);
        menuButtonCount++;

        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 492.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_ADMIN_DISCHARGE_PATIENT;
        TextUtil::copy(menuButtons[menuButtonCount].label, "Discharge Patient", 60);
        menuButtonCount++;

        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 544.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_ADMIN_VIEW_SECURITY_LOG;
        TextUtil::copy(menuButtons[menuButtonCount].label, "View Security Log", 60);
        menuButtonCount++;

        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 596.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_ADMIN_DAILY_REPORT;
        TextUtil::copy(menuButtons[menuButtonCount].label, "Daily Report", 60);
        menuButtonCount++;

        menuButtons[menuButtonCount].area = sf::FloatRect(25.0f, 648.0f, 250.0f, 44.0f);
        menuButtons[menuButtonCount].actionId = ACTION_ADMIN_LOGOUT;
        TextUtil::copy(menuButtons[menuButtonCount].label, "Logout", 60);
        menuButtonCount++;
    }
}

void Gui::clearForm()
{
    fieldCount = 0;
    formActiveField = -1;
    int index = 0;
    while (index < 5)
    {
        TextUtil::copy(fields[index].label, "", 40);
        TextUtil::copy(fields[index].value, "", 520);
        fields[index].maxLength = 0;
        index++;
    }
}

void Gui::prepareAction(int actionId)
{
    currentAction = actionId;
    invalidDateAttempts = 0;
    invalidTopUpAttempts = 0;
    clearForm();

    if (actionId == ACTION_PATIENT_VIEW_APPOINTMENTS)
    {
        system->viewMyAppointments(infoText, 20000);
    }
    else if (actionId == ACTION_PATIENT_VIEW_RECORDS)
    {
        system->viewMyMedicalRecords(infoText, 20000);
    }
    else if (actionId == ACTION_PATIENT_VIEW_BILLS)
    {
        system->viewMyBills(infoText, 20000);
    }
    else if (actionId == ACTION_DOCTOR_VIEW_TODAY)
    {
        system->viewTodayAppointments(infoText, 20000);
    }
    else if (actionId == ACTION_ADMIN_VIEW_PATIENTS)
    {
        system->viewAllPatients(infoText, 20000);
    }
    else if (actionId == ACTION_ADMIN_VIEW_DOCTORS)
    {
        system->viewAllDoctors(infoText, 20000);
    }
    else if (actionId == ACTION_ADMIN_VIEW_APPOINTMENTS)
    {
        system->viewAllAppointments(infoText, 20000);
    }
    else if (actionId == ACTION_ADMIN_VIEW_UNPAID_BILLS)
    {
        system->viewUnpaidBills(infoText, 20000);
    }
    else if (actionId == ACTION_ADMIN_VIEW_SECURITY_LOG)
    {
        system->viewSecurityLog(infoText, 20000);
    }
    else if (actionId == ACTION_ADMIN_DAILY_REPORT)
    {
        system->generateDailyReport(infoText, 20000);
    }
    else if (actionId == ACTION_PATIENT_BOOK)
    {
        fieldCount = 4;
        TextUtil::copy(fields[0].label, "Specialization", 40);
        fields[0].maxLength = 50;
        TextUtil::copy(fields[1].label, "Doctor ID", 40);
        fields[1].maxLength = 10;
        TextUtil::copy(fields[2].label, "Date DD-MM-YYYY", 40);
        fields[2].maxLength = 10;
        TextUtil::copy(fields[3].label, "Time Slot", 40);
        fields[3].maxLength = 5;
        TextUtil::copy(infoText, "Enter specialization to search. Matching doctors and available slots will appear here.", 20000);
    }
    else if (actionId == ACTION_PATIENT_CANCEL)
    {
        fieldCount = 1;
        TextUtil::copy(fields[0].label, "Appointment ID", 40);
        fields[0].maxLength = 10;
        system->viewPendingAppointmentsForCurrentPatient(infoText, 20000);
    }
    else if (actionId == ACTION_PATIENT_PAY_BILL)
    {
        fieldCount = 1;
        TextUtil::copy(fields[0].label, "Bill ID", 40);
        fields[0].maxLength = 10;
        system->viewUnpaidBillsForCurrentPatient(infoText, 20000);
    }
    else if (actionId == ACTION_PATIENT_TOP_UP)
    {
        fieldCount = 1;
        TextUtil::copy(fields[0].label, "Amount", 40);
        fields[0].maxLength = 15;
        TextUtil::copy(infoText, "Enter amount to add in PKR.", 20000);
    }
    else if (actionId == ACTION_DOCTOR_MARK_COMPLETE || actionId == ACTION_DOCTOR_MARK_NO_SHOW)
    {
        fieldCount = 1;
        TextUtil::copy(fields[0].label, "Appointment ID", 40);
        fields[0].maxLength = 10;
        system->viewTodayPendingAppointmentsForDoctor(infoText, 20000);
    }
    else if (actionId == ACTION_DOCTOR_WRITE_PRESCRIPTION)
    {
        fieldCount = 3;
        TextUtil::copy(fields[0].label, "Appointment ID", 40);
        fields[0].maxLength = 10;
        TextUtil::copy(fields[1].label, "Medicines", 40);
        fields[1].maxLength = 499;
        TextUtil::copy(fields[2].label, "Notes", 40);
        fields[2].maxLength = 299;
        TextUtil::copy(infoText, "Enter medicines like: Paracetamol 500mg;Amoxicillin 250mg", 20000);
    }
    else if (actionId == ACTION_DOCTOR_VIEW_HISTORY)
    {
        fieldCount = 1;
        TextUtil::copy(fields[0].label, "Patient ID", 40);
        fields[0].maxLength = 10;
        TextUtil::copy(infoText, "Enter a patient ID to view medical history.", 20000);
    }
    else if (actionId == ACTION_ADMIN_ADD_DOCTOR)
    {
        fieldCount = 5;
        TextUtil::copy(fields[0].label, "Name", 40);
        fields[0].maxLength = 50;
        TextUtil::copy(fields[1].label, "Specialization", 40);
        fields[1].maxLength = 50;
        TextUtil::copy(fields[2].label, "Contact", 40);
        fields[2].maxLength = 11;
        TextUtil::copy(fields[3].label, "Password", 40);
        fields[3].maxLength = 30;
        TextUtil::copy(fields[4].label, "Fee", 40);
        fields[4].maxLength = 15;
        TextUtil::copy(infoText, "Fill all doctor fields exactly as required by the assignment.", 20000);
    }
    else if (actionId == ACTION_ADMIN_REMOVE_DOCTOR)
    {
        fieldCount = 1;
        TextUtil::copy(fields[0].label, "Doctor ID", 40);
        fields[0].maxLength = 10;
        system->viewAllDoctors(infoText, 20000);
    }
    else if (actionId == ACTION_ADMIN_DISCHARGE_PATIENT)
    {
        fieldCount = 1;
        TextUtil::copy(fields[0].label, "Patient ID", 40);
        fields[0].maxLength = 10;
        TextUtil::copy(infoText, "Enter a patient ID to discharge and archive.", 20000);
    }

    if (fieldCount > 0)
    {
        formActiveField = 0;
    }
}

void Gui::refreshActionPreview()
{
    if (currentAction == ACTION_PATIENT_BOOK)
    {
        char doctorsText[10000];
        char slotsText[4000];
        system->listDoctorsBySpecialization(fields[0].value, doctorsText, 10000);
        if (TextUtil::length(fields[1].value) > 0 && TextUtil::length(fields[2].value) > 0)
        {
            system->listAvailableSlots(TextUtil::toInt(fields[1].value), fields[2].value, slotsText, 4000);
            std::snprintf(infoText, 20000, "%s\n\n%s", doctorsText, slotsText);
        }
        else
        {
            TextUtil::copy(infoText, doctorsText, 20000);
        }
    }
    else if (currentAction == ACTION_PATIENT_CANCEL)
    {
        system->viewPendingAppointmentsForCurrentPatient(infoText, 20000);
    }
    else if (currentAction == ACTION_PATIENT_PAY_BILL)
    {
        system->viewUnpaidBillsForCurrentPatient(infoText, 20000);
    }
    else if (currentAction == ACTION_DOCTOR_MARK_COMPLETE || currentAction == ACTION_DOCTOR_MARK_NO_SHOW)
    {
        system->viewTodayPendingAppointmentsForDoctor(infoText, 20000);
    }
    else if (currentAction == ACTION_ADMIN_REMOVE_DOCTOR)
    {
        system->viewAllDoctors(infoText, 20000);
    }
}

void Gui::submitCurrentAction()
{
    char message[20000];
    message[0] = '\0';
    bool success = false;

    if (currentAction == ACTION_PATIENT_BOOK)
    {
        success = system->bookAppointment(fields[0].value, fields[1].value, fields[2].value, fields[3].value, message, 20000);
        if (!success && TextUtil::equals(message, "Invalid date. Use format DD-MM-YYYY."))
        {
            invalidDateAttempts++;
            if (invalidDateAttempts >= 3)
            {
                TextUtil::append(message, "\nReturning to menu after 3 failed attempts.", 20000);
                currentAction = 0;
                clearForm();
            }
        }
        else if (success)
        {
            invalidDateAttempts = 0;
        }
    }
    else if (currentAction == ACTION_PATIENT_CANCEL)
    {
        success = system->cancelAppointment(fields[0].value, message, 20000);
    }
    else if (currentAction == ACTION_PATIENT_PAY_BILL)
    {
        success = system->payBill(fields[0].value, message, 20000);
    }
    else if (currentAction == ACTION_PATIENT_TOP_UP)
    {
        success = system->topUpBalance(fields[0].value, message, 20000);
        if (!success && TextUtil::equals(message, "Enter a positive amount greater than 0."))
        {
            invalidTopUpAttempts++;
            if (invalidTopUpAttempts >= 3)
            {
                TextUtil::append(message, "\nReturning to menu after 3 failed attempts.", 20000);
                currentAction = 0;
                clearForm();
            }
        }
        else if (success)
        {
            invalidTopUpAttempts = 0;
        }
    }
    else if (currentAction == ACTION_DOCTOR_MARK_COMPLETE)
    {
        success = system->markAppointmentComplete(fields[0].value, message, 20000);
    }
    else if (currentAction == ACTION_DOCTOR_MARK_NO_SHOW)
    {
        success = system->markAppointmentNoShow(fields[0].value, message, 20000);
    }
    else if (currentAction == ACTION_DOCTOR_WRITE_PRESCRIPTION)
    {
        success = system->writePrescription(fields[0].value, fields[1].value, fields[2].value, message, 20000);
    }
    else if (currentAction == ACTION_DOCTOR_VIEW_HISTORY)
    {
        success = system->viewPatientMedicalHistory(fields[0].value, message, 20000);
    }
    else if (currentAction == ACTION_ADMIN_ADD_DOCTOR)
    {
        success = system->addDoctor(fields[0].value, fields[1].value, fields[2].value, fields[3].value, fields[4].value, message, 20000);
    }
    else if (currentAction == ACTION_ADMIN_REMOVE_DOCTOR)
    {
        success = system->removeDoctor(fields[0].value, message, 20000);
    }
    else if (currentAction == ACTION_ADMIN_DISCHARGE_PATIENT)
    {
        success = system->dischargePatient(fields[0].value, message, 20000);
    }
    else if (currentAction == ACTION_PATIENT_LOGOUT || currentAction == ACTION_DOCTOR_LOGOUT || currentAction == ACTION_ADMIN_LOGOUT)
    {
        system->logout(message, 20000);
        TextUtil::copy(loginId, "", 30);
        TextUtil::copy(loginPassword, "", 50);
        loginActiveField = 0;
        currentAction = 0;
        clearForm();
    }

    TextUtil::copy(infoText, message, 20000);

    if (success && (currentAction == ACTION_DOCTOR_VIEW_HISTORY))
    {
        clearForm();
        fieldCount = 1;
        TextUtil::copy(fields[0].label, "Patient ID", 40);
        fields[0].maxLength = 10;
    }

}

void Gui::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
        else if (event.type == sf::Event::Resized)
        {
            updateView(event.size.width, event.size.height);
        }
        else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mapped = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y), uiView);
            handleMouseClick(mapped.x, mapped.y);
        }
        else if (event.type == sf::Event::TextEntered)
        {
            handleTextInput(event.text.unicode);
        }
        else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::BackSpace)
        {
            handleBackspace();
        }
    }
}

void Gui::updateView(unsigned int width, unsigned int height)
{
    if (width == 0 || height == 0)
    {
        return;
    }

    float windowRatio = static_cast<float>(width) / static_cast<float>(height);
    float targetRatio = 1320.0f / 820.0f;

    float viewportLeft = 0.0f;
    float viewportTop = 0.0f;
    float viewportWidth = 1.0f;
    float viewportHeight = 1.0f;

    if (windowRatio > targetRatio)
    {
        viewportWidth = targetRatio / windowRatio;
        viewportLeft = (1.0f - viewportWidth) / 2.0f;
    }
    else if (windowRatio < targetRatio)
    {
        viewportHeight = windowRatio / targetRatio;
        viewportTop = (1.0f - viewportHeight) / 2.0f;
    }

    uiView.setSize(1320.0f, 820.0f);
    uiView.setCenter(660.0f, 410.0f);
    uiView.setViewport(sf::FloatRect(viewportLeft, viewportTop, viewportWidth, viewportHeight));
    window.setView(uiView);
}

void Gui::handleMouseClick(float x, float y)
{
    if (system->getCurrentRole() == 0)
    {
        if (sf::FloatRect(180.0f, 170.0f, 180.0f, 44.0f).contains(x, y))
        {
            loginRole = 1;
        }
        else if (sf::FloatRect(380.0f, 170.0f, 180.0f, 44.0f).contains(x, y))
        {
            loginRole = 2;
        }
        else if (sf::FloatRect(580.0f, 170.0f, 180.0f, 44.0f).contains(x, y))
        {
            loginRole = 3;
        }
        else if (sf::FloatRect(780.0f, 170.0f, 180.0f, 44.0f).contains(x, y))
        {
            window.close();
        }
        else if (sf::FloatRect(180.0f, 280.0f, 360.0f, 50.0f).contains(x, y))
        {
            loginActiveField = 0;
        }
        else if (sf::FloatRect(180.0f, 370.0f, 360.0f, 50.0f).contains(x, y))
        {
            loginActiveField = 1;
        }
        else if (sf::FloatRect(180.0f, 460.0f, 180.0f, 50.0f).contains(x, y))
        {
            char message[20000];
            if (system->login(loginRole, loginId, loginPassword, message, 20000))
            {
                TextUtil::copy(infoText, "Login successful. Choose an action from the menu.", 20000);
                currentAction = 0;
                clearForm();
                configureMenuButtons();
            }
            else
            {
                TextUtil::copy(infoText, message, 20000);
            }
        }
        return;
    }

    int buttonIndex = 0;
    while (buttonIndex < menuButtonCount)
    {
        if (menuButtons[buttonIndex].area.contains(x, y))
        {
            if (menuButtons[buttonIndex].actionId == ACTION_PATIENT_LOGOUT ||
                menuButtons[buttonIndex].actionId == ACTION_DOCTOR_LOGOUT ||
                menuButtons[buttonIndex].actionId == ACTION_ADMIN_LOGOUT)
            {
                currentAction = menuButtons[buttonIndex].actionId;
                submitCurrentAction();
            }
            else
            {
                prepareAction(menuButtons[buttonIndex].actionId);
            }
            return;
        }
        buttonIndex++;
    }

    if (currentAction != 0)
    {
        int index = 0;
        while (index < fieldCount)
        {
            float top = 160.0f + static_cast<float>(index) * 78.0f;
            if (sf::FloatRect(340.0f, top + 28.0f, 420.0f, 44.0f).contains(x, y))
            {
                formActiveField = index;
                return;
            }
            index++;
        }

        if (fieldCount > 0 && sf::FloatRect(340.0f, 160.0f + static_cast<float>(fieldCount) * 78.0f + 20.0f, 170.0f, 46.0f).contains(x, y))
        {
            submitCurrentAction();
            return;
        }

        if (sf::FloatRect(530.0f, 160.0f + static_cast<float>(fieldCount) * 78.0f + 20.0f, 170.0f, 46.0f).contains(x, y))
        {
            currentAction = 0;
            clearForm();
            system->buildWelcomeText(infoText, 20000);
        }
    }
}

void Gui::handleTextInput(unsigned int unicode)
{
    if (unicode < 32 || unicode > 126)
    {
        return;
    }

    char inputChar = static_cast<char>(unicode);

    if (system->getCurrentRole() == 0)
    {
        char *target = loginActiveField == 0 ? loginId : loginPassword;
        int limit = loginActiveField == 0 ? 29 : 49;
        int length = TextUtil::length(target);
        if (length < limit)
        {
            target[length] = inputChar;
            target[length + 1] = '\0';
        }
        return;
    }

    if (currentAction != 0 && formActiveField >= 0 && formActiveField < fieldCount)
    {
        int length = TextUtil::length(fields[formActiveField].value);
        if (length < fields[formActiveField].maxLength)
        {
            fields[formActiveField].value[length] = inputChar;
            fields[formActiveField].value[length + 1] = '\0';
            refreshActionPreview();
        }
    }
}

void Gui::handleBackspace()
{
    if (system->getCurrentRole() == 0)
    {
        char *target = loginActiveField == 0 ? loginId : loginPassword;
        int length = TextUtil::length(target);
        if (length > 0)
        {
            target[length - 1] = '\0';
        }
        return;
    }

    if (currentAction != 0 && formActiveField >= 0 && formActiveField < fieldCount)
    {
        int length = TextUtil::length(fields[formActiveField].value);
        if (length > 0)
        {
            fields[formActiveField].value[length - 1] = '\0';
            refreshActionPreview();
        }
    }
}

void Gui::drawButton(const Button &button, bool selected)
{
    sf::RectangleShape shape;
    shape.setPosition(button.area.left, button.area.top);
    shape.setSize(sf::Vector2f(button.area.width, button.area.height));
    shape.setFillColor(selected ? sf::Color(40, 120, 210) : sf::Color(235, 240, 246));
    shape.setOutlineThickness(1.0f);
    shape.setOutlineColor(sf::Color(150, 160, 175));
    window.draw(shape);

    sf::Text text;
    text.setFont(font);
    text.setString(button.label);
    text.setCharacterSize(18);
    text.setFillColor(selected ? sf::Color::White : sf::Color(30, 40, 55));
    text.setPosition(button.area.left + 14.0f, button.area.top + 10.0f);
    window.draw(text);
}

void Gui::drawTextBlock(const char *text, float x, float y, unsigned int size, sf::Color color)
{
    sf::Text drawable;
    drawable.setFont(font);
    drawable.setString(text);
    drawable.setCharacterSize(size);
    drawable.setFillColor(color);
    drawable.setPosition(x, y);
    window.draw(drawable);
}

void Gui::drawWrappedText(const char *text, float x, float y, float maxWidth, unsigned int size, sf::Color color)
{
    if (text == 0 || text[0] == '\0')
    {
        return;
    }

    sf::Text drawable;
    drawable.setFont(font);
    drawable.setCharacterSize(size);
    drawable.setFillColor(color);

    char line[1500];
    char word[700];
    line[0] = '\0';
    word[0] = '\0';

    float currentY = y;
    int index = 0;
    int wordLength = 0;

    while (true)
    {
        char current = text[index];

        if (current == ' ' || current == '\n' || current == '\0')
        {
            if (wordLength > 0)
            {
                word[wordLength] = '\0';

                char trial[1500];
                TextUtil::copy(trial, line, 1500);
                if (TextUtil::length(trial) > 0)
                {
                    TextUtil::append(trial, " ", 1500);
                }
                TextUtil::append(trial, word, 1500);

                drawable.setString(trial);
                if (drawable.getLocalBounds().width > maxWidth && TextUtil::length(line) > 0)
                {
                    drawable.setString(line);
                    drawable.setPosition(x, currentY);
                    window.draw(drawable);
                    currentY += static_cast<float>(size) + 8.0f;
                    TextUtil::copy(line, word, 1500);
                }
                else
                {
                    TextUtil::copy(line, trial, 1500);
                }

                wordLength = 0;
                word[0] = '\0';
            }

            if (current == '\n')
            {
                drawable.setString(line);
                drawable.setPosition(x, currentY);
                window.draw(drawable);
                currentY += static_cast<float>(size) + 8.0f;
                line[0] = '\0';
            }
            else if (current == '\0')
            {
                if (TextUtil::length(line) > 0)
                {
                    drawable.setString(line);
                    drawable.setPosition(x, currentY);
                    window.draw(drawable);
                }
                break;
            }
        }
        else
        {
            if (wordLength < 699)
            {
                word[wordLength] = current;
                wordLength++;
            }
        }

        index++;
    }
}

void Gui::maskPassword(const char *source, char *masked, int bufferSize)
{
    int length = TextUtil::length(source);
    int index = 0;
    while (index < length && index < bufferSize - 1)
    {
        masked[index] = '*';
        index++;
    }
    masked[index] = '\0';
}

void Gui::drawInputBox(float x, float y, float width, float height, const char *label, const char *value, bool active, bool hideText)
{
    drawTextBlock(label, x, y - 24.0f, 18, sf::Color(45, 55, 72));

    sf::RectangleShape box;
    box.setPosition(x, y);
    box.setSize(sf::Vector2f(width, height));
    box.setFillColor(sf::Color::White);
    box.setOutlineThickness(2.0f);
    box.setOutlineColor(active ? sf::Color(40, 120, 210) : sf::Color(180, 190, 205));
    window.draw(box);

    char display[520];
    if (hideText)
    {
        maskPassword(value, display, 520);
    }
    else
    {
        TextUtil::copy(display, value, 520);
    }

    drawTextBlock(display, x + 12.0f, y + 9.0f, 18, sf::Color(25, 32, 45));
}

void Gui::renderLoginScreen()
{
    Button patientButton = {sf::FloatRect(180.0f, 170.0f, 180.0f, 44.0f), 1, "Patient"};
    Button doctorButton = {sf::FloatRect(380.0f, 170.0f, 180.0f, 44.0f), 2, "Doctor"};
    Button adminButton = {sf::FloatRect(580.0f, 170.0f, 180.0f, 44.0f), 3, "Admin"};
    Button exitButton = {sf::FloatRect(780.0f, 170.0f, 180.0f, 44.0f), 4, "Exit"};

    drawTextBlock("Welcome to MediCore Hospital Management System", 180.0f, 80.0f, 30, sf::Color(28, 42, 62));
    drawTextBlock("Login as:", 180.0f, 135.0f, 20, sf::Color(70, 80, 94));

    drawButton(patientButton, loginRole == 1);
    drawButton(doctorButton, loginRole == 2);
    drawButton(adminButton, loginRole == 3);
    drawButton(exitButton, false);

    drawInputBox(180.0f, 280.0f, 360.0f, 50.0f, "ID", loginId, loginActiveField == 0, false);
    drawInputBox(180.0f, 370.0f, 360.0f, 50.0f, "Password", loginPassword, loginActiveField == 1, true);

    Button loginButton = {sf::FloatRect(180.0f, 460.0f, 180.0f, 50.0f), 5, "Login"};
    drawButton(loginButton, false);

    sf::RectangleShape panel;
    panel.setPosition(700.0f, 260.0f);
    panel.setSize(sf::Vector2f(450.0f, 360.0f));
    panel.setFillColor(sf::Color(248, 250, 252));
    panel.setOutlineThickness(1.0f);
    panel.setOutlineColor(sf::Color(195, 205, 215));
    window.draw(panel);

    drawTextBlock("Status", 720.0f, 280.0f, 22, sf::Color(35, 48, 68));
    drawWrappedText(infoText, 720.0f, 320.0f, 390.0f, 18, sf::Color(75, 82, 98));
}

void Gui::renderDashboard()
{
    configureMenuButtons();

    sf::RectangleShape sidebar;
    sidebar.setPosition(0.0f, 0.0f);
    sidebar.setSize(sf::Vector2f(300.0f, 820.0f));
    sidebar.setFillColor(sf::Color(246, 248, 251));
    sidebar.setOutlineThickness(1.0f);
    sidebar.setOutlineColor(sf::Color(210, 218, 226));
    window.draw(sidebar);

    drawTextBlock("MediCore", 24.0f, 26.0f, 28, sf::Color(28, 42, 62));
    drawTextBlock("Hospital Management", 24.0f, 62.0f, 18, sf::Color(100, 108, 122));

    char welcome[500];
    system->buildWelcomeText(welcome, 500);
    drawWrappedText(welcome, 24.0f, 100.0f, 240.0f, 18, sf::Color(45, 55, 72));

    int index = 0;
    while (index < menuButtonCount)
    {
        drawButton(menuButtons[index], currentAction == menuButtons[index].actionId);
        index++;
    }

    sf::RectangleShape formPanel;
    formPanel.setPosition(320.0f, 20.0f);
    formPanel.setSize(sf::Vector2f(460.0f, 780.0f));
    formPanel.setFillColor(sf::Color::White);
    formPanel.setOutlineThickness(1.0f);
    formPanel.setOutlineColor(sf::Color(214, 220, 228));
    window.draw(formPanel);

    sf::RectangleShape infoPanel;
    infoPanel.setPosition(800.0f, 20.0f);
    infoPanel.setSize(sf::Vector2f(500.0f, 780.0f));
    infoPanel.setFillColor(sf::Color::White);
    infoPanel.setOutlineThickness(1.0f);
    infoPanel.setOutlineColor(sf::Color(214, 220, 228));
    window.draw(infoPanel);

    drawTextBlock("Action Panel", 340.0f, 40.0f, 24, sf::Color(35, 48, 68));
    drawTextBlock("Output", 820.0f, 40.0f, 24, sf::Color(35, 48, 68));

    if (currentAction == 0)
    {
        system->buildWelcomeText(infoText, 20000);
        drawWrappedText("Choose an action from the left menu.", 340.0f, 95.0f, 390.0f, 18, sf::Color(90, 96, 108));
    }
    else
    {
        int fieldIndex = 0;
        while (fieldIndex < fieldCount)
        {
            float top = 160.0f + static_cast<float>(fieldIndex) * 78.0f;
            bool hideText = false;
            drawInputBox(340.0f, top + 28.0f, 420.0f, 44.0f, fields[fieldIndex].label, fields[fieldIndex].value, formActiveField == fieldIndex, hideText);
            fieldIndex++;
        }

        if (fieldCount > 0)
        {
            Button submitButton = {sf::FloatRect(340.0f, 160.0f + static_cast<float>(fieldCount) * 78.0f + 20.0f, 170.0f, 46.0f), 0, "Submit"};
            Button backButton = {sf::FloatRect(530.0f, 160.0f + static_cast<float>(fieldCount) * 78.0f + 20.0f, 170.0f, 46.0f), 0, "Back"};
            drawButton(submitButton, false);
            drawButton(backButton, false);
        }
        else
        {
            drawWrappedText("This action shows data directly. Pick another menu item to continue.", 340.0f, 95.0f, 390.0f, 18, sf::Color(90, 96, 108));
        }
    }

    drawWrappedText(infoText, 820.0f, 90.0f, 440.0f, 17, sf::Color(70, 80, 94));
}

void Gui::render()
{
    window.clear(sf::Color(236, 241, 245));
    window.setView(uiView);
    if (system->getCurrentRole() == 0)
    {
        renderLoginScreen();
    }
    else
    {
        renderDashboard();
    }
    window.display();
}
