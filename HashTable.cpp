
#include <iostream>
#include <vector>
#include "HashTable.h"

HashTable::HashTable(int size) {
    tableSize = nextPrime(size);
    table.resize(tableSize, Entry());
    currentSize = 0;
}

void HashTable::insert(int key) {
    if (search(key) != -1) {
        std::cout << "Duplicate key insertion is not allowed" << std::endl;
        return;
    }

    if (static_cast<double>(currentSize + 1) / tableSize > loadFactorThreshold) {
        rehash();
    }

    int idx = quadraticProbe(key, true);
    if (idx == -1) {
        std::cout << "Max probing limit reached!" << std::endl;
        return;
    }

    table[idx] = Entry(key, true);
    currentSize++;
}

void HashTable::remove(int key) {
    int idx = quadraticProbe(key, false);
    if (idx != -1 && table[idx].isActive) {
        table[idx].isActive = false;
        currentSize--;
    } else {
        std::cout << "Element not found" << std::endl;
    }
}

int HashTable::search(int key) {
    int idx = quadraticProbe(key, false);
    if (idx != -1 && table[idx].isActive) {
        return idx;
    }
    return -1;
}

void HashTable::printTable() {
    for (const auto& entry : table) {
        if (entry.isActive) {
            std::cout << entry.key << " ";
        } else {
            std::cout << "- ";
        }
    }
    std::cout << std::endl;
}

int HashTable::hashFunction(int key) {
    return key % tableSize;
}

int HashTable::quadraticProbe(int key, bool forInsertion) {
    int hash = hashFunction(key);
    int i = 0;
    int maxProbes = (tableSize + 1) / 2;
    int idx;

    while (i < maxProbes) {
        idx = (hash + i * i) % tableSize;

        if (forInsertion) {
            if (!table[idx].isActive) {
                return idx;
            }
        } else {
            if (table[idx].key == key && table[idx].isActive) {
                return idx;
            } else if (!table[idx].isActive && table[idx].key == -1) {
                // Stop if an empty slot is found during search
                return -1;
            }
        }
        i++;
    }
    return -1; // Max probing limit reached
}

void HashTable::rehash() {
    int oldSize = tableSize;
    tableSize = nextPrime(2 * tableSize);
    std::vector<Entry> oldTable = table;
    table.clear();
    table.resize(tableSize, Entry());
    currentSize = 0;

    for (const auto& entry : oldTable) {
        if (entry.isActive) {
            insert(entry.key);
        }
    }
}

bool HashTable::isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;

    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

int HashTable::nextPrime(int n) {
    while (!isPrime(n)) {
        n++;
    }
    return n;
}
