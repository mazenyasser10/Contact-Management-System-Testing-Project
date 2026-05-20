#ifndef CONTACT_CONSOLE_H
#define CONTACT_CONSOLE_H

#include "ContactService.h"

class ContactConsole {
private:
    ContactService& service;

    void showMenu();

    void handleAdd();

    void handleView();

    void handleSearch();

    void handleUpdate();

    void handleDelete();

public:
    explicit ContactConsole(ContactService& service);

    void run();
};

#endif
