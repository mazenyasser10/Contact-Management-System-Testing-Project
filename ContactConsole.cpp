#include "ContactConsole.h"
#include "Utils.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

static std::string readLine() {
    std::string line;
    if (!std::getline(std::cin, line))
        return "";
    return line;
}

static bool parseInt(const std::string& input, int& out) {
    std::istringstream iss(input);
    iss >> out;
    if (iss.fail() || !iss.eof())
        return false;
    return true;
}

ContactConsole::ContactConsole(ContactService& svc) : service(svc) {}

void ContactConsole::showMenu() {
    std::cout << "\n--- Contact Manager ---\n";
    std::cout << "1. Add Contact\n";
    std::cout << "2. View Contacts\n";
    std::cout << "3. Search Contact\n";
    std::cout << "4. Update Contact\n";
    std::cout << "5. Delete Contact\n";
    std::cout << "6. Exit\n";
    std::cout << "Select option: ";
}

void ContactConsole::handleAdd() {
    std::cout << "Enter name: ";
    std::string name = readLine();
    std::cout << "Enter phone: ";
    std::string phone = readLine();

    if (!Utils::isValidName(name)) {
        std::cout << "Invalid name.\n";
        return;
    }
    if (!Utils::isValidPhone(phone)) {
        std::cout << "Invalid phone: digits only.\n";
        return;
    }

    if (service.addContact(name, phone))
        std::cout << "Contact added and saved.\n";
    else
        std::cout << "Failed to add contact.\n";
}

void ContactConsole::handleView() {
    std::vector<Contact> contacts = service.viewContacts();
    if (contacts.empty()) {
        std::cout << "(No contacts found.)\n";
        return;
    }

    for (size_t i = 0; i < contacts.size(); ++i) {
        std::cout << "ID: " << contacts[i].getId()
                  << "  Name: " << contacts[i].getName()
                  << "  Phone: " << contacts[i].getPhone() << "\n";
    }
}

void ContactConsole::handleSearch() {
    std::cout << "Enter name or part of name: ";
    std::string keyword = readLine();
    if (!Utils::isValidName(keyword)) {
        std::cout << "Invalid keyword.\n";
        return;
    }

    std::vector<Contact> matches = service.search(keyword);
    if (matches.empty()) {
        std::cout << "No matching contacts.\n";
        return;
    }

    for (size_t i = 0; i < matches.size(); ++i) {
        std::cout << "ID: " << matches[i].getId()
                  << "  Name: " << matches[i].getName()
                  << "  Phone: " << matches[i].getPhone() << "\n";
    }
}

void ContactConsole::handleUpdate() {
    std::cout << "Enter contact ID to update: ";
    std::string idLine = readLine();
    int id = 0;
    if (!parseInt(idLine, id) || id <= 0) {
        std::cout << "Invalid ID.\n";
        return;
    }

    std::cout << "Enter new name: ";
    std::string name = readLine();
    std::cout << "Enter new phone: ";
    std::string phone = readLine();

    if (!Utils::isValidName(name)) {
        std::cout << "Invalid name.\n";
        return;
    }
    if (!Utils::isValidPhone(phone)) {
        std::cout << "Invalid phone: digits only.\n";
        return;
    }

    if (service.updateContact(id, name, phone))
        std::cout << "Contact updated and saved.\n";
    else
        std::cout << "Update failed: invalid ID.\n";
}

void ContactConsole::handleDelete() {
    std::cout << "Enter contact ID to delete: ";
    std::string idLine = readLine();
    int id = 0;
    if (!parseInt(idLine, id) || id <= 0) {
        std::cout << "Invalid ID.\n";
        return;
    }

    if (service.deleteContact(id))
        std::cout << "Contact deleted and saved.\n";
    else
        std::cout << "Delete failed: invalid ID.\n";
}

void ContactConsole::run() {
    service.initialize();

    for (;;) {
        showMenu();
        std::string choice = readLine();
        int option = 0;
        if (!parseInt(choice, option)) {
            std::cout << "Invalid choice. Enter 1-6.\n";
            continue;
        }

        if (option == 1)
            handleAdd();
        else if (option == 2)
            handleView();
        else if (option == 3)
            handleSearch();
        else if (option == 4)
            handleUpdate();
        else if (option == 5)
            handleDelete();
        else if (option == 6) {
            std::cout << "Goodbye.\n";
            break;
        } else
            std::cout << "Invalid choice. Enter 1-6.\n";
    }
}
