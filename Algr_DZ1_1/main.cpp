#include <iostream>

struct List {
    List(size_t number, List *next):number(number), next(next){};
    size_t number;
    struct List *next;
};

List *add_item(List *current, size_t number) {
    auto *item = new List(number, nullptr);
    current->next = item;
    return item;
}

List *create_list(int count) {
    size_t iterator = 1;
    auto *first = new List(iterator, nullptr);
    struct List *item = first;
    iterator++;
    for (; iterator <= count; iterator++) {
        item = add_item(item, iterator);
    }
    item->next = first;
    return first;
}

List *delete_item(List *previous_item) {
    struct List *current = previous_item->next;
    previous_item->next = previous_item->next->next;
    delete (current);
    return previous_item->next;
}

size_t survivor(int count, int except_count) {
    except_count -= 2;
    struct List *list = create_list(count);
    while (list->next != list) {
        for (int i = 0; i < except_count; i++) {
            list = list->next;
        }
        list = delete_item(list);
    }
    size_t number = list->number;
    delete (list);
    return number;
}

int main() {
    int count = 0;
    int except_count = 0;
    std::cin >> count >> except_count;
    size_t number = survivor(count, except_count);
    std::cout << number;
    return 0;
}