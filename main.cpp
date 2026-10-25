#include <iostream>
#include <limits>
#include "LinkedListEngine.h"
#include "StackEngine.h"
#include "QueueEngine.h"
#include "SearchSortEngine.h"
#include "BenchmarkingSuite.h"

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    LinkedListEngine masterRegistry;
    StackEngine undoStack;
    StandardQueue regularQueue;
    PriorityQueueEngine priorityQueue;

    int mainChoice = 0;
    do {
        std::cout << "\n=======================================================\n";
        std::cout << "     UNIQUEUE: STUDENT SERVICE & BENCHMARKING ENGINE   \n";
        std::cout << "=======================================================\n";
        std::cout << " 1. Master Student Registry\n";
        std::cout << " 2. Standard Service Line\n";
        std::cout << " 3. Priority Express Lane\n";
        std::cout << " 4. Undo Action Engine\n";
        std::cout << " 5. Search & Sort Student Records\n";
        std::cout << " 6. Execute Empirical Benchmarking Suite\n";
        std::cout << " 7. Exit System\n";
        std::cout << "-------------------------------------------------------\n";
        std::cout << "Enter Choice [1-7]: ";

        if (!(std::cin >> mainChoice)) {
            std::cout << "[Error] Invalid input type. Please enter a valid integer.\n";
            clearInputBuffer();
            continue;
        }

        switch (mainChoice) {
            case 1: {
                int subChoice = 0;
                std::cout << "\n--- MASTER REGISTRY MENU ---\n";
                std::cout << "1. View All Records Forward\n";
                std::cout << "2. View All Records Backward\n";
                std::cout << "3. Add New Student Record\n";
                std::cout << "4. Delete Student Record by ID\n";
                std::cout << "5. Update Student Record\n";
                std::cout << "Enter choice: ";
                std::cin >> subChoice;

                if (subChoice == 1) {
                    masterRegistry.displayForward();
                } else if (subChoice == 2) {
                    masterRegistry.displayBackward();
                } else if (subChoice == 3) {
                    int id; double gpa; int tierChoice;
                    std::string name, service, time;
                    std::cout << "Enter Student ID: "; std::cin >> id;
                    clearInputBuffer();
                    std::cout << "Enter Full Name: "; std::getline(std::cin, name);
                    std::cout << "Enter Service Type: "; std::getline(std::cin, service);
                    std::cout << "Enter Priority Tier (1-Regular, 2-Graduating, 3-PWD/Senior): "; std::cin >> tierChoice;
                    std::cout << "Enter GPA: "; std::cin >> gpa;
                    clearInputBuffer();
                    std::cout << "Enter Timestamp: "; std::getline(std::cin, time);

                    StudentRecord newRec = {id, name, service, static_cast<PriorityTier>(tierChoice), gpa, time};
                    masterRegistry.insertTail(newRec);
                    undoStack.push("Add Student", newRec);
                    std::cout << "[Success] Student record added successfully!\n";
                } else if (subChoice == 4) {
                    int id;
                    std::cout << "Enter Student ID to delete: "; std::cin >> id;
                    ListNode* nodeToDelete = masterRegistry.searchRecord(id);
                    if (nodeToDelete) {
                        StudentRecord backup = nodeToDelete->data;
                        if (masterRegistry.deleteRecord(id)) {
                            undoStack.push("Delete Student", backup);
                            std::cout << "[Success] Student ID " << id << " deleted and logged to undo stack.\n";
                        }
                    } else {
                        std::cout << "[Error] Student ID not found in registry.\n";
                    }
                } else if (subChoice == 5) {
                    int id; double gpa; std::string service;
                    std::cout << "Enter Student ID to update: "; std::cin >> id;
                    clearInputBuffer();
                    std::cout << "Enter New Service Type: "; std::getline(std::cin, service);
                    std::cout << "Enter New GPA: "; std::cin >> gpa;
                    if (masterRegistry.updateRecord(id, service, gpa)) {
                        std::cout << "[Success] Student record updated successfully!\n";
                    } else {
                        std::cout << "[Error] Record not found.\n";
                    }
                }
                break;
            }
            case 2: {
                int qChoice;
                std::cout << "\n--- STANDARD QUEUE MENU ---\n";
                std::cout << "1. Enqueue Student to Walk-in Line\n";
                std::cout << "2. Serve / Dequeue Next Student\n";
                std::cout << "3. View Queue Status\n";
                std::cout << "Enter choice: "; std::cin >> qChoice;

                if (qChoice == 1) {
                    int id; double gpa;
                    std::string name, service, time;
                    std::cout << "Enter ID: "; std::cin >> id;
                    clearInputBuffer();
                    std::cout << "Name: "; std::getline(std::cin, name);
                    std::cout << "Service: "; std::getline(std::cin, service);
                    StudentRecord r = {id, name, service, PriorityTier::REGULAR, 1.75, "09:00 AM"};
                    regularQueue.enqueue(r);
                    std::cout << "[Success] Added to standard queue line.\n";
                } else if (qChoice == 2) {
                    StudentRecord served;
                    if (regularQueue.dequeue(served)) {
                        std::cout << "[Served] Now processing: " << served.fullName << "\n";
                    } else {
                        std::cout << "[Queue] Line is empty.\n";
                    }
                } else if (qChoice == 3) {
                    regularQueue.displayQueue();
                }
                break;
            }
            case 3: {
                int pChoice;
                std::cout << "\n--- PRIORITY EXPRESS LANE MENU ---\n";
                std::cout << "1. Priority Enqueue\n";
                std::cout << "2. Serve Priority Student\n";
                std::cout << "3. View Priority Lane\n";
                std::cout << "Enter choice: "; std::cin >> pChoice;

                if (pChoice == 1) {
                    int id, tier;
                    std::string name, service;
                    std::cout << "Enter ID: "; std::cin >> id;
                    clearInputBuffer();
                    std::cout << "Name: "; std::getline(std::cin, name);
                    std::cout << "Service: "; std::getline(std::cin, service);
                    std::cout << "Priority Tier (2-Graduating, 3-PWD/Senior): "; std::cin >> tier;
                    StudentRecord r = {id, name, service, static_cast<PriorityTier>(tier), 1.5, "09:05 AM"};
                    priorityQueue.priorityEnqueue(r);
                    std::cout << "[Success] Enqueued into priority triage lane.\n";
                } else if (pChoice == 2) {
                    StudentRecord served;
                    if (priorityQueue.dequeue(served)) {
                        std::cout << "[Served] Priority client processed: " << served.fullName << "\n";
                    } else {
                        std::cout << "[Priority Queue] Triage queue is empty.\n";
                    }
                } else if (pChoice == 3) {
                    priorityQueue.displayQueue();
                }
                break;
            }
            case 4: {
                std::cout << "\n--- LIFO UNDO AUDIT ENGINE ---\n";
                undoStack.displayStack();
                std::cout << "Do you want to undo the last action? (1-Yes, 0-No): ";
                int undoChoice; std::cin >> undoChoice;
                if (undoChoice == 1) {
                    std::string action; StudentRecord rec;
                    if (undoStack.pop(action, rec)) {
                        std::cout << "[Undo Executed] Reverted action: " << action << " on Student ID " << rec.studentId << "\n";
                    } else {
                        std::cout << "[Undo] No actions left to undo.\n";
                    }
                }
                break;
            }
            case 5: {
                int size = 0;
                StudentRecord* arr = masterRegistry.toArray(size);
                if (size == 0) {
                    std::cout << "[Search/Sort] Registry is empty.\n";
                    break;
                }

                int sChoice;
                std::cout << "\n--- SEARCH & SORT ENGINE ---\n";
                std::cout << "1. Perform Linear Search\n";
                std::cout << "2. Perform Binary Search\n";
                std::cout << "3. Run Sorting Algorithms & Metrics\n";
                std::cout << "Enter choice: "; std::cin >> sChoice;

                if (sChoice == 1) {
                    int targetId;
                    std::cout << "Enter Student ID to search: "; std::cin >> targetId;
                    long long comps = 0;
                    int idx = SearchSortEngine::linearSearch(arr, size, targetId, comps);
                    if (idx != -1) {
                        std::cout << "[Found via Linear Search] ID: " << arr[idx].studentId << " | Name: " << arr[idx].fullName << " | Comparisons: " << comps << "\n";
                    } else {
                        std::cout << "[Not Found] Record does not exist. Comparisons: " << comps << "\n";
                    }
                } else if (sChoice == 2) {
                    long long dComps = 0, dSwaps = 0;
                    SearchSortEngine::insertionSort(arr, size, dComps, dSwaps);
                    int targetId;
                    std::cout << "Enter Student ID to search: "; std::cin >> targetId;
                    long long comps = 0;
                    int idx = SearchSortEngine::binarySearch(arr, size, targetId, comps);
                    if (idx != -1) {
                        std::cout << "[Found via Binary Search] ID: " << arr[idx].studentId << " | Name: " << arr[idx].fullName << " | Comparisons: " << comps << "\n";
                    } else {
                        std::cout << "[Not Found] Record does not exist. Comparisons: " << comps << "\n";
                    }
                } else if (sChoice == 3) {
                    long long comps = 0, swaps = 0;
                    StudentRecord* sortCopy = new StudentRecord[size];
                    for(int i=0; i<size; i++) sortCopy[i] = arr[i];

                    SearchSortEngine::insertionSort(sortCopy, size, comps, swaps);
                    std::cout << "\n[Insertion Sort Results]\n- Comparisons: " << comps << "\n- Swaps: " << swaps << "\n";
                    delete[] sortCopy;
                }
                delete[] arr;
                break;
            }
            case 6:
                BenchmarkingSuite::runBenchmarkSuite();
                break;
            case 7:
                std::cout << "Exiting UniQueue Engine. Cleaning up memory... Goodbye!\n";
                break;
            default:
                std::cout << "[Error] Invalid menu option. Please choose between 1 and 7.\n";
        }
    } while (mainChoice != 7);

    std::cout << "\nPress Enter to exit the program...";
    clearInputBuffer();
    std::cin.get();

    return 0;
}
