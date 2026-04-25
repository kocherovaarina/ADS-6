// Copyright 2021 NNTU-CS

#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>
#include <utility>
#include <functional>

struct SYM {
    char ch;
    int prior;

    
    bool operator<(const SYM& other) const {
        return prior < other.prior;
    }
};

struct SYMPriorityComparator {
    bool operator()(const SYM& a, const SYM& b) const {
        return a.prior < b.prior;
    }
};

template<typename T, typename Comparator = std::less<T>>
class TPQueue {
private:
    struct Node {
        T data;
        Node* next;

        explicit Node(const T& value)
            : data(value), next(nullptr) {}
        explicit Node(T&& value)
            : data(std::move(value)), next(nullptr) {}
    };

    Node* head;
    Comparator comp;

public:
    explicit TPQueue(Comparator c = Comparator())
        : head(nullptr), comp(c) {}

    ~TPQueue() {
        while (head) {
            pop();
        }
    }

    TPQueue(const TPQueue& other)
        : head(nullptr), comp(other.comp) {
        Node* current = other.head;
        while (current) {
            push(current->data);
            current = current->next;
        }
    }

    TPQueue& operator=(const TPQueue& other) {
        if (this != &other) {
            TPQueue temp(other);
            std::swap(head, temp.head);
        }
        return *this;
    }

    TPQueue(TPQueue&& other) noexcept
        : head(other.head), comp(std::move(other.comp)) {
        other.head = nullptr;
    }

    TPQueue& operator=(TPQueue&& other) noexcept {
        std::swap(head, other.head);
        comp = std::move(other.comp);
        return *this;
    }

    void push(const T& value) {
        pushImpl(value);
    }

    void push(T&& value) {
        pushImpl(std::move(value));
    }

    T pop() {
        if (!head) {
            throw std::runtime_error("Queue is empty");
        }
        Node* temp = head;
        T returnValue = std::move(head->data);
        head = head->next;
        delete temp;
        return returnValue;
    }

    const T& front() const {
        if (!head) {
            throw std::runtime_error("Queue is empty");
        }
        return head->data;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

private:
    template<typename U>
    void pushImpl(U&& value) {
        Node* newNode = new Node(std::forward<U>(value));
        if (!head || comp(head->data, newNode->data)) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next &&
                   !comp(newNode->data, current->next->data)) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }
};

#endif  // INCLUDE_TPQUEUE_H_
