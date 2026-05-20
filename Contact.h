#ifndef CONTACT_H
#define CONTACT_H

#include <string>

class Contact {
private:
    int id;
    std::string name;
    std::string phone;

public:
    Contact(int id, const std::string& name, const std::string& phone)
        : id(id), name(name), phone(phone) {}

    int getId() const { return id; }

    const std::string& getName() const { return name; }

    const std::string& getPhone() const { return phone; }

    void setName(const std::string& value) { name = value; }

    void setPhone(const std::string& value) { phone = value; }
};

#endif
