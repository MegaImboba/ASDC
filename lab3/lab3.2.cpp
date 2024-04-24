#include <iostream>
#include <stdexcept>
#include <cassert> // Include for assert function

// Definition of the list node structure
struct Node {
    int value;
    Node* prev;
    Node* next;

    Node(int v) : value(v), prev(nullptr), next(nullptr) {}
};

// Definition of the doubly linked list structure
struct LinkedList {
    Node* head;
    Node* tail;

    LinkedList() : head(nullptr), tail(nullptr) {}
};

// Functions for managing the list
Node* insertAfter(LinkedList* list, Node* node, int value) {
    Node* newNode = new Node(value);
    if (!node) {
        if (!list->head) {
            list->head = list->tail = newNode;
        } else {
            newNode->next = list->head;
            list->head->prev = newNode;
            list->head = newNode;
        }
    } else {
        newNode->next = node->next;
        newNode->prev = node;
        if (node->next) {
            node->next->prev = newNode;
        } else {
            list->tail = newNode;
        }
        node->next = newNode;
    }
    return newNode;
}

Node* insertBefore(LinkedList* list, Node* node, int value) {
    Node* newNode = new Node(value);
    if (!node) {
        if (!list->head) {
            list->head = list->tail = newNode;
        } else {
            newNode->next = list->head;
            list->head->prev = newNode;
            list->head = newNode;
        }
    } else {
        newNode->prev = node->prev;
        newNode->next = node;
        if (node->prev) {
            node->prev->next = newNode;
        } else {
            list->head = newNode;
        }
        node->prev = newNode;
    }
    return newNode;
}

Node* find(LinkedList* list, int value) {
    Node* current = list->head;
    while (current) {
        if (current->value == value) return current;
        current = current->next;
    }
    return nullptr;
}

void remove(LinkedList* list, Node* node) {
    if (!node) return;

    if (node->prev) {
        node->prev->next = node->next;
    } else {
        list->head = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    } else {
        list->tail = node->prev;
    }

    delete node;
}

void assertNoCycles(LinkedList* list) {
    Node* slow = list->head;
    Node* fast = list->head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            throw std::runtime_error("Cycle detected in the list!");
        } 
    }
}


// Main function
int main() {
        LinkedList list;
    Node* n1 = insertAfter(&list, nullptr, 10);
    Node* n2 = insertAfter(&list, n1, 20);
    Node* n3 = insertBefore(&list, n1, 5);

    assert(find(&list, 10) == n1);
    assert(find(&list, 20) == n2);
    assert(find(&list, 5) == n3);

    remove(&list, n1);
    assert(find(&list, 10) == nullptr);

    try {
        assertNoCycles(&list);
        std::cout << "No cycles detected." << std::endl;
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
