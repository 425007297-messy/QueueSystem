#ifndef ENTITY_MODEL_H
#define ENTITY_MODEL_H

#include <string>

enum class PriorityTier {
    REGULAR = 1,
    GRADUATING = 2,
    PWD_SENIOR = 3
};

struct StudentRecord {
    int studentId;
    std::string fullName;
    std::string serviceType;
    PriorityTier priorityStatus;
    double gpa;
    std::string timestamp;
};

inline std::string priorityTierToString(PriorityTier tier) {
    switch (tier) {
        case PriorityTier::REGULAR: return "Regular";
        case PriorityTier::GRADUATING: return "Graduating";
        case PriorityTier::PWD_SENIOR: return "PWD / Senior";
        default: return "Unknown";
    }
}

#endif
