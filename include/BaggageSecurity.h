#pragma once
#include <string>

class BaggageSecurity {
public:
    // Load security rules
    void loadRules(const std::string& path);
    // Assess risk for a baggage entry
    void assessBaggageRisk(const std::string& id,
                           const std::string& passengerID,
                           const std::string& origin,
                           const std::string& dest,
                           const std::string& type,
                           const std::string& history);
};
