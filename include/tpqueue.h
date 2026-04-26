// Copyright 2022 NNTU-CS
#ifndef TPQUEUE_H
#define TPQUEUE_H

template<typename T>
class TPQueue {
 private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

 public:
    TPQueue() : head(nullptr), tail(nullptr), size(0) {}

    ~TPQueue() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(const T& item) {
        Node* newNode = new Node(item);
        if (isEmpty() || item.prior > head->data.prior) {
            newNode->next = head;
            head = newNode;
            if (tail == nullptr) {
                tail = head;
            }
        } else {
            Node* current = head;
            while (current->next != nullptr &&
                   current->next->data.prior >= item.prior) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;

          
            if (newNode->next == nullptr) {
                tail = newNode;
            }
        }
        size++;
    }

    T pop() {
        if (isEmpty()) {
            throw "Queue is empty";
        }

        Node* temp = head;
        T result = head->data;
        head = head->next;
      
        if (head == nullptr) {
            tail = nullptr;
        }

        delete temp;
        size--;
        return result;
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    int getSize() const {
        return size;
    }
};

#endif
