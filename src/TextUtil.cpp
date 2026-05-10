#include "../include/TextUtil.h"

#include <cctype>
#include <cstdio>
#include <ctime>

int TextUtil::length(const char *text)
{
    if (text == 0)
    {
        return 0;
    }

    int count = 0;
    while (text[count] != '\0')
    {
        count++;
    }
    return count;
}

void TextUtil::copy(char *destination, const char *source, int maxLength)
{
    if (destination == 0 || maxLength <= 0)
    {
        return;
    }

    int index = 0;
    if (source != 0)
    {
        while (source[index] != '\0' && index < maxLength - 1)
        {
            destination[index] = source[index];
            index++;
        }
    }
    destination[index] = '\0';
}

bool TextUtil::equals(const char *left, const char *right)
{
    if (left == 0 || right == 0)
    {
        return false;
    }

    int index = 0;
    while (left[index] != '\0' && right[index] != '\0')
    {
        if (left[index] != right[index])
        {
            return false;
        }
        index++;
    }
    return left[index] == '\0' && right[index] == '\0';
}

bool TextUtil::equalsIgnoreCase(const char *left, const char *right)
{
    if (left == 0 || right == 0)
    {
        return false;
    }

    int index = 0;
    while (left[index] != '\0' && right[index] != '\0')
    {
        if (std::tolower(left[index]) != std::tolower(right[index]))
        {
            return false;
        }
        index++;
    }
    return left[index] == '\0' && right[index] == '\0';
}

void TextUtil::append(char *destination, const char *source, int maxLength)
{
    if (destination == 0 || source == 0 || maxLength <= 0)
    {
        return;
    }

    int destinationLength = length(destination);
    int sourceIndex = 0;

    while (source[sourceIndex] != '\0' && destinationLength < maxLength - 1)
    {
        destination[destinationLength] = source[sourceIndex];
        destinationLength++;
        sourceIndex++;
    }

    destination[destinationLength] = '\0';
}

void TextUtil::appendLine(char *destination, const char *source, int maxLength)
{
    append(destination, source, maxLength);
    append(destination, "\n", maxLength);
}

void TextUtil::clear(char *text)
{
    if (text != 0)
    {
        text[0] = '\0';
    }
}

bool TextUtil::isDigits(const char *text)
{
    if (text == 0 || text[0] == '\0')
    {
        return false;
    }

    int index = 0;
    while (text[index] != '\0')
    {
        if (!std::isdigit(text[index]))
        {
            return false;
        }
        index++;
    }
    return true;
}

int TextUtil::toInt(const char *text)
{
    if (text == 0)
    {
        return 0;
    }

    int index = 0;
    int sign = 1;
    int value = 0;

    if (text[index] == '-')
    {
        sign = -1;
        index++;
    }

    while (text[index] != '\0')
    {
        if (std::isdigit(text[index]))
        {
            value = value * 10 + (text[index] - '0');
        }
        index++;
    }

    return value * sign;
}

float TextUtil::toFloat(const char *text)
{
    if (text == 0)
    {
        return 0.0f;
    }

    int index = 0;
    int sign = 1;
    float value = 0.0f;
    float fraction = 0.1f;
    bool decimalFound = false;

    if (text[index] == '-')
    {
        sign = -1;
        index++;
    }

    while (text[index] != '\0')
    {
        if (text[index] == '.')
        {
            decimalFound = true;
        }
        else if (std::isdigit(text[index]))
        {
            if (!decimalFound)
            {
                value = value * 10.0f + static_cast<float>(text[index] - '0');
            }
            else
            {
                value = value + static_cast<float>(text[index] - '0') * fraction;
                fraction = fraction * 0.1f;
            }
        }
        index++;
    }

    return value * sign;
}

void TextUtil::intToText(int value, char *buffer, int bufferSize)
{
    if (buffer == 0 || bufferSize <= 0)
    {
        return;
    }

    std::snprintf(buffer, bufferSize, "%d", value);
}

void TextUtil::floatToText(float value, char *buffer, int bufferSize)
{
    if (buffer == 0 || bufferSize <= 0)
    {
        return;
    }

    std::snprintf(buffer, bufferSize, "%.2f", value);
}

void TextUtil::trimLineEnd(char *text)
{
    if (text == 0)
    {
        return;
    }

    int size = length(text);
    while (size > 0 && (text[size - 1] == '\n' || text[size - 1] == '\r'))
    {
        text[size - 1] = '\0';
        size--;
    }
}

int TextUtil::dateToSerial(const char *date)
{
    if (date == 0 || length(date) < 10)
    {
        return 0;
    }

    int day = (date[0] - '0') * 10 + (date[1] - '0');
    int month = (date[3] - '0') * 10 + (date[4] - '0');
    int year = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');

    return year * 10000 + month * 100 + day;
}

int TextUtil::compareDateAscending(const char *left, const char *right)
{
    int leftValue = dateToSerial(left);
    int rightValue = dateToSerial(right);

    if (leftValue < rightValue)
    {
        return -1;
    }
    if (leftValue > rightValue)
    {
        return 1;
    }
    return 0;
}

int TextUtil::compareDateDescending(const char *left, const char *right)
{
    return compareDateAscending(right, left);
}

int TextUtil::compareTimeAscending(const char *left, const char *right)
{
    int leftHour = (left[0] - '0') * 10 + (left[1] - '0');
    int leftMinute = (left[3] - '0') * 10 + (left[4] - '0');
    int rightHour = (right[0] - '0') * 10 + (right[1] - '0');
    int rightMinute = (right[3] - '0') * 10 + (right[4] - '0');

    int leftValue = leftHour * 60 + leftMinute;
    int rightValue = rightHour * 60 + rightMinute;

    if (leftValue < rightValue)
    {
        return -1;
    }
    if (leftValue > rightValue)
    {
        return 1;
    }
    return 0;
}

int TextUtil::daysDifference(const char *oldDate, const char *newDate)
{
    std::tm oldValue = {};
    std::tm newValue = {};

    oldValue.tm_mday = (oldDate[0] - '0') * 10 + (oldDate[1] - '0');
    oldValue.tm_mon = (oldDate[3] - '0') * 10 + (oldDate[4] - '0') - 1;
    oldValue.tm_year = ((oldDate[6] - '0') * 1000 + (oldDate[7] - '0') * 100 + (oldDate[8] - '0') * 10 + (oldDate[9] - '0')) - 1900;

    newValue.tm_mday = (newDate[0] - '0') * 10 + (newDate[1] - '0');
    newValue.tm_mon = (newDate[3] - '0') * 10 + (newDate[4] - '0') - 1;
    newValue.tm_year = ((newDate[6] - '0') * 1000 + (newDate[7] - '0') * 100 + (newDate[8] - '0') * 10 + (newDate[9] - '0')) - 1900;

    std::time_t oldTime = std::mktime(&oldValue);
    std::time_t newTime = std::mktime(&newValue);

    return static_cast<int>(std::difftime(newTime, oldTime) / (60 * 60 * 24));
}
