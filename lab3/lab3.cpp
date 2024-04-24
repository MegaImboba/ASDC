#include <cassert>
#include <iostream>

// Определение узла односвязного списка
template<typename T>
struct Node {
    T value;
    Node<T>* next = nullptr;
};

// Определение односвязного списка
template<typename T>
struct LinkedList {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    int size = 0;
};

// Результат поиска
template<typename T>
struct FindNodeResult {
    Node<T>* foundNode = nullptr;
    Node<T>* previousNode = nullptr;
};

// Вставка элемента после заданного узла
template<typename T>
Node<T>* insertAfter(LinkedList<T>& list, Node<T>* node, T value) {
    Node<T>* newNode = new Node<T>{value, nullptr};
    if (node == nullptr) { // Вставка в начало списка
        newNode->next = list.head;
        list.head = newNode;
        if (list.size == 0)
            list.tail = newNode;
    } else { // Вставка после существующего узла
        newNode->next = node->next;
        node->next = newNode;
        if (node == list.tail)
            list.tail = newNode;
    }
    list.size++;
    return newNode;
}

// Поиск узла с заданным значением
template<typename T>
FindNodeResult<T> find(LinkedList<T>& list, T value) {
    Node<T>* current = list.head;
    Node<T>* previous = nullptr;
    while (current != nullptr) {
        if (current->value == value) {
            return {current, previous};
        }
        previous = current;
        current = current->next;
    }
    return {nullptr, nullptr};
}

// Удаление узла после заданного узла
template<typename T>
void removeAfter(LinkedList<T>& list, Node<T>* node) {
    if (node == nullptr && list.head) { // Удалить первый узел
        Node<T>* toDelete = list.head;
        list.head = list.head->next;
        if (list.tail == toDelete)
            list.tail = nullptr;
        delete toDelete;
    } else if (node && node->next) { // Удалить узел после node
        Node<T>* toDelete = node->next;
        node->next = toDelete->next;
        if (list.tail == toDelete)
            list.tail = node;
        delete toDelete;
    }
    list.size--;
}

// Проверка на наличие циклов в списке
template<typename T>
void assertNoCycles(LinkedList<T>& list) {
    Node<T>* slow = list.head;
    Node<T>* fast = list.head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
        assert(slow != fast && "Cycle detected in LinkedList!");
    }
}

int main() {
    LinkedList<int> myList;

    // Тестирование добавления элементов
    Node<int>* first = insertAfter(myList, static_cast<Node<int>*>(nullptr), 10); // Добавить в начало
    insertAfter(myList, first, 20); // Добавить после первого узла
    insertAfter(myList, static_cast<Node<int>*>(nullptr), 5); // Добавить в начало

    // Тестирование поиска
    FindNodeResult<int> result = find(myList, 20);
    std::cout << "Found: " << (result.foundNode ? result.foundNode->value : -1) << std::endl;

    // Тестирование удаления
    removeAfter(myList, first); // Удалить узел после первого узла
    removeAfter(myList, static_cast<Node<int>*>(nullptr)); // Удалить первый узел

    // Проверка на отсутствие циклов
    assertNoCycles(myList);

    return 0;
}

