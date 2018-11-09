#include <iostream>
#include <cstring>
#include <cassert>

#define MAX_STRING_LENGTH_ 256
#define CAPACITY_ 256

char **input(int &strings_count) {
    char **strings = NULL;
    auto *buffer = new char[MAX_STRING_LENGTH_];
    while (std::cin.good()) {
        std::cin.getline(buffer, MAX_STRING_LENGTH_, '\n');
        if (strlen(buffer) == 0) {
            break;
        }
        strings_count++;
        char **strings_memory_error = strings;
        strings = (char **)realloc(strings_memory_error, sizeof(char *) * strings_count);
        size_t buffer_len = strlen(buffer);
        strings[strings_count - 1] = new char[MAX_STRING_LENGTH_];
        memmove(strings[strings_count - 1], buffer, sizeof(char) * buffer_len + 1);
    }
    delete[] buffer;
    return strings;
}

int getKey(char symbol) {
    return (int) symbol;
};

void countSort(char **strings, int count, int radix, int *bins) {
    for (int i = 0; i < count; i++) {
        bins[getKey(strings[i][radix])]++;
    }
    int start = 0;
    for (int i = 0; i < CAPACITY_; i++) {
        int symbol_count = bins[i];
        bins[i] = start;
        start += symbol_count;
    }
    auto sortStrings = new char*[count];
    auto buffer = new char*[count];
    for (int i = 0; i < count; i++) {
        buffer[i] = new char[strlen(strings[i]) + 1];
        memcpy(buffer[i], strings[i], strlen(strings[i]) * sizeof(char) + 1);
    }
    for (int i = 0; i < count; i++) {
        int pastPos = bins[getKey(strings[i][radix])];
        sortStrings[pastPos] = buffer[i];
        bins[getKey(strings[i][radix])]++;
    }
    for (int i = 0; i < count; i++) {
        memcpy(strings[i], sortStrings[i], strlen(sortStrings[i]) * sizeof(char) + 1);
    }

    delete[] sortStrings;
    for (int i = 0; i < count; i++) {
        delete[] buffer[i];
    }
    delete[] buffer;
}

void msd_sort(char **strings, int count, int radix = 0) {
    auto bins = (int*) calloc(CAPACITY_ + 1, sizeof(int));
    bins[CAPACITY_] = count;
    countSort(strings, count, radix, bins);
    for (int i = 0; i < CAPACITY_; i++) {
        int binSize = bins[i + 1] - bins[i];
        if (binSize > 1) {
            msd_sort(strings + bins[i], binSize, radix + 1);
        }
    }
    free(bins);
}

int main() {
    int strings_count = 0;
    char **strings = input(strings_count);
    assert(strings);
    msd_sort(strings, strings_count);
    for (int i = 0; i < strings_count; i++) {
        for (int j = 0; j < strlen(strings[i]); j++) {
            std::cout << strings[i][j];
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < strings_count; i++) {
        delete[] strings[i];
    }
    free(strings);
    return 0;
}