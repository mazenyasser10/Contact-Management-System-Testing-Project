#ifndef CONTACT_SERVICE_H
#define CONTACT_SERVICE_H

#include "Contact.h"
#include "ContactRepository.h"
#include <string>
#include <vector>

class ContactService {
private:
    ContactRepository& repo;

public:
    explicit ContactService(ContactRepository& repo);

    void initialize();

    bool addContact(const std::string& name, const std::string& phone);

    std::vector<Contact> viewContacts();

    std::vector<Contact> search(const std::string& keyword);

    bool updateContact(int id, const std::string& name, const std::string& phone);

    bool deleteContact(int id);

    int generateId();
};

#endif
