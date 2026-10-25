#ifndef QUEUE_ENGINE_H
#define QUEUE_ENGINE_H

#include "EntityModel.h"

struct QueueNode {
    StudentRecord data;
    QueueNode* next;
    QueueNode(StudentRecord rec) : data(rec), next(nullptr) {}
};

class StandardQueue {
private:
    QueueNode* frontNode;
    QueueNode* rearNode;
    int count;

public:
    StandardQueue();
    ~StandardQueue();

    void enqueue(StudentRecord record);
    bool dequeue(StudentRecord& outRecord);
    bool peek(StudentRecord& outRecord) const;
    void displayQueue() const;
    bool isEmpty() const;
    int getCount() const;
};

class PriorityQueueEngine {
private:
    QueueNode* head;
    int count;

public:
    PriorityQueueEngine();
    ~PriorityQueueEngine();

    void priorityEnqueue(StudentRecord record);
    bool dequeue(StudentRecord& outRecord);
    bool peek(StudentRecord& outRecord) const;
    void displayQueue() const;
    bool isEmpty() const;
    int getCount() const;
};

#endif
