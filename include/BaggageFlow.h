#pragma once
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

struct BaggageItem {
    std::string id;
    int priority;
    std::string type;
    std::string origin;
    std::string destination;
    std::string passengerID;
};

class BaggageFlow {
private:
    std::vector<BaggageItem> baggageList;
    std::priority_queue<std::pair<int, std::string>> priorityQueue; // min-heap
    std::unordered_map<std::string, BaggageItem> baggageMap;
    int nextIndex;

public:
    BaggageFlow() : nextIndex(0) {}
    
    // Load baggage manifest (ID, priority, type, origin, dest)
    void loadManifest(const std::string& path);
    // Insert next baggage into BST + min-heap
    void insertNext();
    // Extract next baggage from heap
    void extractNext();
    // Show current queue status
    void showQueueStatus();
};
