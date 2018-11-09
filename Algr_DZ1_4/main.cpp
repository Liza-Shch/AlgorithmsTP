#include <iostream>
#include <cassert>

struct Item {
    Item() : value(0), position(0) {};
    Item(int value, int position) : value(value), position(position) {};
    int value;
    int position;
};

class Heap {
public:
    Heap(int bufferSize);
    ~Heap();
    Heap(const Heap &object);
    Heap(Heap &&object);
    Heap &operator=(const Heap &object);
    Heap &operator=(Heap &&object);
    void Create(const int *array, int size);
    void Add(Item item);
    void DeleteMax();
    Item GetMax();
private:
    Item *buffer;
    int bufferSize;
    int currentSize;
    void siftDown(int item_position);
    void siftUp(int itemPosition);
};

void Heap::siftDown(int item_position) {
    int left = 2 * item_position + 1;
    int right = left + 1;
    int largest = item_position;
    if (left < currentSize && buffer[left].value > buffer[largest].value) {
        largest = left;
    }
    if (right < currentSize && buffer[right].value > buffer[largest].value) {
        largest = right;
    }
    if (largest != item_position) {
        std::swap(buffer[largest], buffer[item_position]);
        siftDown(largest);
    }
}

void Heap::siftUp(int itemPosition) {
    while (itemPosition > 0) {
        int parent = (itemPosition - 1) / 2;
        if (buffer[itemPosition].value <= buffer[parent].value) {
            return;
        }
        std::swap(buffer[itemPosition], buffer[parent]);
        itemPosition = parent;
    }
}

Heap::Heap(int bufferSize) : bufferSize(bufferSize), currentSize(0) {
    buffer = new Item[bufferSize];
}

Heap::~Heap() {
    delete[] buffer;
}

Heap::Heap(const Heap &object): bufferSize(object.bufferSize), currentSize(object.currentSize) {
    buffer = new Item[currentSize];
    for (int i = 0; i < currentSize; i++) {
        buffer[i] = object.buffer[i];
    }
}

Heap::Heap(Heap &&object): bufferSize(object.bufferSize), currentSize(object.currentSize) {
    buffer = object.buffer;
    object.buffer = nullptr;
    object.bufferSize = 0;
    object.currentSize = 0;
}

Heap& Heap::operator=(const Heap &object) {
    if (this != &object) {
        bufferSize = object.bufferSize;
        currentSize = object.currentSize;
        delete[] buffer;
        buffer = new Item[bufferSize];
        for (int i = 0; i < bufferSize; i++) {
            buffer[i] = object.buffer[i];
        }
    }
    return *this;
}

Heap& Heap::operator=(Heap &&object) {
    if (this != &object) {
        bufferSize = object.bufferSize;
        currentSize = object.currentSize;
        delete[] buffer;
        buffer = object.buffer;
        object.buffer = nullptr;
        object.bufferSize = 0;
        object.currentSize = 0;
    }
    return *this;
}

void Heap::Create(const int *array, int size) {
    currentSize = size;
    for (int i = 0; i < size; i++) {
        buffer[i].value = array[i];
        buffer[i].position = i;
    }
    for (int i = (size - 1) / 2; i >= 0; i--) {
        siftDown(i);
    }
}

void Heap::Add(Item item) {
    buffer[currentSize] = item;
    currentSize++;
    siftUp(currentSize - 1);
}

void Heap::DeleteMax() {
    assert(currentSize > 0);
    buffer[0] = buffer[currentSize - 1];
    currentSize--;
    if (currentSize > 0) {
        siftDown(0);
    }
}

Item Heap::GetMax() {
    assert(currentSize > 0);
    return buffer[0];
}

void searchMaxInWindowsOfArray(const int *array, int arraySize, int windowSize) {
    assert(array && arraySize > 0);
    Heap heap(arraySize);
    heap.Create(array, windowSize);
    std::cout << heap.GetMax().value << ' ';
    int windowLeft = 1;
    int windowRight = windowLeft + windowSize - 1;
    for (; windowRight < arraySize; windowRight++, windowLeft++) {
        heap.Add(Item(array[windowRight], windowRight));
        while (heap.GetMax().position < windowLeft) {
            heap.DeleteMax();
        }
        std::cout << heap.GetMax().value << ' ';
    }
}

int main() {
    int array_count = 0;
    std::cin >> array_count;
    auto *array = new int[array_count];
    for (int i = 0; i < array_count; i++) {
        std::cin >> array[i];
    }
    int window_size = 0;
    std::cin >> window_size;
    searchMaxInWindowsOfArray(array, array_count, window_size);
    delete[] array;
    return 0;
}