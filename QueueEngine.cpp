#include "QueueEngine.h"
#include <iostream>

StandardQueue::StandardQueue() : frontNode(nullptr), rearNode(nullptr), count(0) {}

StandardQueue::~StandardQueue() {
    StudentRecord dummy;
    while (dequeue(dummy));
}

void StandardQueue::enqueue(StudentRecord record) {
    QueueNode* newNode = new QueueNode(record);
    if (!rearNode) {
        frontNode = rearNode = newNode;
    } else {
        rearNode->next = newNode;
        rearNode = newNode;
    }
    count++;
}

bool StandardQueue::dequeue(StudentRecord& outRecord) {
    if (isEmpty()) return false;
    QueueNode* temp = frontNode;
    outRecord = temp->data;
    frontNode = frontNode->next;
    if (!frontNode) rearNode = nullptr;
    delete temp;
    count--;
    return true;
}

bool StandardQueue::peek(StudentRecord& outRecord) const {
    if (isEmpty()) return false;
    outRecord = frontNode->data;
    return true;
}

void StandardQueue::displayQueue() const {
    if (isEmpty()) {
        std::cout << "[Queue] Standard service line is empty.\n";
        return;
    }
    std::cout << "\n============================= STANDARD FIFO SERVICE QUEUE =============================\n";
    QueueNode* current = frontNode;
    int pos = 1;
    while (current) {
        std::cout << "Pos " << pos++ << ": ID " << current->data.studentId
                  << " | " << current->data.fullName
                  << " | Request: " << current->data.serviceType << "\n";
        current = current->next;
    }
    std::cout << "=======================================================================================\n";
}

bool StandardQueue::isEmpty() const { return frontNode == nullptr; }
int StandardQueue::getCount() const { return count; }


PriorityQueueEngine::PriorityQueueEngine() : head(nullptr), count(0) {}

PriorityQueueEngine::~PriorityQueueEngine() {
    StudentRecord dummy;
    while (dequeue(dummy));
}

void PriorityQueueEngine::priorityEnqueue(StudentRecord record) {
    QueueNode* newNode = new QueueNode(record);
    if (!head || static_cast<int>(record.priorityStatus) > static_cast<int>(head->data.priorityStatus)) {
        newNode->next = head;
        head = newNode;
    } else {
        QueueNode* current = head;
        while (current->next && static_cast<int>(current->next->data.priorityStatus) >= static_cast<int>(record.priorityStatus)) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    count++;
}

bool PriorityQueueEngine::dequeue(StudentRecord& outRecord) {
    if (isEmpty()) return false;
    QueueNode* temp = head;
    outRecord = temp->data;
    head = head->next;
    delete temp;
    count--;
    return true;
}

bool PriorityQueueEngine::peek(StudentRecord& outRecord) const {
    if (isEmpty()) return false;
    outRecord = head->data;
    return true;
}

void PriorityQueueEngine::displayQueue() const {
    if (isEmpty()) {
        std::cout << "[Priority Queue] Priority express line is empty.\n";
        return;
    }
    std::cout << "\n========================= PRIORITY EXPRESS TRIAGE QUEUE =========================\n";
    QueueNode* current = head;
    int pos = 1;
    while (current) {
        std::cout << "Priority Pos " << pos++ << ": ID " << current->data.studentId
                  << " | " << current->data.fullName
                  << " | Tier: " << priorityTierToString(current->data.priorityStatus) << "\n";
        current = current->next;
    }
    std::cout << "=================================================================================\n";
}

bool PriorityQueueEngine::isEmpty() const { return head == nullptr; }
int PriorityQueueEngine::getCount() const { return count; }
