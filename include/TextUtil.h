#ifndef TEXTUTIL_H
#define TEXTUTIL_H

class TextUtil
{
public:
    static int length(const char *text);
    static void copy(char *destination, const char *source, int maxLength);
    static bool equals(const char *left, const char *right);
    static bool equalsIgnoreCase(const char *left, const char *right);
    static void append(char *destination, const char *source, int maxLength);
    static void appendLine(char *destination, const char *source, int maxLength);
    static void clear(char *text);
    static bool isDigits(const char *text);
    static int toInt(const char *text);
    static float toFloat(const char *text);
    static void intToText(int value, char *buffer, int bufferSize);
    static void floatToText(float value, char *buffer, int bufferSize);
    static void trimLineEnd(char *text);
    static int compareDateAscending(const char *left, const char *right);
    static int compareDateDescending(const char *left, const char *right);
    static int compareTimeAscending(const char *left, const char *right);
    static int dateToSerial(const char *date);
    static int daysDifference(const char *oldDate, const char *newDate);
};

#endif
