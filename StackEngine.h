#ifndef STACK_ENGINE_H
#define STACK_ENGINE_H

#include "EntityModel.h"
#include <string>

struct StackNode {
    std::string actionDescription;
    StudentRecord snapshot;
    StackNode* next;
    StackNode(std::string desc, StudentRecord rec) : actionDescription(desc), snapshot(rec), next(nullptr) {}
};

class StackEngine {
private:
    StackNode* top;
    int size;

public:
    StackEngine();
    ~StackEngine();

    void push(std::string actionDesc, StudentRecord record);
    bool pop(std::string& outDesc, StudentRecord& outRecord);
    bool peek(std::string& outDesc, StudentRecord& outRecord) const;
    void displayStack() const;
    bool isEmpty() const;
    int getSize() const;
};

#endif
