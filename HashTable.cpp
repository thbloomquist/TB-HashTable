//
//  HashTable.cpp
//

#include "HashTable.h"
#include "Flags.h"

/* **************************************************************** */

#if CONSTRUCTOR || ALL
HashTable::HashTable(int tableSize)
{
    size = tableSize;
    table = new Node*[size];
    // TODO: Constructor
    for(int i = 0; i < tableSize; i++) {
        table[i] = nullptr;
    }
}
#endif

/* **************************************************************** */

#if DESTRUCTOR || ALL
HashTable::~HashTable()
{
    for(int i = 0; i < size; i++) {
        delete table[i];
    }
    delete[] table;
}
#endif

/* **************************************************************** */

#if INSERT || ALL
    // TODO: insert() method
    void HashTable::insert(std::string x) {
        if(!find(x)) {
            int hNum = hash(x);
            if(table[hNum] == nullptr) {
                Node *temp = new Node(x, nullptr);
                table[hNum] = temp;
            } else {
                Node *temp = new Node(x, table[hNum]);
                table[hNum] = temp;
            }
        }
    }
#endif

/* **************************************************************** */

#if FIND || ALL
    // TODO: find() method
    bool HashTable::find(std::string x) {
        int hNum = hash(x);
        if(table[hNum] == nullptr) {
            return false;
        } else {
            Node *temp = table[hNum];
            while(temp != nullptr) {
                if(temp->data == x) {
                    return true;
                }
                temp = temp->next;
            }
        }
    }
#endif

/* **************************************************************** */

#if REMOVE || ALL
    // TODO: remove() method
    void HashTable::remove(std::string x) {
        if(find(x)) {
                int hNum = hash(x);
                Node *curN = table[hNum];
                Node *prevN;
                while(curN->data != x) {
                    prevN = curN;
                    curN = curN->next;
                }
                if(table[hNum]->data == x) {
                    table[hNum] = curN->next;
                    delete curN;
                } else {
                    prevN->next = curN->next;
                    delete curN;
                }

//            if(temp->data == x) {
//                delete table[hNum];
//                table[hNum] = nullptr;
//            } else {
//                while(temp->data != x) {
//                    temp = temp->next;
//                }
//                if(temp->next == nullptr) {
//                    temp = nullptr;
//                } else {
//                    Node *nTemp = new Node(temp->next->data, temp->next);
//                    temp = nTemp;
//                }
//            }

        }
    }
#endif

/* **************************************************************** */

#if LOADFACTOR || ALL
// TODO: loadFactor() method
float HashTable::loadFactor()
{
    float num = 0;
    for(int i = 0; i < size; i++) {
        if(table[i] != nullptr) {
            Node *temp = table[i];
            num++;
            temp = temp->next;
            while(temp != nullptr) {
                num++;
                temp = temp->next;
            }
        }
    }
    float lNum = num/size;
    return lNum;
}
#endif

/* **************************************************************** */

#if MAXCHAINLENGTH || ALL
// TODO: maxChainLength() method
void HashTable::maxChainLength(int &maxLength, int &maxSlotIndex)
{
    int tMax = 0;
    int cMax = 0;
    maxSlotIndex = 0;
    for(int i = 0; i < size; i++) {
        if(table[i] != nullptr) {
            Node *temp = table[i];
            while(temp != nullptr) {
                cMax++;
                temp = temp->next;
            }
        }
        if(cMax > tMax) {
            tMax = cMax;
            maxSlotIndex = i;
        }
        cMax = 0;
    }
    maxLength = tMax;
}
#endif

/* **************************************************************** */

#if NUMEMPTYSLOTS || ALL
//TODO: numEmptySlots() method
int HashTable::numEmptySlots()
{
    int num = 0;
    for(int i = 0; i < size; i++) {
        if(table[i] == nullptr) {
            num++;
        }
    }
    return num;
}
#endif

/* **************************************************************** */



/* **************************************************************** */
/* Do NOT modify anything below this line                           */
/* **************************************************************** */

#ifndef BUILD_LIB
unsigned int HashTable::hash(std::string x) {
    unsigned int hashCode = 0;
    std::string::iterator it;
    for (it=x.begin(); it < x.end(); it ++) {
        hashCode = *it + (hashCode << 5) - hashCode;
    }
    return hashCode % size;
}


void HashTable::printHashTable() {
    std::stringstream ss;
    printHashTableToStream(ss);
    std::cout << ss.str();
}


void HashTable::printHashTableToStream(std::stringstream& ss) {
    Node* node;
    // Iterate over table
    for (int i = 0; i < size; i++) {
        ss << "[" << i << "]: ";
        // Iterate over list
        node = table[i];
        while (node != nullptr) {
            ss << node->data << " -> ";
            node = node->next;
        }
        ss << "nullptr" << std::endl;
    }
}
#endif
