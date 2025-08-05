#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct FlyerRecord {
    std::string passengerID;
    int flights;
    int miles;
    std::string tier;
};

class FrequentFlyer {
private:
    std::vector<FlyerRecord> flyers;
    std::unordered_map<std::string, FlyerRecord> flyerMap;

public:
    // Load frequent flyer data (passengerID, flights, miles, tier)
    void loadFrequentFlyers(const std::string& path);
    // Display top-K flyers by flight count
    void topKByFlights(int k);
    // Display top-K flyers by miles
    void topKByMiles(int k);
};
