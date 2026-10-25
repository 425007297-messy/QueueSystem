#include "StackEngine.h"
#include <iostream>

StackEngine::StackEngine() : top(nullptr), size(0) {}

StackEngine::~StackEngine() {
    while (!isEmpty()) {
        std::string d;
        StudentRecord r;
        pop(d, r);
    }
}

void StackEngine::push(std::string actionDesc, StudentRecord record) {
    StackNode* newNode = new StackNode(actionDesc, record);
    newNode->next = top;
    top = newNode;
    size++;
}

bool StackEngine::pop(std::string& outDesc, StudentRecord& outRecord) {
    if (isEmpty()) return false;
    StackNode* temp = top;
    outDesc = temp->actionDescription;
    outRecord = temp->snapshot;
    top = top->next;
    delete temp;
    size--;
    return true;
}

bool StackEngine::peek(std::string& outDesc, StudentRecord& outRecord) const {
    if (isEmpty()) return false;
    outDesc = top->actionDescription;
    outRecord = top->snapshot;
    return true;
}

void StackEngine::displayStack() const {
    if (isEmpty()) {
        std::cout << "[Stack] Undo audit trail is currently empty.\n";
        return;
    }
    std::cout << "\n========================== LIFO UNDO AUDIT TRAIL (STACK TOP -> BOTTOM) ==========================\n";
    StackNode* current = top;
    int idx = 1;
    while (current) {
        std::cout << idx++ << ". Action: " << current->actionDescription
                  << " | Student ID: " << current->snapshot.studentId
                  << " (" << current->snapshot.fullName << ")\n";
        current = current->next;
    }
    std::cout << "=================================================================================================\n";
}

bool StackEngine::isEmpty() const { return top == nullptr; }
int StackEngine::getSize() const { return size; }
