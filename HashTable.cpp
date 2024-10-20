#include <iostream>
#include <vector>
using namespace std;

class CustomHashTable {
private:
    int capacity;      // Size of the table
    int elements;      // Number of elements currently in the table
    int* storage;      // Array representing the hash table
    float loadThreshold = 0.8;  // Load factor threshold for resizing

    // Hash function: computes index using modulo operation
    int computeHash(int key) {
        return key % capacity;
    }

public:
    // Constructor to initialize the table with given size
    CustomHashTable(int initialSize) {
        capacity = initialSize;
        elements = 0;
        storage = new int[capacity];

        // Initialize all slots to -1 (indicating empty)
        for (int i = 0; i < capacity; i++) {
            storage[i] = -1;
        }
    }

    // Insert a key into the hash table
    void insert(int key) {
        float currentLoad = static_cast<float>(elements) / capacity;

        if (currentLoad >= loadThreshold) {
            expandAndRehash();
        }

        int index = computeHash(key);

        for (int i = 0; computeHash(index + i * i) != index || i == 0; i++) {
            int newIndex = computeHash(index + i * i);

            if (storage[newIndex] == key) {
                cout << "Duplicate key insertion is not allowed" << endl;
                return;
            }

            if (storage[newIndex] == -1) {
                storage[newIndex] = key;
                elements++;
                return;
            }
        }
        cout << "Max probing limit reached!" << endl;
    }

    // Remove a key from the table
    void remove(int key) {
        int index = computeHash(key);

        for (int i = 0; computeHash(index + i * i) != index || i == 0; i++) {
            int newIndex = computeHash(index + i * i);

            if (storage[newIndex] == key) {
                storage[newIndex] = -1;
                elements--;
                return;
            }
        }
        cout << "Element not found" << endl;
    }

    // Resize the hash table when load factor exceeds the threshold
    void expandAndRehash() {
        int oldCapacity = capacity;
        capacity = findNextPrime(2 * oldCapacity);

        int* newStorage = new int[capacity];
        for (int i = 0; i < capacity; i++) {
            newStorage[i] = -1;
        }

        for (int i = 0; i < oldCapacity; i++) {
            if (storage[i] != -1) {
                int key = storage[i];
                int index = computeHash(key);

                if (newStorage[index] == -1) {
                    newStorage[index] = key;
                    continue;
                }

                for (int j = 1; j < capacity; j++) {
                    int newIndex = computeHash(index + j * j);
                    if (newStorage[newIndex] == -1) {
                        newStorage[newIndex] = key;
                        break;
                    }
                }
            }
        }
        delete[] storage;
        storage = newStorage;
    }

    // Search for a key in the table and return its index, or -1 if not found
    int search(int key) {
        int index = computeHash(key);

        for (int i = 0; computeHash(index + i * i) != index || i == 0; i++) {
            int newIndex = computeHash(index + i * i);

            if (storage[newIndex] == -1) {
                return -1;
            }
            if (storage[newIndex] == key) {
                return newIndex;
            }
        }
        return -1;
    }

    // Print the contents of the table
    void printTable() {
        for (int i = 0; i < capacity; i++) {
            if (storage[i] == -1) {
                cout << "- ";
            } else {
                cout << storage[i] << " ";
            }
        }
        cout << endl;
    }

    // Check if a number is prime
    bool isPrime(int num) {
        if (num <= 1) return false;
        if (num == 2 || num == 3) return true;
        if (num % 2 == 0 || num % 3 == 0) return false;
        for (int i = 5; i * i <= num; i += 6) {
            if (num % i == 0 || num % (i + 2) == 0) return false;
        }
        return true;
    }

    // Find the next prime number greater than or equal to n
    int findNextPrime(int n) {
        int candidate = n;
        while (!isPrime(candidate)) {
            candidate++;
        }
        return candidate;
    }
};



