#ifndef CONTACT_REPOSITORY_H
#define CONTACT_REPOSITORY_H

#include "Contact.h"
#include <string>
#include <vector>

class ContactRepository {
private:
    std::vector<Contact> contacts;
    std::string filePath;

public:
    explicit ContactRepository(const std::string& filePath);

    void load();

    void save();

    std::vector<Contact> getAll() const;

    void add(const Contact& contact);

    bool remove(int id);

    bool update(const Contact& contact);
};

#endif
