#include "LinkedListEngine.h"
#include <iostream>

LinkedListEngine::LinkedListEngine() : head(nullptr), tail(nullptr), count(0) {}

LinkedListEngine::~LinkedListEngine() {
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
}

void LinkedListEngine::insertHead(StudentRecord record) {
    ListNode* newNode = new ListNode(record);
    if (!head) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    count++;
}

void LinkedListEngine::insertTail(StudentRecord record) {
    ListNode* newNode = new ListNode(record);
    if (!tail) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    count++;
}

void LinkedListEngine::insertSorted(StudentRecord record) {
    if (!head || head->data.studentId >= record.studentId) {
        insertHead(record);
        return;
    }
    if (tail->data.studentId <= record.studentId) {
        insertTail(record);
        return;
    }
    ListNode* current = head;
    while (current->next && current->next->data.studentId < record.studentId) {
        current = current->next;
    }
    ListNode* newNode = new ListNode(record);
    newNode->next = current->next;
    newNode->prev = current;
    current->next->prev = newNode;
    current->next = newNode;
    count++;
}

bool LinkedListEngine::deleteRecord(int studentId) {
    ListNode* target = searchRecord(studentId);
    if (!target) return false;

    if (target == head && target == tail) {
        head = tail = nullptr;
    } else if (target == head) {
        head = head->next;
        head->prev = nullptr;
    } else if (target == tail) {
        tail = tail->prev;
        tail->next = nullptr;
    } else {
        target->prev->next = target->next;
        target->next->prev = target->prev;
    }

    delete target;
    count--;
    return true;
}

ListNode* LinkedListEngine::searchRecord(int studentId) {
    ListNode* current = head;
    while (current) {
        if (current->data.studentId == studentId) return current;
        current = current->next;
    }
    return nullptr;
}

bool LinkedListEngine::updateRecord(int studentId, std::string newService, double newGpa) {
    ListNode* target = searchRecord(studentId);
    if (!target) return false;
    target->data.serviceType = newService;
    target->data.gpa = newGpa;
    return true;
}

void LinkedListEngine::displayForward() const {
    if (!head) {
        std::cout << "[Registry] Master record list is empty.\n";
        return;
    }
    std::cout << "\n================================ MASTER REGISTRY (FORWARD) ================================\n";
    std::cout << "ID\tFull Name\t\tService Type\t\tPriority Status\tGPA\tTimestamp\n";
    std::cout << "-------------------------------------------------------------------------------------------\n";
    ListNode* current = head;
    while (current) {
        std::cout << current->data.studentId << "\t"
                  << current->data.fullName << "\t\t"
                  << current->data.serviceType << "\t"
                  << priorityTierToString(current->data.priorityStatus) << "\t"
                  << current->data.gpa << "\t"
                  << current->data.timestamp << "\n";
        current = current->next;
    }
    std::cout << "===========================================================================================\n";
}

void LinkedListEngine::displayBackward() const {
    if (!tail) {
        std::cout << "[Registry] Master record list is empty.\n";
        return;
    }
    std::cout << "\n=============================== MASTER REGISTRY (BACKWARD) ================================\n";
    std::cout << "ID\tFull Name\t\tService Type\t\tPriority Status\tGPA\tTimestamp\n";
    std::cout << "-------------------------------------------------------------------------------------------\n";
    ListNode* current = tail;
    while (current) {
        std::cout << current->data.studentId << "\t"
                  << current->data.fullName << "\t\t"
                  << current->data.serviceType << "\t"
                  << priorityTierToString(current->data.priorityStatus) << "\t"
                  << current->data.gpa << "\t"
                  << current->data.timestamp << "\n";
        current = current->prev;
    }
    std::cout << "===========================================================================================\n";
}

int LinkedListEngine::getCount() const { return count; }

StudentRecord* LinkedListEngine::toArray(int& outSize) const {
    outSize = count;
    if (outSize == 0) return nullptr;
    StudentRecord* arr = new StudentRecord[outSize];
    ListNode* current = head;
    int i = 0;
    while (current && i < outSize) {
        arr[i++] = current->data;
        current = current->next;
    }
    return arr;
}
