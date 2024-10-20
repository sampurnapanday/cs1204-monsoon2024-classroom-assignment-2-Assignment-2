#include <vector>
#include <cmath>
#include <iostream>

class CustomHashMap {
private:
    std::vector<int> slots;
    int capacity;
    int filledSlots;
    double maxLoadFactor;

    int computeHash(int key) {
        return key % capacity;
    }

    int findNextPrime(int num) {
        while (true) {
            bool prime = true;
            for (int i = 2; i <= std::sqrt(num); i++) {
                if (num % i == 0) {
                    prime = false;
                    break;
                }
            }
            if (prime) return num;
            num++;
        }
    }

    void expandAndRehash() {
        int newCapacity = findNextPrime(capacity * 2);
        std::vector<int> newSlots(newCapacity, -1);

        for (int i = 0; i < capacity; i++) {
            if (slots[i] != -1 && slots[i] != -2) {
                int key = slots[i];
                int index = key % newCapacity;
                int step = 0;
                while (newSlots[(index + step * step) % newCapacity] != -1) {
                    step++;
                }
                newSlots[(index + step * step) % newCapacity] = key;
            }
        }

        slots = newSlots;
        capacity = newCapacity;
    }

public:
    CustomHashMap(int initialCapacity = 7) {  // Start with 7 as per test case
        capacity = findNextPrime(initialCapacity);
        slots = std::vector<int>(capacity, -1);
        filledSlots = 0;
        maxLoadFactor = 0.8;
    }

    void insert(int key) {
        if (filledSlots >= maxLoadFactor * capacity) {
            expandAndRehash();
        }

        int index = computeHash(key);
        int step = 0;

        while (step < capacity) {
            int probedIndex = (index + (step * step)) % capacity;
            if (slots[probedIndex] == key) {
                std::cout << "Duplicate key insertion is not allowed\n";
                return;
            }
            if (slots[probedIndex] == -1 || slots[probedIndex] == -2) {
                slots[probedIndex] = key;
                filledSlots++;
                return;
            }
            step++;
        }

        std::cout << "Max probing limit reached!\n";
    }

    void remove(int key) {
        int index = computeHash(key);
        int step = 0;

        while (step < capacity) {
            int probedIndex = (index + (step * step)) % capacity;
            if (slots[probedIndex] == key) {
                slots[probedIndex] = -2;  // -2 means deleted
                filledSlots--;
                return;
            } else if (slots[probedIndex] == -1) {
                std::cout << "Element not found\n";
                return;
            }
            step++;
        }

        std::cout << "Element not found\n";
    }

    int search(int key) {
        int index = computeHash(key);
        int step = 0;

        while (step < capacity) {
            int probedIndex = (index + (step * step)) % capacity;
            if (slots[probedIndex] == key) {
                return probedIndex;
            } else if (slots[probedIndex] == -1) {
                return -1;
            }
            step++;
        }
        return -1;
    }

    void printTable() {
        for (int i = 0; i < capacity; i++) {
            if (slots[i] == -1 || slots[i] == -2) {
                std::cout << "- ";
            } else {
                std::cout << slots[i] << " ";
            }
        }
        std::cout << "\n";
    }
};



