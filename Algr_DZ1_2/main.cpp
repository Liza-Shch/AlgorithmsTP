#include <iostream>

void find_scope(int item, const int *array, int size, int &left, int &right) {
    while (array[right] < item) {
        left = right;
        right *= 2;
        if (right >= size) {
            right = size;
            break;
        }
    }
}

int find_insertion_point(int item, const int *sort_array, int left, int right) {
    while (left < right) {
        int middle = (left + right) / 2;
        if (sort_array[middle] < item) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    return left;
}

int twin_search(int item, const int *sort_array, int sort_array_size) {
    if (sort_array_size == 1) {
        return 0;
    }
    int left = 0;
    int right = 1;
    find_scope(item, sort_array, sort_array_size, left, right);
    left = find_insertion_point(item, sort_array, left, right);
    if (left == 0) {
        return 0;
    }
    if (left == sort_array_size) {
        left--;
        while (left > 0 && sort_array[left - 1] == sort_array[left]) {
            left--;
        }
        return left;
    }
    if (item - sort_array[left - 1] <= sort_array[left] - item) {
        left--;
    }
    while (left > 0 && sort_array[left - 1] == sort_array[left]) {
        left--;
    }
    return left;
}

int main() {
    int sort_array_size = 0;
    std::cin >> sort_array_size;
    auto *sort_array = new int[sort_array_size];
    for (int i = 0; i < sort_array_size; i++) {
        std::cin >> sort_array[i];
    }
    int array_size = 0;
    std::cin >> array_size;
    auto *array = new int[array_size];
    for (int i = 0; i < array_size; i++) {
        std::cin >> array[i];
    }
    for (int i = 0; i < array_size; i++) {
        std::cout << twin_search(array[i], sort_array, sort_array_size) << ' ';
    }
    delete[] sort_array;
    delete[] array;
    return 0;
}