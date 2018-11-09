#include <iostream>
#include <cstring>
#include <cassert>

struct TimeTable {
    TimeTable() : timeCome(0), timeGone(0) {};
    int timeCome;
    int timeGone;
};

void merge(TimeTable *firstBuffer, int firstSize, TimeTable *secondBuffer, int secondSize, TimeTable *result) {
    int first_array_iterator = 0;
    int second_array_iterator = 0;
    while (first_array_iterator < firstSize && second_array_iterator < secondSize) {
        if (firstBuffer[first_array_iterator].timeGone < secondBuffer[second_array_iterator].timeGone) {
            *result = firstBuffer[first_array_iterator];
            first_array_iterator++;
        } else {
            *result = secondBuffer[second_array_iterator];
            second_array_iterator++;
        }
        result++;
    }
    while (first_array_iterator < firstSize) {
        *result = firstBuffer[first_array_iterator];
        first_array_iterator++;
        result++;
    }
    while (second_array_iterator < secondSize) {
        *result = secondBuffer[second_array_iterator];
        second_array_iterator++;
        result++;
    }
}

void mergeSort(TimeTable *timeTable, int size) {
    if (size <= 1) {
        return;
    }
    int firstSize = size / 2;
    int secondSize = size - firstSize;
    mergeSort(timeTable, firstSize);
    mergeSort(timeTable + firstSize, secondSize);
    auto *result = new TimeTable[size];
    merge(timeTable, firstSize, timeTable + firstSize, secondSize, result);
    memcpy(timeTable, result, sizeof(TimeTable) * size);
    delete[] result;
}

int countAds(TimeTable *timeTable, int size) {
    assert(timeTable && size > 0);
    int adsCount = 2;
    int timeOfSecondAd = timeTable[0].timeGone;
    int timeOfFirstAd = timeOfSecondAd - 1;
    for (int i = 1; i < size; i++) {
        if (timeTable[i].timeCome > timeOfSecondAd) {
            timeOfSecondAd = timeTable[i].timeGone;
            timeOfFirstAd = timeOfSecondAd - 1;
            adsCount += 2;
        } else {
            if (timeTable[i].timeCome == timeOfSecondAd) {
                timeOfFirstAd = timeOfSecondAd;
                timeOfSecondAd = timeTable[i].timeGone;
                adsCount++;
            } else {
                if (timeTable[i].timeCome > timeOfFirstAd) {
                    timeOfFirstAd = timeOfSecondAd;
                    timeOfSecondAd = timeTable[i].timeGone;
                    adsCount++;
                }
            }
        }
    }
    return adsCount;
}

int main() {
    int buyersCount = 0;
    std::cin >> buyersCount;
    auto *timeTable = new TimeTable[buyersCount];
    for (int i = 0; i < buyersCount; i++) {
        std::cin >> timeTable[i].timeCome >> timeTable[i].timeGone;
    }
    mergeSort(timeTable, buyersCount);
    int adsCount = countAds(timeTable, buyersCount);
    std::cout << adsCount;
    delete[] timeTable;
    return 0;
}