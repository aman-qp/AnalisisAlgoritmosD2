#ifndef LINKEDLIST_H
#define LINKEDLIST_H

class Node {
public:
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
public:
    LinkedList();
    ~LinkedList();
    bool search(int data);  // Solo implementamos búsqueda
    void insert(int data);
};

#endif
