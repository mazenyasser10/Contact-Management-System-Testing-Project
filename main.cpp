#include "ContactConsole.h"
#include "ContactRepository.h"
#include "ContactService.h"
#include <string>


int main() {
    const std::string dataFile = "contacts.json";
    ContactRepository repo(dataFile);
    ContactService service(repo);
    ContactConsole console(service);
    console.run();
    return 0;
}

