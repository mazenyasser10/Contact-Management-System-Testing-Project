
#include "ContactRepository.h"
#include "json.hpp"
#include <fstream>
#include <sstream>

using json = nlohmann::json;

ContactRepository::ContactRepository(const std::string& path) : filePath(path) {}

void ContactRepository::load() {
    contacts.clear();

    std::ifstream in(filePath.c_str());
    if (!in)
        return;

    std::stringstream buffer;
    buffer << in.rdbuf();
    std::string raw = buffer.str();
    if (raw.empty())
        return;

    try {
        json j = json::parse(raw);
        if (!j.contains("contacts") || !j["contacts"].is_array())
            return;

        for (size_t i = 0; i < j["contacts"].size(); ++i) {
            const json& item = j["contacts"][i];
            if (!item.contains("id") || !item.contains("name") || !item.contains("phone"))
                continue;
            int id = item["id"].get<int>();
            std::string name = item["name"].get<std::string>();
            std::string phone = item["phone"].get<std::string>();
            contacts.push_back(Contact(id, name, phone));
        }
    } catch (...) {
        contacts.clear();
    }
}

void ContactRepository::save() {
    json j;
    j["contacts"] = json::array();
    for (size_t i = 0; i < contacts.size(); ++i) {
        json item;
        item["id"] = contacts[i].getId();
        item["name"] = contacts[i].getName();
        item["phone"] = contacts[i].getPhone();
        j["contacts"].push_back(item);
    }

    std::ofstream out(filePath.c_str());
    out << j.dump(2);
}

std::vector<Contact> ContactRepository::getAll() const {
    return contacts;
}

void ContactRepository::add(const Contact& contact) {
    contacts.push_back(contact);
}

bool ContactRepository::remove(int id) {
    for (size_t i = 0; i < contacts.size(); ++i) {
        if (contacts[i].getId() == id) {
            contacts.erase(contacts.begin() + static_cast<std::ptrdiff_t>(i));
            return true;
        }
    }
    return false;
}

bool ContactRepository::update(const Contact& contact) {
    for (size_t i = 0; i < contacts.size(); ++i) {
        if (contacts[i].getId() == contact.getId()) {
            contacts[i].setName(contact.getName());
            contacts[i].setPhone(contact.getPhone());
            return true;
        }
    }
    return false;
}
