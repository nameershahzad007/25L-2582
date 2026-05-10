#include "../include/Person.h"
#include "../include/TextUtil.h"

Person::Person()
{
    id = 0;
    TextUtil::copy(name, "", 51);
    TextUtil::copy(contact, "", 20);
    TextUtil::copy(password, "", 50);
}

Person::Person(int personId, const char *personName, const char *personContact, const char *personPassword)
{
    id = personId;
    TextUtil::copy(name, personName, 51);
    TextUtil::copy(contact, personContact, 20);
    TextUtil::copy(password, personPassword, 50);
}

Person::~Person()
{
}

int Person::getId() const
{
    return id;
}

const char *Person::getName() const
{
    return name;
}

const char *Person::getContact() const
{
    return contact;
}

const char *Person::getPassword() const
{
    return password;
}

void Person::setId(int value)
{
    id = value;
}

void Person::setName(const char *value)
{
    TextUtil::copy(name, value, 51);
}

void Person::setContact(const char *value)
{
    TextUtil::copy(contact, value, 20);
}

void Person::setPassword(const char *value)
{
    TextUtil::copy(password, value, 50);
}
