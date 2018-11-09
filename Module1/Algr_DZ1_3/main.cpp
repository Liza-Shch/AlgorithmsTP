#include <iostream>
#include <cassert>

#define PUSH 3
#define POP 2

class Queue {
public:
    explicit Queue(): buffer(nullptr), bufferSize(defaultBufferSize), head(0), tail(0) {
        buffer = new int[bufferSize];
    };
    ~Queue();
    Queue(const Queue &object);
    Queue(Queue &&object);
    Queue &operator=(const Queue &object);
    Queue &operator=(Queue &&object);

    bool IsEmpty();
    void Enqueue(int item);
    int Dequeue();
private:
    int *buffer;
    const size_t defaultBufferSize = 2;
    size_t bufferSize;
    size_t head;
    size_t tail;
    void grow();
};

Queue::~Queue() {
    delete[] buffer;
}

Queue::Queue(const Queue &object): bufferSize(object.bufferSize), head(object.head), tail(object.tail) {
    buffer = new int[bufferSize];
    for (size_t i = 0; i < bufferSize; i++) {
        buffer[i] = object.buffer[i];
    }
}

Queue::Queue(Queue &&object): bufferSize(object.bufferSize), head(object.head), tail(object.tail) {
    buffer = object.buffer;
    object.buffer = nullptr;
    object.bufferSize = 0;
    object.head = 0;
    object.tail = 0;
}

Queue& Queue::operator=(const Queue &object) {
    if (this != &object) {
        bufferSize = object.bufferSize;
        head = object.head;
        tail = object.tail;
        delete[] buffer;
        buffer = new int[bufferSize];
        for (int i = 0; i < bufferSize; i++) {
            buffer[i] = object.buffer[i];
        }
    }
    return *this;
}

Queue& Queue::operator=(Queue &&object) {
    if (this != &object) {
        bufferSize = object.bufferSize;
        head = object.head;
        tail = object.tail;
        delete[] buffer;
        buffer = object.buffer;
        object.buffer = nullptr;
        object.bufferSize = 0;
        object.head = 0;
        object.tail = 0;
    }
    return *this;
}

void Queue::grow() {
    size_t newBufferSize = bufferSize * 2;
    auto *newBuffer = new int[newBufferSize];
    size_t newTail =  0;
    while (head != tail) {
        newBuffer[newTail] = buffer[head];
        head = (head + 1) % bufferSize;
        newTail++;
    }
    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newBufferSize;
    head = 0;
    tail = newTail;
}

bool Queue::IsEmpty() {
    return head == tail;
}

void Queue::Enqueue(int item) {
    if ((tail + 1) % bufferSize == head) {
        grow();
    }
    buffer[tail] = item;
    tail = (tail + 1) % bufferSize;
}

int Queue::Dequeue() {
    assert(!IsEmpty());
    int result = buffer[head];
    head = (head + 1) % bufferSize;
    return result;
}

bool useQueue(size_t commandCount) {
    Queue queue;
    for (size_t i = 0; i < commandCount; i++) {
        int command_id = 0;
        int item = 0;
        std::cin >> command_id >> item;
        switch (command_id) {
            case PUSH: {
                queue.Enqueue(item);
                break;
            }
            case POP: {
                if (queue.IsEmpty()) {
                    if (item != -1) {
                        return false;
                    }
                    break;
                }
                int result = queue.Dequeue();
                if (result != item) {
                    return false;
                }
                break;
            }
            default: {
                return false;
            }
        }
    }
    return true;
}

int main() {
    size_t commandCount = 0;
    std::cin >> commandCount;
    bool correct = useQueue(commandCount);
    if (correct) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
    return 0;
}