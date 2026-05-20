#include "pch.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Contact.h"
#include "ContactRepository.h"
#include "ContactService.h"

#include <cstdio>
#include <string>
#include <vector>

using ::testing::SizeIs;

// Unit testing test fixture

class ContactServiceUnitTest : public ::testing::Test
{
protected:
    const std::string testFile = "unit_test_contacts.json";

    ContactRepository repo;
    ContactService service;

    ContactServiceUnitTest()
        : repo(testFile), service(repo)
    {}

    void SetUp() override
    {
        std::remove(testFile.c_str());
        service.initialize();
    }

    void TearDown() override
    {
        std::remove(testFile.c_str());
    }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// UNIT TESTING 

// Add Testing

// UT-01: Add valid contact
TEST_F(ContactServiceUnitTest, UT01_AddValidContact)
{
    bool result = service.addContact("Ali", "01012345678");

    EXPECT_TRUE(result);

    std::vector<Contact> contacts = service.viewContacts();

    ASSERT_THAT(contacts, SizeIs(1));
    EXPECT_EQ(contacts[0].getName(), "Ali");
    EXPECT_EQ(contacts[0].getPhone(), "01012345678");
}

// UT-02: Add contact with empty name
TEST_F(ContactServiceUnitTest, UT02_AddEmptyName)
{
    bool result = service.addContact("", "01012345678");

    EXPECT_FALSE(result);
    EXPECT_THAT(service.viewContacts(), SizeIs(0));
}

// UT-03: Add contact with empty phone
TEST_F(ContactServiceUnitTest, UT03_AddEmptyPhone)
{
    bool result = service.addContact("Ali", "");

    EXPECT_FALSE(result);
    EXPECT_THAT(service.viewContacts(), SizeIs(0));
}

// UT-04: Generate unique ID
TEST_F(ContactServiceUnitTest, UT04_UniqueID)
{
    service.addContact("Ali", "01012345678");
    service.addContact("Mona", "01112345678");
    service.addContact("Sara", "01212345678");

    std::vector<Contact> contacts = service.viewContacts();

    ASSERT_THAT(contacts, SizeIs(3));

    EXPECT_NE(contacts[0].getId(), contacts[1].getId());
    EXPECT_NE(contacts[0].getId(), contacts[2].getId());
    EXPECT_NE(contacts[1].getId(), contacts[2].getId());
}

// UT-05: Validate phone format
TEST_F(ContactServiceUnitTest, UT05_InvalidPhone)
{
    bool result = service.addContact("Ali", "abc123");

    EXPECT_FALSE(result);
    EXPECT_THAT(service.viewContacts(), SizeIs(0));
}

// UT-06: Add duplicate contact
TEST_F(ContactServiceUnitTest, UT06_AddDuplicateContact)
{
    bool firstAdd = service.addContact("Ali", "01012345678");
    bool duplicateAdd = service.addContact("Ali", "01012345678");

    EXPECT_TRUE(firstAdd);
    EXPECT_FALSE(duplicateAdd);

    std::vector<Contact> contacts = service.viewContacts();

    ASSERT_THAT(contacts, SizeIs(1));
    EXPECT_EQ(contacts[0].getName(), "Ali");
    EXPECT_EQ(contacts[0].getPhone(), "01012345678");
}

// Search Testing

// UT-07: Search existing contact
TEST_F(ContactServiceUnitTest, UT07_SearchExistingContact)
{
    service.addContact("Ali", "01012345678");
    service.addContact("Mona", "01112345678");

    std::vector<Contact> result = service.search("Ali");

    ASSERT_THAT(result, SizeIs(1));
    EXPECT_EQ(result[0].getName(), "Ali");
}



// UT-08: Search partial name
TEST_F(ContactServiceUnitTest, UT08_SearchPartialName)
{
    service.addContact("Ali", "01012345678");
    service.addContact("Alaa", "01112345678");
    service.addContact("Mona", "01212345678");

    std::vector<Contact> result = service.search("Al");

    ASSERT_THAT(result, SizeIs(2));
    EXPECT_EQ(result[0].getName(), "Ali");
    EXPECT_EQ(result[1].getName(), "Alaa");
}

// UT-09: Search non-existing contact
TEST_F(ContactServiceUnitTest, UT09_SearchNonExistingContact)
{
    service.addContact("Ali", "01012345678");

    std::vector<Contact> result = service.search("Omar");

    EXPECT_THAT(result, SizeIs(0));
}

// Delete Testing

// UT-010: Delete valid ID
TEST_F(ContactServiceUnitTest, UT10_DeleteValidID)
{
    service.addContact("Ali", "01012345678");

    std::vector<Contact> contacts = service.viewContacts();
    ASSERT_THAT(contacts, SizeIs(1));

    int id = contacts[0].getId();

    bool deleted = service.deleteContact(id);

    EXPECT_TRUE(deleted);
    EXPECT_THAT(service.viewContacts(), SizeIs(0));
}

// UT-11: Delete invalid ID
TEST_F(ContactServiceUnitTest, UT11_DeleteInvalidID)
{
    service.addContact("Ali", "01012345678");

    bool deleted = service.deleteContact(999);

    EXPECT_FALSE(deleted);
    EXPECT_THAT(service.viewContacts(), SizeIs(1));
}

// UT-12: Update valid contact
TEST_F(ContactServiceUnitTest, UT12_UpdateValidContact)
{
    service.addContact("Ali", "01012345678");

    std::vector<Contact> contacts = service.viewContacts();
    ASSERT_THAT(contacts, SizeIs(1));

    int id = contacts[0].getId();

    bool updated = service.updateContact(id, "Ahmed", "01111111111");

    EXPECT_TRUE(updated);

    std::vector<Contact> updatedContacts = service.viewContacts();

    ASSERT_THAT(updatedContacts, SizeIs(1));
    EXPECT_EQ(updatedContacts[0].getName(), "Ahmed");
    EXPECT_EQ(updatedContacts[0].getPhone(), "01111111111");
}

// UT-13: Update invalid ID
TEST_F(ContactServiceUnitTest, UT13_UpdateInvalidID)
{
    service.addContact("Ali", "01012345678");

    bool updated = service.updateContact(999, "Ahmed", "01111111111");

    EXPECT_FALSE(updated);

    std::vector<Contact> contacts = service.viewContacts();

    ASSERT_THAT(contacts, SizeIs(1));
    EXPECT_EQ(contacts[0].getName(), "Ali");
    EXPECT_EQ(contacts[0].getPhone(), "01012345678");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Integration Testing test fixture

class ContactIntegrationTest : public ::testing::Test
{
protected:
    std::string testFile;
    ContactRepository repo;
    ContactService service;

    ContactIntegrationTest()
        : testFile("integration_test_contacts.json"),
        repo(testFile),
        service(repo)
    {}

    void SetUp() override
    {
        std::remove(testFile.c_str());
        service.initialize();
    }

    void TearDown() override
    {
        std::remove(testFile.c_str());
    }
};

// Integration Testing
// IT-01: Add contact integration
TEST_F(ContactIntegrationTest, IT01_AddContactIntegration)
{
    bool result = service.addContact("Ali", "01012345678");

    EXPECT_TRUE(result);

    ContactRepository newRepo(testFile);
    newRepo.load();

    std::vector<Contact> contacts = newRepo.getAll();

    ASSERT_THAT(contacts, SizeIs(1));
    EXPECT_EQ(contacts[0].getName(), "Ali");
    EXPECT_EQ(contacts[0].getPhone(), "01012345678");
}

// IT-02: View contacts integration
TEST_F(ContactIntegrationTest, IT02_ViewContactsIntegration)
{
    service.addContact("Ali", "01012345678");
    service.addContact("Mona", "01112345678");

    ContactRepository newRepo(testFile);
    ContactService newService(newRepo);

    newService.initialize();

    std::vector<Contact> contacts = newService.viewContacts();

    ASSERT_THAT(contacts, SizeIs(2));
    EXPECT_EQ(contacts[0].getName(), "Ali");
    EXPECT_EQ(contacts[0].getPhone(), "01012345678");
    EXPECT_EQ(contacts[1].getName(), "Mona");
    EXPECT_EQ(contacts[1].getPhone(), "01112345678");
}

// IT-03: Search integration
TEST_F(ContactIntegrationTest, IT03_SearchIntegration)
{
    service.addContact("Ali", "01012345678");
    service.addContact("Mona", "01112345678");

    ContactRepository newRepo(testFile);
    ContactService newService(newRepo);

    newService.initialize();

    std::vector<Contact> result = newService.search("Ali");

    ASSERT_THAT(result, SizeIs(1));
    EXPECT_EQ(result[0].getName(), "Ali");
    EXPECT_EQ(result[0].getPhone(), "01012345678");
}

// IT-04: Update integration
TEST_F(ContactIntegrationTest, IT04_UpdateIntegration)
{
    service.addContact("Ali", "01012345678");

    std::vector<Contact> contacts = service.viewContacts();
    ASSERT_THAT(contacts, SizeIs(1));

    int id = contacts[0].getId();

    bool updated = service.updateContact(id, "Ahmed", "01111111111");

    EXPECT_TRUE(updated);

    ContactRepository newRepo(testFile);
    ContactService newService(newRepo);

    newService.initialize();

    std::vector<Contact> updatedContacts = newService.viewContacts();

    ASSERT_THAT(updatedContacts, SizeIs(1));
    EXPECT_EQ(updatedContacts[0].getName(), "Ahmed");
    EXPECT_EQ(updatedContacts[0].getPhone(), "01111111111");
}

// IT-05: Delete integration ------ 
TEST_F(ContactIntegrationTest, IT05_DeleteIntegration)
{
    service.addContact("Ali", "01012345678");

    std::vector<Contact> contacts = service.viewContacts();
    ASSERT_THAT(contacts, SizeIs(1));

    int id = contacts[0].getId();

    bool deleted = service.deleteContact(id);

    EXPECT_TRUE(deleted);

    ContactRepository newRepo(testFile);
    ContactService newService(newRepo);

    newService.initialize();

    std::vector<Contact> remainingContacts = newService.viewContacts();

    EXPECT_THAT(remainingContacts, SizeIs(0));
}