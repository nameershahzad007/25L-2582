#ifndef VALIDATOR_H
#define VALIDATOR_H

class Validator
{
public:
    Validator();

    bool isValidId(int id) const;
    bool isValidDate(const char *date) const;
    bool isValidTimeSlot(const char *timeSlot) const;
    bool isValidContact(const char *contact) const;
    bool isValidPassword(const char *password) const;
    bool isPositiveFloat(const char *numberText) const;
    bool isMenuChoice(int choice, int minimum, int maximum) const;
};

#endif
