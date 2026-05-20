
#include "ContactService.h"
#include "Utils.h"

ContactService::ContactService(ContactRepository& repository) : repo(repository) {}

void ContactService::initialize() {
    repo.load();
}

bool ContactService::addContact(const std::string& name, const std::string& phone) {
    if (!Utils::isValidName(name) || !Utils::isValidPhone(phone))
        return false;

    int id = generateId();
    repo.add(Contact(id, name, phone));
    repo.save();
    return true;
}

std::vector<Contact> ContactService::viewContacts() {
    return repo.getAll();
}

std::vector<Contact> ContactService::search(const std::string& keyword) {
    std::vector<Contact> out;
    if (!Utils::isValidName(keyword))
        return out;

    std::vector<Contact> all = repo.getAll();
    for (size_t i = 0; i < all.size(); ++i) {
        if (Utils::contains(all[i].getName(), keyword))
            out.push_back(all[i]);
    }
    return out;
}

bool ContactService::updateContact(int id, const std::string& name, const std::string& phone) {
    if (!Utils::isValidName(name) || !Utils::isValidPhone(phone))
        return false;

    bool updated = repo.update(Contact(id, name, phone));
    if (!updated)
        return false;

    repo.save();
    return true;
}

bool ContactService::deleteContact(int id) {
    bool removed = repo.remove(id);
    if (!removed)
        return false;

    repo.save();
    return true;
}

int ContactService::generateId() {
    std::vector<Contact> all = repo.getAll();
    int maxId = 0;
    for (size_t i = 0; i < all.size(); ++i) {
        if (all[i].getId() > maxId)
            maxId = all[i].getId();
    }
    return maxId + 1;
}
