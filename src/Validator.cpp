#include "../include/Validator.h"
#include "../include/TextUtil.h"

#include <cctype>
#include <ctime>

Validator::Validator()
{
}

bool Validator::isValidId(int id) const
{
    return id > 0;
}

bool Validator::isValidDate(const char *date) const
{
    if (TextUtil::length(date) != 10)
    {
        return false;
    }

    int index = 0;
    while (index < 10)
    {
        if (index == 2 || index == 5)
        {
            if (date[index] != '-')
            {
                return false;
            }
        }
        else if (!std::isdigit(date[index]))
        {
            return false;
        }
        index++;
    }

    int day = (date[0] - '0') * 10 + (date[1] - '0');
    int month = (date[3] - '0') * 10 + (date[4] - '0');
    int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');

    std::time_t now = std::time(0);
    std::tm *currentTime = std::localtime(&now);
    int currentYear = currentTime->tm_year + 1900;

    if (day < 1 || day > 31)
    {
        return false;
    }

    if (month < 1 || month > 12)
    {
        return false;
    }

    if (year < currentYear)
    {
        return false;
    }

    return true;
}

bool Validator::isValidTimeSlot(const char *timeSlot) const
{
    const char *slots[8] = {"09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00"};

    int index = 0;
    while (index < 8)
    {
        if (TextUtil::equals(timeSlot, slots[index]))
        {
            return true;
        }
        index++;
    }
    return false;
}

bool Validator::isValidContact(const char *contact) const
{
    return TextUtil::length(contact) == 11 && TextUtil::isDigits(contact);
}

bool Validator::isValidPassword(const char *password) const
{
    return TextUtil::length(password) >= 6;
}

bool Validator::isPositiveFloat(const char *numberText) const
{
    if (numberText == 0 || numberText[0] == '\0')
    {
        return false;
    }

    bool dotFound = false;
    int index = 0;

    while (numberText[index] != '\0')
    {
        if (numberText[index] == '.')
        {
            if (dotFound)
            {
                return false;
            }
            dotFound = true;
        }
        else if (!std::isdigit(numberText[index]))
        {
            return false;
        }
        index++;
    }

    return TextUtil::toFloat(numberText) > 0.0f;
}

bool Validator::isMenuChoice(int choice, int minimum, int maximum) const
{
    return choice >= minimum && choice <= maximum;
}
