#include "BaggageFlow.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

void BaggageFlow::loadManifest(const std::string& path) {
    std::cout << "[BaggageFlow] Loading manifest from " << path << "\n";
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "[BaggageFlow] Error: Could not open manifest file: " << path << "\n";
        return;
    }
    
    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string id, passengerID, type, priorityStr, origin;
        
        if (std::getline(iss, id, ',') && 
            std::getline(iss, passengerID, ',') && 
            std::getline(iss, type, ',') && 
            std::getline(iss, priorityStr, ',') && 
            std::getline(iss, origin)) {
            
            try {
                int priority = std::stoi(priorityStr);
                BaggageItem item = {id, priority, type, origin, "DEST", passengerID}; // DEST placeholder
                baggageList.push_back(item);
                baggageMap[id] = item;
                count++;
            } catch (const std::exception&) {
                continue;
            }
        }
    }
    std::cout << "[BaggageFlow] Successfully loaded " << count << " baggage records\n";
    file.close();
}

void BaggageFlow::insertNext() {
    if (nextIndex >= baggageList.size()) {
        std::cout << "[BaggageFlow] No more baggage to insert\n";
        return;
    }
    
    const BaggageItem& item = baggageList[nextIndex];
    priorityQueue.push({-item.priority, item.id}); // Negative for min-heap
    std::cout << "[BaggageFlow] Inserted baggage " << item.id << " (Priority: " << item.priority << ")\n";
    std::cout << "[BaggageFlow] Type: " << item.type << ", Origin: " << item.origin << "\n";
    std::cout << "[BaggageFlow] Passenger: " << item.passengerID << "\n";
    nextIndex++;
}

void BaggageFlow::extractNext() {
    if (priorityQueue.empty()) {
        std::cout << "[BaggageFlow] Priority queue is empty\n";
        return;
    }
    
    auto top = priorityQueue.top();
    priorityQueue.pop();
    int priority = -top.first; // Convert back from negative
    std::string id = top.second;
    
    auto it = baggageMap.find(id);
    if (it != baggageMap.end()) {
        const BaggageItem& item = it->second;
        std::cout << "[BaggageFlow] Extracted baggage " << id << " (Priority: " << priority << ")\n";
        std::cout << "[BaggageFlow] Passenger: " << item.passengerID << ", Type: " << item.type << "\n";
        std::cout << "[BaggageFlow] Origin: " << item.origin << "\n";
    }
}

void BaggageFlow::showQueueStatus() {
    std::cout << "[BaggageFlow] Queue Status:\n";
    std::cout << "  Total baggage loaded: " << baggageList.size() << "\n";
    std::cout << "  Next to insert: " << nextIndex << "\n";
    std::cout << "  Items in priority queue: " << priorityQueue.size() << "\n";
    
    if (!priorityQueue.empty()) {
        std::cout << "  Next to extract: " << priorityQueue.top().second << "\n";
    }
}
