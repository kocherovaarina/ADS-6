// Copyright 2021 NNTU-CS

#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

template<typename T>
class TPQueue {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;

public:
    TPQueue() : head(nullptr) {}

    ~TPQueue() {
        while (head) {
            pop();
        }
    }

    void push(const T& value) {
        Node* newNode = new Node(value);
        if (!head || head->data.prior < value.prior) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next && current->next->data.prior >= value.prior) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    T pop() {
        if (!head) {
            throw std::runtime_error("Queue is empty");
        }
        Node* temp = head;
        T returnValue = head->data;
        head = head->next;
        delete temp;
        return returnValue;
    }

    bool isEmpty() const {
        return head == nullptr;
    }
};

struct SYM {
    char ch;
    int prior;
};

#endif

