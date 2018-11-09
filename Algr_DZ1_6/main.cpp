#include <iostream>
#include <cassert>

int partition(int *buffer, int size, int pivot_pos) {
    if (size <= 1) {
        return 0;
    }
    std::swap(buffer[pivot_pos], buffer[size - 1]);
    pivot_pos = size - 1;
    int i = 0;
    int j = size - 2;
    while (i <= j) {
        while (buffer[i] < buffer[pivot_pos]) {
            i++;
        }
        while (j >=0 && buffer[j] >= buffer[pivot_pos]) {
            j--;
        }
        if (i < j) {
            std::swap(buffer[i++], buffer[j--]);
        }
    }
    std::swap(buffer[pivot_pos], buffer[i]);
    return i;
}

int k_statistic(int *buffer, int size, int k) {
    int pivot_pos = rand() % size;
    int pivot = buffer[pivot_pos];
    pivot_pos = partition(buffer, size, pivot_pos);
    if (pivot_pos == k) {
        return pivot;
    }
    if (pivot_pos > k) {
        return k_statistic(buffer, pivot_pos, k);
    }
    if (pivot_pos < k) {
        return k_statistic(buffer + pivot_pos + 1, size - (pivot_pos + 1), k - (pivot_pos + 1));
    }
}

int main() {
    int size = 0;
    int k = 0;
    std::cin >> size >> k;
    auto *buffer = new int[size];
    for (int i = 0; i < size; i++) {
        std::cin >> buffer[i];
    }
    srand(time(0));
    int number_on_k_position = k_statistic(buffer, size, k);
    std::cout << number_on_k_position;
    return 0;
}