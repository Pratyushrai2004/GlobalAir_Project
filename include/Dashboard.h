#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct DelayRecord {
    std::string airport;
    int delayMinutes;
    std::string timestamp;
};

struct LostBaggageRecord {
    std::string baggageID;
    std::string passengerID;
    std::string lastKnownLocation;
    std::string status;
    std::string description;
};

class Dashboard {
private:
    std::vector<DelayRecord> delays;
    std::unordered_map<std::string, LostBaggageRecord> lostBaggageMap;
    std::unordered_map<std::string, std::vector<int>> airportDelays;

public:
    // Load delays data and parse it
    void loadDelays(const std::string& path);
    // Load lost baggage data and parse it
    void loadLostBaggage(const std::string& path);
    // Show total delayed flights count
    void showTotalDelayedFlights();
    // Show top-K routes by average delay
    void topKDelayProne(int k);
    // Query lost baggage by ID
    void queryLostBaggage(const std::string& baggageID);
};
