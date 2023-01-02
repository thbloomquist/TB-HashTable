//
//  tests.cpp
//

#define CATCH_CONFIG_RUNNER
#define CATCH_CONFIG_CONSOLE_WIDTH 150

#include <iostream>
#include "HashTable.h"
#include "catch.hpp"


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing constructor", "[CONSTRUCTOR]") {
    HashTable t(17);
    
    SECTION("constructor must initialize the HashTable size") {
        INFO("size should be initialized to 17");
        REQUIRE(t.size == 17);
    }
    
    SECTION("constructor must initialize the HashTable's backing array") {
        REQUIRE(t.table != nullptr);
    }
    
    SECTION("constructor must initialize the contents of the HashTable's backing array") {
        for (int i=0; i < 17; i++) {
            REQUIRE(t.table[i] == nullptr);
        }
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing insert(x) method on an empty HashTable", "[INSERT]") {
    HashTable t(7);
    INFO("created a HashTable of size 7");

    SECTION("verify structure of HashTable after single insert into empty HashTable") {
        t.insert("Harpies");
        INFO("inserted value \"Harpies\"");
        const char* hashTableString = ""
            "[0]: nullptr\n"
            "[1]: nullptr\n"
            "[2]: nullptr\n"
            "[3]: nullptr\n"
            "[4]: nullptr\n"
            "[5]: nullptr\n"
            "[6]: Harpies -> nullptr\n";
        INFO("\nHashTable should be: \n" << hashTableString);
        std::stringstream ss;
        t.printHashTableToStream(ss);
        INFO("Your HashTable is: \n" << ss.str());
        REQUIRE(t.table[0] == nullptr);                   // slot 0
        REQUIRE(t.table[1] == nullptr);                   // slot 1
        REQUIRE(t.table[2] == nullptr);                   // slot 2
        REQUIRE(t.table[3] == nullptr);                   // slot 3
        REQUIRE(t.table[4] == nullptr);                   // slot 4
        REQUIRE(t.table[5] == nullptr);                   // slot 5
        REQUIRE(t.table[6]->data == "Harpies");        // slot 6
        REQUIRE(t.table[6]->next == nullptr);
    }
    
    SECTION("verify structure of HashTable after multiple inserts into empty HashTable (one insert per slot)") {
        t.insert("Medusa");     // slot 0
        t.insert("Cerberus");   // slot 1
        t.insert("Minotaur");   // slot 2
        t.insert("Sirens");     // slot 3
        t.insert("Phoenix");    // slot 4
        t.insert("Sphinx");     // slot 5
        t.insert("Harpies");    // slot 6
        INFO("inserted values: \"Medusa\", \"Cerberus\", \"Minotaur\", \"Sirens\", \"Phoenix\", \"Sphinx\", \"Harpies\"");
        const char* hashTableString = ""
            "[0]: Medusa -> nullptr\n"
            "[1]: Cerberus -> nullptr\n"
            "[2]: Minotaur -> nullptr\n"
            "[3]: Sirens -> nullptr\n"
            "[4]: Phoenix -> nullptr\n"
            "[5]: Sphinx -> nullptr\n"
            "[6]: Harpies -> nullptr\n";
        INFO("\nHashTable should be: \n" << hashTableString);
        std::stringstream ss;
        t.printHashTableToStream(ss);
        INFO("Your HashTable is: \n" << ss.str());
        REQUIRE(t.table[0]->data == "Medusa");        // slot 0
        REQUIRE(t.table[0]->next == nullptr);
        REQUIRE(t.table[1]->data == "Cerberus");      // slot 1
        REQUIRE(t.table[1]->next == nullptr);
        REQUIRE(t.table[2]->data == "Minotaur");      // slot 2
        REQUIRE(t.table[2]->next == nullptr);
        REQUIRE(t.table[3]->data == "Sirens");        // slot 3
        REQUIRE(t.table[3]->next == nullptr);
        REQUIRE(t.table[4]->data == "Phoenix");       // slot 4
        REQUIRE(t.table[4]->next == nullptr);
        REQUIRE(t.table[5]->data == "Sphinx");        // slot 5
        REQUIRE(t.table[5]->next == nullptr);
        REQUIRE(t.table[6]->data == "Harpies");       // slot 6
        REQUIRE(t.table[6]->next == nullptr);
    }
}


TEST_CASE("testing insert(x) method on a non-empty HashTable", "[INSERT]") {
    HashTable t(7);
    INFO("created a HashTable of size 7");
    Node *medusaNode = new Node("Medusa", nullptr);
    Node *cerberusNode = new Node("Cerberus", nullptr);
    Node *griffinNode = new Node("Griffin", nullptr);
    Node *pegasusNode = new Node("Pegasus", griffinNode);
    Node *arachneNode = new Node("Arachne", pegasusNode);
    Node *minotaurNode = new Node("Minotaur", arachneNode);
    Node *cyclopsNode = new Node("Cyclops", minotaurNode);
    Node *phoenixNode = new Node("Phoenix", nullptr);
    Node *sphinxNode = new Node("Sphinx", nullptr);
    Node *harpiesNode = new Node("Harpies", nullptr);
    Node *chimeraNode = new Node("Chimera", harpiesNode);
    t.table[0] = medusaNode;
    t.table[1] = cerberusNode;
    t.table[2] = cyclopsNode;
    t.table[3] = nullptr;
    t.table[4] = phoenixNode;
    t.table[5] = sphinxNode;
    t.table[6] = chimeraNode;
    const char* hashTableString = ""
        "[0]: Medusa -> nullptr\n"
        "[1]: Cerberus -> nullptr\n"
        "[2]: Cyclops -> Minotaur -> Arachne -> Pegasus -> Griffin -> nullptr\n"
        "[3]: nullptr\n"
        "[4]: Phoenix -> nullptr\n"
        "[5]: Sphinx -> nullptr\n"
        "[6]: Chimera -> Harpies -> nullptr\n";
    INFO("inserted many nodes into HashTable");
    INFO("\nbefore calling insert(x), HashTable should be: \n" << hashTableString);
    std::stringstream ss;
    t.printHashTableToStream(ss);
    INFO("Your HashTable is: \n" << ss.str());

    SECTION("verify structure of HashTable after single insert into empty slot of non-empty HashTable") {
        t.insert("Sirens");     // inserts into slot 3
        INFO("after attempting to insert value: \"Sirens\"");
        const char* hashTableString2 = ""
            "[0]: Medusa -> nullptr\n"
            "[1]: Cerberus -> nullptr\n"
            "[2]: Cyclops -> Minotaur -> Arachne -> Pegasus -> Griffin -> nullptr\n"
            "[3]: Sirens -> nullptr\n"
            "[4]: Phoenix -> nullptr\n"
            "[5]: Sphinx -> nullptr\n"
            "[6]: Chimera -> Harpies -> nullptr\n";
        INFO("HashTable should be: \n" << hashTableString2);
        std::stringstream ss2;
        t.printHashTableToStream(ss2);
        INFO("Your HashTable is: \n" << ss2.str());
        REQUIRE(t.table[0]->data == "Medusa");                          // slot 0
        REQUIRE(t.table[0]->next == nullptr);
        REQUIRE(t.table[1]->data == "Cerberus");                        // slot 1
        REQUIRE(t.table[1]->next == nullptr);
        REQUIRE(t.table[2]->data == "Cyclops");                         // slot 2
        REQUIRE(t.table[2]->next->data == "Minotaur");
        REQUIRE(t.table[2]->next->next->data == "Arachne");
        REQUIRE(t.table[2]->next->next->next->data == "Pegasus");
        REQUIRE(t.table[2]->next->next->next->next->data == "Griffin");
        REQUIRE(t.table[2]->next->next->next->next->next == nullptr);
        REQUIRE(t.table[3]->data == "Sirens");                          // slot 3
        REQUIRE(t.table[3]->next == nullptr);
        REQUIRE(t.table[4]->data == "Phoenix");                         // slot 4
        REQUIRE(t.table[4]->next == nullptr);
        REQUIRE(t.table[5]->data == "Sphinx");                          // slot 5
        REQUIRE(t.table[5]->next == nullptr);
        REQUIRE(t.table[6]->data == "Chimera");                         // slot 6
        REQUIRE(t.table[6]->next->data == "Harpies");
        REQUIRE(t.table[6]->next->next == nullptr);
    }
    
    SECTION("verify structure of HashTable after single insert into non-empty slot of non-empty HashTable (single node already in slot)") {
        t.insert("Centaur");     // inserts into slot 1
        INFO("after attempting to insert value: \"Centaur\"");
        const char* hashTableString2 = ""
            "[0]: Medusa -> nullptr\n"
            "[1]: Centaur -> Cerberus -> nullptr\n"
            "[2]: Cyclops -> Minotaur -> Arachne -> Pegasus -> Griffin -> nullptr\n"
            "[3]: nullptr\n"
            "[4]: Phoenix -> nullptr\n"
            "[5]: Sphinx -> nullptr\n"
            "[6]: Chimera -> Harpies -> nullptr\n";
        INFO("HashTable should be: \n" << hashTableString2);
        std::stringstream ss2;
        t.printHashTableToStream(ss2);
        INFO("Your HashTable is: \n" << ss2.str());
        REQUIRE(t.table[0]->data == "Medusa");                          // slot 0
        REQUIRE(t.table[0]->next == nullptr);
        REQUIRE(t.table[1]->data == "Centaur");                         // slot 1
        REQUIRE(t.table[1]->next->data == "Cerberus");
        REQUIRE(t.table[1]->next->next == nullptr);
        REQUIRE(t.table[2]->data == "Cyclops");                         // slot 2
        REQUIRE(t.table[2]->next->data == "Minotaur");
        REQUIRE(t.table[2]->next->next->data == "Arachne");
        REQUIRE(t.table[2]->next->next->next->data == "Pegasus");
        REQUIRE(t.table[2]->next->next->next->next->data == "Griffin");
        REQUIRE(t.table[2]->next->next->next->next->next == nullptr);
        REQUIRE(t.table[3] == nullptr);                                    // slot 3
        REQUIRE(t.table[4]->data == "Phoenix");                         // slot 4
        REQUIRE(t.table[4]->next == nullptr);
        REQUIRE(t.table[5]->data == "Sphinx");                          // slot 5
        REQUIRE(t.table[5]->next == nullptr);
        REQUIRE(t.table[6]->data == "Chimera");                         // slot 6
        REQUIRE(t.table[6]->next->data == "Harpies");
        REQUIRE(t.table[6]->next->next == nullptr);
    }
    
    SECTION("verify structure of HashTable after single insert into non-empty slot of non-empty HashTable (multiple nodes already in slot)") {
        t.insert("Argus");     // inserts into slot 6
        INFO("after attempting to insert value: \"Argus\"");
        const char* hashTableString2 = ""
            "[0]: Medusa -> nullptr\n"
            "[1]: Cerberus -> nullptr\n"
            "[2]: Cyclops -> Minotaur -> Arachne -> Pegasus -> Griffin -> nullptr\n"
            "[3]: nullptr\n"
            "[4]: Phoenix -> nullptr\n"
            "[5]: Sphinx -> nullptr\n"
            "[6]: Argus -> Chimera -> Harpies -> nullptr\n";
        INFO("HashTable should be: \n" << hashTableString2);
        std::stringstream ss2;
        t.printHashTableToStream(ss2);
        INFO("Your HashTable is: \n" << ss2.str());
        REQUIRE(t.table[0]->data == "Medusa");                          // slot 0
        REQUIRE(t.table[0]->next == nullptr);
        REQUIRE(t.table[1]->data == "Cerberus");                        // slot 1
        REQUIRE(t.table[1]->next == nullptr);
        REQUIRE(t.table[2]->data == "Cyclops");                         // slot 2
        REQUIRE(t.table[2]->next->data == "Minotaur");
        REQUIRE(t.table[2]->next->next->data == "Arachne");
        REQUIRE(t.table[2]->next->next->next->data == "Pegasus");
        REQUIRE(t.table[2]->next->next->next->next->data == "Griffin");
        REQUIRE(t.table[2]->next->next->next->next->next == nullptr);
        REQUIRE(t.table[3] == nullptr);                                    // slot 3
        REQUIRE(t.table[4]->data == "Phoenix");                         // slot 4
        REQUIRE(t.table[4]->next == nullptr);
        REQUIRE(t.table[5]->data == "Sphinx");                          // slot 5
        REQUIRE(t.table[5]->next == nullptr);
        REQUIRE(t.table[6]->data == "Argus");                           // slot 6
        REQUIRE(t.table[6]->next->data == "Chimera");
        REQUIRE(t.table[6]->next->next->data == "Harpies");
        REQUIRE(t.table[6]->next->next->next == nullptr);
    }
    
    SECTION("verify structure of HashTable after attempting to insert a duplicate value into non-empty HashTable") {
        t.insert("Pegasus");     // inserts into slot 2
        INFO("after attempting to insert value: \"Pegasus\"");
        const char* hashTableString2 = ""
            "[0]: Medusa -> nullptr\n"
            "[1]: Cerberus -> nullptr\n"
            "[2]: Cyclops -> Minotaur -> Arachne -> Pegasus -> Griffin -> nullptr\n"
            "[3]: nullptr\n"
            "[4]: Phoenix -> nullptr\n"
            "[5]: Sphinx -> nullptr\n"
            "[6]: Chimera -> Harpies -> nullptr\n";
        INFO("HashTable should still be: \n" << hashTableString2);
        std::stringstream ss2;
        t.printHashTableToStream(ss2);
        INFO("Your HashTable is: \n" << ss2.str());
        REQUIRE(t.table[0]->data == "Medusa");                          // slot 0
        REQUIRE(t.table[0]->next == nullptr);
        REQUIRE(t.table[1]->data == "Cerberus");                        // slot 1
        REQUIRE(t.table[1]->next == nullptr);
        REQUIRE(t.table[2]->data == "Cyclops");                         // slot 2
        REQUIRE(t.table[2]->next->data == "Minotaur");
        REQUIRE(t.table[2]->next->next->data == "Arachne");
        REQUIRE(t.table[2]->next->next->next->data == "Pegasus");
        REQUIRE(t.table[2]->next->next->next->next->data == "Griffin");
        REQUIRE(t.table[2]->next->next->next->next->next == nullptr);
        REQUIRE(t.table[3] == nullptr);                                    // slot 3
        REQUIRE(t.table[4]->data == "Phoenix");                         // slot 4
        REQUIRE(t.table[4]->next == nullptr);
        REQUIRE(t.table[5]->data == "Sphinx");                          // slot 5
        REQUIRE(t.table[5]->next == nullptr);
        REQUIRE(t.table[6]->data == "Chimera");                         // slot 6
        REQUIRE(t.table[6]->next->data == "Harpies");
        REQUIRE(t.table[6]->next->next == nullptr);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing find(x) method on an empty HashTable", "[FIND]") {
    HashTable t(17);
    
    SECTION("verify that find(x) returns false when HashTable is empty") {
        REQUIRE(t.find("Medusa") == false);
        REQUIRE(t.find("") == false);
    }
}


TEST_CASE("testing find(x) method on a non-empty HashTable", "[FIND]") {
    HashTable t(7);
    INFO("created a HashTable of size 7");
    Node *medusaNode = new Node("Medusa", nullptr);
    Node *cerberusNode = new Node("Cerberus", nullptr);
    Node *centaurNode = new Node("Centaur", cerberusNode);
    Node *griffinNode = new Node("Griffin", nullptr);
    Node *pegasusNode = new Node("Pegasus", griffinNode);
    Node *arachneNode = new Node("Arachne", pegasusNode);
    Node *minotaurNode = new Node("Minotaur", arachneNode);
    Node *cyclopsNode = new Node("Cyclops", minotaurNode);
    Node *phoenixNode = new Node("Phoenix", nullptr);
    Node *sphinxNode = new Node("Sphinx", nullptr);
    Node *harpiesNode = new Node("Harpies", nullptr);
    Node *chimeraNode = new Node("Chimera", harpiesNode);
    t.table[0] = medusaNode;
    t.table[1] = centaurNode;
    t.table[2] = cyclopsNode;
    t.table[3] = nullptr;
    t.table[4] = phoenixNode;
    t.table[5] = sphinxNode;
    t.table[6] = chimeraNode;
    const char* hashTableString = ""
        "[0]: Medusa -> nullptr\n"
        "[1]: Centaur -> Cerberus -> nullptr\n"
        "[2]: Cyclops -> Minotaur -> Arachne -> Pegasus -> Griffin -> nullptr\n"
        "[3]: nullptr\n"
        "[4]: Phoenix -> nullptr\n"
        "[5]: Sphinx -> nullptr\n"
        "[6]: Chimera -> Harpies -> nullptr\n";
    INFO("inserted many nodes into HashTable");
    INFO("\nbefore calling find(x), HashTable should be: \n" << hashTableString);
    std::stringstream ss;
    t.printHashTableToStream(ss);
    INFO("Your HashTable is: \n" << ss.str());
    
    SECTION("verify that find(x) returns false when attempting to find a value not in HashTable (slot is empty)") {
        INFO("should fail to find the value \"Sirens\"");
        REQUIRE(t.find("Sirens") == false);
    }
    
    SECTION("verify that find(x) returns false when attempting to find a value not in HashTable (slot has other nodes)") {
        INFO("should fail to find the value \"Argus\"");
        REQUIRE(t.find("Argus") == false);
    }
        
    SECTION("verify that find(x) returns true when the value exists and its node is the only node in the HashTable slot") {
        INFO("should successfully find the value \"Phoenix\"");
        REQUIRE(t.find("Phoenix") == true);
    }
        
    SECTION("verify that find(x) returns true when the value exists and its node is at the head of a multi-node chain") {
        INFO("should successfully find the value \"Cyclops\"");
        REQUIRE(t.find("Cyclops") == true);
    }
        
    SECTION("verify that find(x) returns true when the value exists and its node is in the middle of a multi-node chain") {
        INFO("should successfully find the value \"Arachne\"");
        REQUIRE(t.find("Arachne") == true);
    }
        
    SECTION("verify that find(x) returns true when the value exists and its node is at the tail of a multi-node chain") {
        INFO("should successfully find the value \"Harpies\"");
        REQUIRE(t.find("Harpies") == true);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing rempve(x) method on an empty HashTable", "[REMOVE]") {
    HashTable t(17);
    INFO("created a HashTable of size 17");
    INFO("before calling remove(x), HashTable should be emtpy");
    
    INFO("before calling remove(x), size should be 17");
    REQUIRE(t.size == 17);
    INFO("before calling remove(x), backing array should exist");
    REQUIRE(t.table != nullptr);
    INFO("before calling remove(x), contents of backing array should all be nullptr");
    for (int i=0; i < 17; i++) {
        REQUIRE(t.table[i] == nullptr);
    }
    
    SECTION("verify that remove(x) doesn't break anything when HashTable is empty") {
        t.remove("testString");
        INFO("after calling remove(x), size should be 17");
        REQUIRE(t.size == 17);
        INFO("after calling remove(x), backing array should exist");
        REQUIRE(t.table != nullptr);
        INFO("after calling remove(x), contents of backing array should all be nullptr");
        for (int i=0; i < 17; i++) {
            REQUIRE(t.table[i] == nullptr);
        }
    }
}

    
TEST_CASE("testing rempve(x) method on a non-empty HashTable", "[REMOVE]") {
    HashTable t(7);
    INFO("created a HashTable of size 7");
    Node *medusaNode = new Node("Medusa", nullptr);
    Node *cerberusNode = new Node("Cerberus", nullptr);
    Node *centaurNode = new Node("Centaur", cerberusNode);
    Node *griffinNode = new Node("Griffin", nullptr);
    Node *pegasusNode = new Node("Pegasus", griffinNode);
    Node *arachneNode = new Node("Arachne", pegasusNode);
    Node *minotaurNode = new Node("Minotaur", arachneNode);
    Node *cyclopsNode = new Node("Cyclops", minotaurNode);
    Node *phoenixNode = new Node("Phoenix", nullptr);
    Node *sphinxNode = new Node("Sphinx", nullptr);
    Node *harpiesNode = new Node("Harpies", nullptr);
    Node *chimeraNode = new Node("Chimera", harpiesNode);
    t.table[0] = medusaNode;
    t.table[1] = centaurNode;
    t.table[2] = cyclopsNode;
    t.table[3] = nullptr;
    t.table[4] = phoenixNode;
    t.table[5] = sphinxNode;
    t.table[6] = chimeraNode;
    const char* hashTableString = ""
        "[0]: Medusa -> nullptr\n"
        "[1]: Centaur -> Cerberus -> nullptr\n"
        "[2]: Cyclops -> Minotaur -> Arachne -> Pegasus -> Griffin -> nullptr\n"
        "[3]: nullptr\n"
        "[4]: Phoenix -> nullptr\n"
        "[5]: Sphinx -> nullptr\n"
        "[6]: Chimera -> Harpies -> nullptr\n";
    INFO("inserted many nodes into HashTable");
    INFO("\nbefore calling remove(x), HashTable should be: \n" << hashTableString);
    std::stringstream ss;
    t.printHashTableToStream(ss);
    INFO("Your HashTable is: \n" << ss.str());
    
    SECTION("verify that remove(x) doesn't break anything when attempting to remove a value not in HashTable (slot is empty)") {
        t.remove("Sirens");
        INFO("after attempting to remove non-existent value: \"Sirens\"");
        INFO("HashTable should still be: \n" << hashTableString);
        std::stringstream ss2;
        t.printHashTableToStream(ss2);
        INFO("Your HashTable is: \n" << ss2.str());
        REQUIRE(t.table[0]->data == "Medusa");                          // slot 0
        REQUIRE(t.table[0]->next == nullptr);
        REQUIRE(t.table[1]->data == "Centaur");                         // slot 1
        REQUIRE(t.table[1]->next->data == "Cerberus");
        REQUIRE(t.table[1]->next->next == nullptr);
        REQUIRE(t.table[2]->data == "Cyclops");                         // slot 2
        REQUIRE(t.table[2]->next->data == "Minotaur");
        REQUIRE(t.table[2]->next->next->data == "Arachne");
        REQUIRE(t.table[2]->next->next->next->data == "Pegasus");
        REQUIRE(t.table[2]->next->next->next->next->data == "Griffin");
        REQUIRE(t.table[2]->next->next->next->next->next == nullptr);
        REQUIRE(t.table[3] == nullptr);                                    // slot 3
        REQUIRE(t.table[4]->data == "Phoenix");                         // slot 4
        REQUIRE(t.table[4]->next == nullptr);
        REQUIRE(t.table[5]->data == "Sphinx");                          // slot 5
        REQUIRE(t.table[5]->next == nullptr);
        REQUIRE(t.table[6]->data == "Chimera");                         // slot 6
        REQUIRE(t.table[6]->next->data == "Harpies");
        REQUIRE(t.table[6]->next->next == nullptr);
    }
    
    SECTION("verify that remove(x) doesn't break anything when attempting to remove a value not in HashTable (slot has other nodes)") {
        t.remove("Argus");
        INFO("after attempting to remove non-existent value: \"Argus\"");
        INFO("HashTable should still be: \n" << hashTableString);
        std::stringstream ss2;
        t.printHashTableToStream(ss2);
        INFO("Your HashTable is: \n" << ss2.str());
        REQUIRE(t.table[0]->data == "Medusa");                          // slot 0
        REQUIRE(t.table[0]->next == nullptr);
        REQUIRE(t.table[1]->data == "Centaur");                         // slot 1
        REQUIRE(t.table[1]->next->data == "Cerberus");
        REQUIRE(t.table[1]->next->next == nullptr);
        REQUIRE(t.table[2]->data == "Cyclops");                         // slot 2
        REQUIRE(t.table[2]->next->data == "Minotaur");
        REQUIRE(t.table[2]->next->next->data == "Arachne");
        REQUIRE(t.table[2]->next->next->next->data == "Pegasus");
        REQUIRE(t.table[2]->next->next->next->next->data == "Griffin");
        REQUIRE(t.table[2]->next->next->next->next->next == nullptr);
        REQUIRE(t.table[3] == nullptr);                                    // slot 3
        REQUIRE(t.table[4]->data == "Phoenix");                         // slot 4
        REQUIRE(t.table[4]->next == nullptr);
        REQUIRE(t.table[5]->data == "Sphinx");                          // slot 5
        REQUIRE(t.table[5]->next == nullptr);
        REQUIRE(t.table[6]->data == "Chimera");                         // slot 6
        REQUIRE(t.table[6]->next->data == "Harpies");
        REQUIRE(t.table[6]->next->next == nullptr);
    }

    SECTION("verify that remove(x) successfully removes a node when that node is the only node in the HashTable slot") {
        t.remove("Phoenix");
        INFO("after attempting to remove value: \"Phoenix\"");
        const char* hashTableString2 = ""
            "[0]: Medusa -> nullptr\n"
            "[1]: Centaur -> Cerberus -> nullptr\n"
            "[2]: Cyclops -> Minotaur -> Arachne -> Pegasus -> Griffin -> nullptr\n"
            "[3]: nullptr\n"
            "[4]: nullptr\n"
            "[5]: Sphinx -> nullptr\n"
            "[6]: Chimera -> Harpies -> nullptr\n";
        INFO("HashTable should be: \n" << hashTableString2);
        std::stringstream ss2;
        t.printHashTableToStream(ss2);
        INFO("Your HashTable is: \n" << ss2.str());
        REQUIRE(t.table[0]->data == "Medusa");                          // slot 0
        REQUIRE(t.table[0]->next == nullptr);
        REQUIRE(t.table[1]->data == "Centaur");                         // slot 1
        REQUIRE(t.table[1]->next->data == "Cerberus");
        REQUIRE(t.table[1]->next->next == nullptr);
        REQUIRE(t.table[2]->data == "Cyclops");                         // slot 2
        REQUIRE(t.table[2]->next->data == "Minotaur");
        REQUIRE(t.table[2]->next->next->data == "Arachne");
        REQUIRE(t.table[2]->next->next->next->data == "Pegasus");
        REQUIRE(t.table[2]->next->next->next->next->data == "Griffin");
        REQUIRE(t.table[2]->next->next->next->next->next == nullptr);
        REQUIRE(t.table[3] == nullptr);                                    // slot 3
        REQUIRE(t.table[4] == nullptr);                                    // slot 4
        REQUIRE(t.table[5]->data == "Sphinx");                          // slot 5
        REQUIRE(t.table[5]->next == nullptr);
        REQUIRE(t.table[6]->data == "Chimera");                         // slot 6
        REQUIRE(t.table[6]->next->data == "Harpies");
        REQUIRE(t.table[6]->next->next == nullptr);
    }

    SECTION("verify that remove(x) successfully removes a node when that node is at the head of a multi-node chain") {
        t.remove("Cyclops");
        INFO("after attempting to remove value: \"Cyclops\"");
        const char* hashTableString2 = ""
            "[0]: Medusa -> nullptr\n"
            "[1]: Centaur -> Cerberus -> nullptr\n"
            "[2]: Minotaur -> Arachne -> Pegasus -> Griffin -> nullptr\n"
            "[3]: nullptr\n"
            "[4]: Phoenix -> nullptr\n"
            "[5]: Sphinx -> nullptr\n"
            "[6]: Chimera -> Harpies -> nullptr\n";
        INFO("HashTable should be: \n" << hashTableString2);
        std::stringstream ss2;
        t.printHashTableToStream(ss2);
        INFO("Your HashTable is: \n" << ss2.str());
        REQUIRE(t.table[0]->data == "Medusa");                          // slot 0
        REQUIRE(t.table[0]->next == nullptr);
        REQUIRE(t.table[1]->data == "Centaur");                         // slot 1
        REQUIRE(t.table[1]->next->data == "Cerberus");
        REQUIRE(t.table[1]->next->next == nullptr);
        REQUIRE(t.table[2]->data == "Minotaur");                        // slot 2
        REQUIRE(t.table[2]->next->data == "Arachne");
        REQUIRE(t.table[2]->next->next->data == "Pegasus");
        REQUIRE(t.table[2]->next->next->next->data == "Griffin");
        REQUIRE(t.table[2]->next->next->next->next == nullptr);
        REQUIRE(t.table[3] == nullptr);                                    // slot 3
        REQUIRE(t.table[4]->data == "Phoenix");                         // slot 4
        REQUIRE(t.table[4]->next == nullptr);
        REQUIRE(t.table[5]->data == "Sphinx");                          // slot 5
        REQUIRE(t.table[5]->next == nullptr);
        REQUIRE(t.table[6]->data == "Chimera");                         // slot 6
        REQUIRE(t.table[6]->next->data == "Harpies");
        REQUIRE(t.table[6]->next->next == nullptr);
    }
    
    SECTION("verify that remove(x) successfully removes a node when that node is in the middle of a multi-node chain") {
        t.remove("Arachne");
        INFO("after attempting to remove value: \"Arachne\"");
        const char* hashTableString2 = ""
            "[0]: Medusa -> nullptr\n"
            "[1]: Centaur -> Cerberus -> nullptr\n"
            "[2]: Cyclops -> Minotaur -> Pegasus -> Griffin -> nullptr\n"
            "[3]: nullptr\n"
            "[4]: Phoenix -> nullptr\n"
            "[5]: Sphinx -> nullptr\n"
            "[6]: Chimera -> Harpies -> nullptr\n";
        INFO("HashTable should be: \n" << hashTableString2);
        std::stringstream ss2;
        t.printHashTableToStream(ss2);
        INFO("Your HashTable is: \n" << ss2.str());
        REQUIRE(t.table[0]->data == "Medusa");                          // slot 0
        REQUIRE(t.table[0]->next == nullptr);
        REQUIRE(t.table[1]->data == "Centaur");                         // slot 1
        REQUIRE(t.table[1]->next->data == "Cerberus");
        REQUIRE(t.table[1]->next->next == nullptr);
        REQUIRE(t.table[2]->data == "Cyclops");                         // slot 2
        REQUIRE(t.table[2]->next->data == "Minotaur");
        REQUIRE(t.table[2]->next->next->data == "Pegasus");
        REQUIRE(t.table[2]->next->next->next->data == "Griffin");
        REQUIRE(t.table[2]->next->next->next->next == nullptr);
        REQUIRE(t.table[3] == nullptr);                                    // slot 3
        REQUIRE(t.table[4]->data == "Phoenix");                         // slot 4
        REQUIRE(t.table[4]->next == nullptr);
        REQUIRE(t.table[5]->data == "Sphinx");                          // slot 5
        REQUIRE(t.table[5]->next == nullptr);
        REQUIRE(t.table[6]->data == "Chimera");                         // slot 6
        REQUIRE(t.table[6]->next->data == "Harpies");
        REQUIRE(t.table[6]->next->next == nullptr);
    }
    
    SECTION("verify that remove(x) successfully removes a node when that node is at the tail of a multi-node chain") {
        t.remove("Harpies");
        INFO("after attempting to remove value: \"Harpies\"");
        const char* hashTableString2 = ""
            "[0]: Medusa -> nullptr\n"
            "[1]: Centaur -> Cerberus -> nullptr\n"
            "[2]: Cyclops -> Minotaur -> Arachne -> Pegasus -> Griffin -> nullptr\n"
            "[3]: nullptr\n"
            "[4]: Phoenix -> nullptr\n"
            "[5]: Sphinx -> nullptr\n"
            "[6]: Chimera -> nullptr\n";
        INFO("HashTable should be: \n" << hashTableString2);
        std::stringstream ss2;
        t.printHashTableToStream(ss2);
        INFO("Your HashTable is: \n" << ss2.str());
        REQUIRE(t.table[0]->data == "Medusa");                          // slot 0
        REQUIRE(t.table[0]->next == nullptr);
        REQUIRE(t.table[1]->data == "Centaur");                         // slot 1
        REQUIRE(t.table[1]->next->data == "Cerberus");
        REQUIRE(t.table[1]->next->next == nullptr);
        REQUIRE(t.table[2]->data == "Cyclops");                         // slot 2
        REQUIRE(t.table[2]->next->data == "Minotaur");
        REQUIRE(t.table[2]->next->next->data == "Arachne");
        REQUIRE(t.table[2]->next->next->next->data == "Pegasus");
        REQUIRE(t.table[2]->next->next->next->next->data == "Griffin");
        REQUIRE(t.table[2]->next->next->next->next->next == nullptr);
        REQUIRE(t.table[3] == nullptr);                                    // slot 3
        REQUIRE(t.table[4]->data == "Phoenix");                         // slot 4
        REQUIRE(t.table[4]->next == nullptr);
        REQUIRE(t.table[5]->data == "Sphinx");                          // slot 5
        REQUIRE(t.table[5]->next == nullptr);
        REQUIRE(t.table[6]->data == "Chimera");                         // slot 6
        REQUIRE(t.table[6]->next == nullptr);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing loadFactor() method on an empty HashTable", "[LOADFACTOR]") {
    HashTable t(17);
    INFO("created a HashTable of size 17");
    
    SECTION("verify that loadFactor() returns the correct value when called on empty HashTable") {
        INFO("when called on empty HashTable, loadFactor() should be 0.0");
        REQUIRE(t.loadFactor() == 0.0f);
    }
}


TEST_CASE("testing loadFactor() method on a non-empty HashTable", "[LOADFACTOR]") {

    SECTION("verify that loadFactor() returns the correct value when multiple chains exists in HashTable of size 8") {
        HashTable t(8);
        INFO("created a HashTable of size 8");
        Node *n1 = new Node("testString_0.1", nullptr);
        Node *n2 = new Node("testString_0.0", n1);
        t.table[0] = n2;
        Node *n3 = new Node("testString_15.2", nullptr);
        Node *n4 = new Node("testString_15.1", n3);
        Node *n5 = new Node("testString_15.0", n4);
        t.table[7] = n5;
        std::stringstream ss;
        t.printHashTableToStream(ss);
        INFO("inserted two nodes into slot 0 of HashTable");
        INFO("inserted three nodes into slot 7 of HashTable");
        INFO("before calling loadFactor(), HashTable is: \n\n" << ss.str());
        INFO("when multiple chains exists in HashTable of size 8 (with a total of 5 nodes), \nloadFactor() should return 0.625f");
        REQUIRE(t.loadFactor() == 0.625f);
    }
    
    SECTION("verify that loadFactor() returns the correct value when multiple chains exists in HashTable of size 16") {
        HashTable t(16);
        INFO("created a HashTable of size 16");
        Node *n1 = new Node("testString_0.1", nullptr);
        Node *n2 = new Node("testString_0.0", n1);
        t.table[0] = n2;
        Node *n3 = new Node("testString_15.2", nullptr);
        Node *n4 = new Node("testString_15.1", n3);
        Node *n5 = new Node("testString_15.0", n4);
        t.table[15] = n5;
        std::stringstream ss;
        t.printHashTableToStream(ss);
        INFO("inserted two nodes into slot 0 of HashTable");
        INFO("inserted three nodes into slot 15 of HashTable");
        INFO("before calling loadFactor(), HashTable is: \n\n" << ss.str());
        INFO("when multiple chains exists in HashTable of size 16 (with a total of 5 nodes), \nloadFactor() should return 0.3125f");
        REQUIRE(t.loadFactor() == 0.3125f);
    }
    
    SECTION("verify that loadFactor() returns the correct value when 7 nodes exists in HashTable of size 7 (one in each slot)") {
        HashTable t(7);
        INFO("created a HashTable of size 7");
        for (int i=0; i < 7; i++) {
            std::string str = "testString_" + std::to_string(i);
            Node *n = new Node(str, nullptr);
            t.table[i] = n;
        }
        std::stringstream ss;
        t.printHashTableToStream(ss);
        INFO("inserted a single node into each slot of HashTable");
        INFO("before calling loadFactor(), HashTable is: \n\n" << ss.str());
        INFO("when a single node exists in each slot of the HashTable, \nloadFactor() should return 1.0f");
        REQUIRE(t.loadFactor() == 1.0f);
    }
    
    SECTION("verify that loadFactor() returns the correct value when 9 nodes exists in HashTable of size 8 (multiple nodes in one of the slots)") {
        HashTable t(8);
        INFO("created a HashTable of size 8");
        for (int i=0; i < 7; i++) {
            std::string str = "testString_" + std::to_string(i);
            Node *n = new Node(str, nullptr);
            t.table[i] = n;
        }
        Node *n1 = new Node("testString_7.2", nullptr);
        Node *n2 = new Node("testString_7.1", n1);
        Node *n3 = new Node("testString_7.0", n2);
        t.table[7] = n3;
        std::stringstream ss;
        t.printHashTableToStream(ss);
        INFO("inserted a single node into each slot of HashTable");
        INFO("inserted two additional nodes into slot 7 of HashTable");
        INFO("before calling loadFactor(), HashTable is: \n\n" << ss.str());
        INFO("when 10 nodes exists in a HashTable of size 8, \nloadFactor() should return 1.25f");
        REQUIRE(t.loadFactor() == 1.25f);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing maxChainLength(&maxLength, &maxSlotIndex) method on an empty HashTable", "[MAXCHAINLENGTH]") {
    HashTable t(17);
    INFO("created a HashTable of size 17");
    
    SECTION("verify that maxChainLength(&maxLength, &maxSlotIndex) returns the correct values when called on empty HashTable") {
        int maxLength = 65536; int maxSlotIndex = 65536; // large "uninitialized" values
        t.maxChainLength(maxLength, maxSlotIndex);
        INFO("when called on empty HashTable, maxLength and maxSlotIndex should both be 0");
        REQUIRE(maxLength == 0);
        REQUIRE(maxSlotIndex == 0);
    }
}


TEST_CASE("testing maxChainLength(&maxLength, &maxSlotIndex) method on a non-empty HashTable", "[MAXCHAINLENGTH]") {
    HashTable t(17);
    INFO("created a HashTable of size 17");
    
    SECTION("verify that maxChainLength(&maxLength, &maxSlotIndex) returns the correct values when a single chain of length 1 exists in slot 0") {
        Node *n = new Node("testString_0", nullptr);
        t.table[0] = n;
        std::stringstream ss;
        t.printHashTableToStream(ss);
        INFO("inserted a single node into slot 0 of HashTable");
        INFO("before calling maxChainLength(&maxLength, &maxSlotIndex), HashTable is: \n\n" << ss.str());
        int maxLength = 65536; int maxSlotIndex = 65536;
        t.maxChainLength(maxLength, maxSlotIndex);
        INFO("when a single chain of length 1 exists in slot 0, maxLength should be 1 and maxSlotIndex should be 0");
        REQUIRE(maxLength == 1);
        REQUIRE(maxSlotIndex == 0);
    }
    
    SECTION("verify that maxChainLength(&maxLength, &maxSlotIndex) returns the correct values when a single chain of length 3 exists in slot 0") {
        Node *n1 = new Node("testString_0.2", nullptr);
        Node *n2 = new Node("testString_0.1", n1);
        Node *n3 = new Node("testString_0.0", n2);
        t.table[0] = n3;
        std::stringstream ss;
        t.printHashTableToStream(ss);
        INFO("inserted three nodes into slot 0 of HashTable");
        INFO("before calling maxChainLength(&maxLength, &maxSlotIndex), HashTable is: \n\n" << ss.str());
        int maxLength = 65536; int maxSlotIndex = 65536;
        t.maxChainLength(maxLength, maxSlotIndex);
        INFO("when a single chain of length 3 exists in slot 0, maxLength should be 3 and maxSlotIndex should be 0");
        REQUIRE(maxLength == 3);
        REQUIRE(maxSlotIndex == 0);
    }
    
    SECTION("verify that maxChainLength(&maxLength, &maxSlotIndex) returns the correct values when a single chain of length 3 exists in slot 16") {
        Node *n1 = new Node("testString_0.2", nullptr);
        Node *n2 = new Node("testString_0.1", n1);
        Node *n3 = new Node("testString_0.0", n2);
        t.table[16] = n3;
        std::stringstream ss;
        t.printHashTableToStream(ss);
        INFO("inserted three nodes into slot 16 of HashTable");
        INFO("before calling maxChainLength(&maxLength, &maxSlotIndex), HashTable is: \n\n" << ss.str());
        int maxLength = 65536; int maxSlotIndex = 65536;
        t.maxChainLength(maxLength, maxSlotIndex);
        INFO("when a single chain of length 3 exists in slot 16, maxLength should be 3 and maxSlotIndex should be 0");
        REQUIRE(maxLength == 3);
        REQUIRE(maxSlotIndex == 16);
    }
    
    SECTION("verify that maxChainLength(&maxLength, &maxSlotIndex) returns the correct values when the longest chain is the first of multiple chains") {
        Node *n1 = new Node("testString_4.2", nullptr);
        Node *n2 = new Node("testString_4.1", n1);
        Node *n3 = new Node("testString_4.0", n2);
        t.table[4] = n3;
        Node *n4 = new Node("testString_7.1", nullptr);
        Node *n5 = new Node("testString_7.0", n4);
        t.table[7] = n5;
        std::stringstream ss;
        t.printHashTableToStream(ss);
        INFO("inserted three nodes into slot 4 of HashTable");
        INFO("inserted two nodes into slot 7 of HashTable");
        INFO("before calling maxChainLength(&maxLength, &maxSlotIndex), HashTable is: \n\n" << ss.str());
        int maxLength = 65536; int maxSlotIndex = 65536;
        t.maxChainLength(maxLength, maxSlotIndex);
        INFO("when a chain of length 3 exists in slot 4 and a chain of length 2 exists in slot 7, \nmaxLength should be 3 and maxSlotIndex should be 4");
        REQUIRE(maxLength == 3);
        REQUIRE(maxSlotIndex == 4);
    }
    
    SECTION("verify that maxChainLength(&maxLength, &maxSlotIndex) returns the correct values when the longest chain is the last of multiple chains") {
        Node *n1 = new Node("testString_4.1", nullptr);
        Node *n2 = new Node("testString_4.0", n1);
        t.table[4] = n2;
        Node *n3 = new Node("testString_7.2", nullptr);
        Node *n4 = new Node("testString_7.1", n3);
        Node *n5 = new Node("testString_7.0", n4);
        t.table[7] = n5;
        std::stringstream ss;
        t.printHashTableToStream(ss);
        INFO("inserted two nodes into slot 4 of HashTable");
        INFO("inserted three nodes into slot 7 of HashTable");
        INFO("before calling maxChainLength(&maxLength, &maxSlotIndex), HashTable is: \n\n" << ss.str());
        int maxLength = 65536; int maxSlotIndex = 65536;
        t.maxChainLength(maxLength, maxSlotIndex);
        INFO("when a chain of length 2 exists in slot 4 and a chain of length 3 exists in slot 7, \nmaxLength should be 3 and maxSlotIndex should be 7");
        REQUIRE(maxLength == 3);
        REQUIRE(maxSlotIndex == 7);
    }
    
    SECTION("verify that maxChainLength(&maxLength, &maxSlotIndex) returns the correct values when multiple chains have the maxLength") {
        Node *n1 = new Node("testString_4.2", nullptr);
        Node *n2 = new Node("testString_4.1", n1);
        Node *n3 = new Node("testString_4.0", n2);
        t.table[4] = n3;
        Node *n4 = new Node("testString_7.2", nullptr);
        Node *n5 = new Node("testString_7.1", n4);
        Node *n6 = new Node("testString_7.0", n5);
        t.table[7] = n6;
        std::stringstream ss;
        t.printHashTableToStream(ss);
        INFO("inserted three nodes into slot 4 of HashTable");
        INFO("inserted three nodes into slot 7 of HashTable");
        INFO("before calling maxChainLength(&maxLength, &maxSlotIndex), HashTable is: \n\n" << ss.str());
        int maxLength = 65536; int maxSlotIndex = 65536;
        t.maxChainLength(maxLength, maxSlotIndex);
        INFO("when a chain of length 3 exists in slot 4 and a chain of length 3 exists in slot 7, \nmaxLength should be 3 and maxSlotIndex should be 4");
        REQUIRE(maxLength == 3);
        REQUIRE(maxSlotIndex == 4);
    }
}


/* **************************************************************** */
/* **************************************************************** */


TEST_CASE("testing numEmptySlots() method on an empty HashTable", "[NUMEMPTYSLOTS]") {
    
    SECTION("verify that numEmptySlots() returns the correct value when called on empty HashTable of size 1") {
        HashTable t1(1);
        INFO("created a HashTable of size 1");
        INFO("when called on empty HashTable of size 1, numEmptySlots() should return 1");
        REQUIRE(t1.numEmptySlots() == 1);
    }
    
    SECTION("verify that numEmptySlots() returns the correct value when called on empty HashTable of size 100") {
        HashTable t100(100);
        INFO("created a HashTable of size 100");
        INFO("when called on empty HashTable of size 100, numEmptySlots() should return 100");
        REQUIRE(t100.numEmptySlots() == 100);
    }
}


TEST_CASE("testing numEmptySlots() method on a non-empty HashTable", "[NUMEMPTYSLOTS]") {
    HashTable t(17);
    INFO("created a HashTable of size 17");
    
    SECTION("verify that numEmptySlots() returns the correct value when a single node exists in slot 0") {
        Node *n = new Node("testString_0", nullptr);
        t.table[0] = n;
        std::stringstream ss;
        t.printHashTableToStream(ss);
        INFO("inserted a single node into slot 0 of HashTable");
        INFO("before calling numEmptySlots(), HashTable is: \n\n" << ss.str());
        INFO("when a single node exists in slot 0, numEmptySlots() should return 16");
        REQUIRE(t.numEmptySlots() == 16);
    }
    
    SECTION("verify that numEmptySlots() returns the correct value when a single node exists in the last slot") {
        Node *n = new Node("testString_16", nullptr);
        t.table[16] = n;
        std::stringstream ss;
        t.printHashTableToStream(ss);
        INFO("inserted a single node into slot 16 of HashTable");
        INFO("before calling numEmptySlots(), HashTable is: \n\n" << ss.str());
        INFO("when a single node exists in slot 16, numEmptySlots() should return 16");
        REQUIRE(t.numEmptySlots() == 16);
    }
    
    SECTION("verify that numEmptySlots() returns the correct value when multiple nodes exist in a single slot") {
        Node *n1 = new Node("testString_0.1", nullptr);
        Node *n2 = new Node("testString_0.0", n1);
        t.table[0] = n2;
        std::stringstream ss;
        t.printHashTableToStream(ss);
        INFO("inserted two nodes into slot 0 of HashTable");
        INFO("before calling numEmptySlots(), HashTable is: \n\n" << ss.str());
        INFO("when multiple nodes exist in a slot 0, numEmptySlots() should return 16");
        REQUIRE(t.numEmptySlots() == 16);
    }

    SECTION("verify that numEmptySlots() returns the correct value when multiple nodes exist throughout the HashTable") {
        for (int i=0; i < 17; i++) {
            if (i % 2 == 0) {
                std::string str = "testString_" + std::to_string(i);
                Node *n = new Node(str, nullptr);
                t.table[i] = n;
            }
        }
        std::stringstream ss;
        t.printHashTableToStream(ss);
        INFO("inserted nodes into even numbered slots of HashTable");
        INFO("before calling numEmptySlots(), HashTable is: \n\n" << ss.str());
        INFO("when nodes exist in even numbered slots, numEmptySlots() should return 8");
        REQUIRE(t.numEmptySlots() == 8);
    }
    
    SECTION("verify that numEmptySlots() returns the correct value when the HashTable has no empty slots") {
        for (int i=0; i < 17; i++) {
            std::string str = "testString_" + std::to_string(i);
            Node *n = new Node(str, nullptr);
            t.table[i] = n;
        }
        std::stringstream ss;
        t.printHashTableToStream(ss);
        INFO("inserted a single node into each slot of HashTable");
        INFO("before calling numEmptySlots(), HashTable is: \n\n" << ss.str());
        INFO("when nodes exist in every slot, numEmptySlots() should return 0");
        REQUIRE(t.numEmptySlots() == 0);
    }
}


/* **************************************************************** */
/* **************************************************************** */



/* **************************************************************** */
/* **************************************************************** */
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
/* **************************************************************** */
/* **************************************************************** */


int main( int argc, char const* const* const argv )
{
    // global setup...
    std::cout << BOLDCYAN << std::endl;
    std::cout << "###############################################################################" << std::endl;
    std::cout << "############################# Running Unit Tests ##############################" << std::endl;
    std::cout << "###############################################################################" << std::endl;
    std::cout << RESET << std::endl;

    int result = Catch::Session().run( argc, argv );

    // global clean-up...
    std::cout << BOLDCYAN << std::endl;
    std::cout << "###############################################################################" << std::endl;
    std::cout << "########################### Done Running Unit Tests ###########################" << std::endl;
    std::cout << "###############################################################################" << std::endl;
    std::cout << RESET << std::endl;

    return result;
}
