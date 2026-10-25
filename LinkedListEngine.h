#ifndef LINKED_LIST_ENGINE_H
#define LINKED_LIST_ENGINE_H

#include "EntityModel.h"

struct ListNode {
    StudentRecord data;
    ListNode* prev;
    ListNode* next;
    ListNode(StudentRecord val) : data(val), prev(nullptr), next(nullptr) {}
};

class LinkedListEngine {
private:
    ListNode* head;
    ListNode* tail;
    int count;

public:
    LinkedListEngine();
    ~LinkedListEngine();

    void insertHead(StudentRecord record);
    void insertTail(StudentRecord record);
    void insertSorted(StudentRecord record);
    bool deleteRecord(int studentId);
    ListNode* searchRecord(int studentId);
    bool updateRecord(int studentId, std::string newService, double newGpa);
    void displayForward() const;
    void displayBackward() const;
    int getCount() const;

    StudentRecord* toArray(int& outSize) const;
};

#endif
