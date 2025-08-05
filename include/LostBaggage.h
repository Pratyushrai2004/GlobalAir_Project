#pragma once
#include <string>
#include <unordered_map>

struct BaggageRecord {
    std::string baggageID;
    std::string passengerID;
    std::string lastKnownLocation;
    std::string status;
    std::string description;
};

class LostBaggage {
private:
    std::unordered_map<std::string, BaggageRecord> baggageMap;

public:
    // Load lost baggage records (ID, lastCheckpoint, status)
    void loadLostBaggage(const std::string& path);
    // Report lost baggage by ID
    void report(const std::string& id);
    // Resolve lost baggage by ID
    void resolve(const std::string& id);
    // Query baggage by ID and show full details
    void queryByID(const std::string& id);
};
