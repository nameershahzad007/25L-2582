#ifndef PERSON_H
#define PERSON_H

class Person
{
protected:
    int id;
    char name[51];
    char contact[20];
    char password[50];

public:
    Person();
    Person(int personId, const char *personName, const char *personContact, const char *personPassword);
    virtual ~Person();

    int getId() const;
    const char *getName() const;
    const char *getContact() const;
    const char *getPassword() const;

    void setId(int value);
    void setName(const char *value);
    void setContact(const char *value);
    void setPassword(const char *value);

    virtual const char *getRole() const = 0;
    virtual void getDisplayText(char *buffer, int bufferSize) const = 0;
};

#endif
