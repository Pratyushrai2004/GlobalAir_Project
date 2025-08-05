#include "FrequentFlyer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

void FrequentFlyer::loadFrequentFlyers(const std::string& path) {
    std::cout << "[FrequentFlyer] Loading frequent flyer data from " << path << "\n";
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "[FrequentFlyer] Error: Could not open frequent flyer file: " << path << "\n";
        return;
    }
    
    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string passengerID, flightsStr, milesStr, tier;
        
        if (std::getline(iss, passengerID, ',') && 
            std::getline(iss, flightsStr, ',') && 
            std::getline(iss, milesStr, ',') && 
            std::getline(iss, tier)) {
            
            try {
                int flights = std::stoi(flightsStr);
                int miles = std::stoi(milesStr);
                
                FlyerRecord record = {passengerID, flights, miles, tier};
                flyers.push_back(record);
                flyerMap[passengerID] = record;
                count++;
            } catch (const std::exception&) {
                // Skip invalid lines
                continue;
            }
        }
    }
    std::cout << "[FrequentFlyer] Successfully loaded " << count << " frequent flyer records\n";
    file.close();
}

void FrequentFlyer::topKByFlights(int k) {
    std::cout << "[FrequentFlyer] Showing top-" << k << " flyers by flight count\n";
    
    // Sort by flights (descending)
    std::vector<FlyerRecord> sortedByFlights = flyers;
    std::sort(sortedByFlights.begin(), sortedByFlights.end(),
              [](const auto& a, const auto& b) { return a.flights > b.flights; });
    
    // Display top-K
    std::cout << std::setw(12) << "Passenger ID" << " | " 
              << std::setw(8) << "Flights" << " | " 
              << std::setw(8) << "Miles" << " | " 
              << std::setw(10) << "Tier" << "\n";
    std::cout << std::string(45, '-') << "\n";
    
    for (int i = 0; i < std::min(k, (int)sortedByFlights.size()); i++) {
        const auto& record = sortedByFlights[i];
        std::cout << std::setw(12) << record.passengerID << " | " 
                  << std::setw(8) << record.flights << " | " 
                  << std::setw(8) << record.miles << " | " 
                  << std::setw(10) << record.tier << "\n";
    }
}

void FrequentFlyer::topKByMiles(int k) {
    std::cout << "[FrequentFlyer] Showing top-" << k << " flyers by miles\n";
    
    // Sort by miles (descending)
    std::vector<FlyerRecord> sortedByMiles = flyers;
    std::sort(sortedByMiles.begin(), sortedByMiles.end(),
              [](const auto& a, const auto& b) { return a.miles > b.miles; });
    
    // Display top-K
    std::cout << std::setw(12) << "Passenger ID" << " | " 
              << std::setw(8) << "Flights" << " | " 
              << std::setw(8) << "Miles" << " | " 
              << std::setw(10) << "Tier" << "\n";
    std::cout << std::string(45, '-') << "\n";
    
    for (int i = 0; i < std::min(k, (int)sortedByMiles.size()); i++) {
        const auto& record = sortedByMiles[i];
        std::cout << std::setw(12) << record.passengerID << " | " 
                  << std::setw(8) << record.flights << " | " 
                  << std::setw(8) << record.miles << " | " 
                  << std::setw(10) << record.tier << "\n";
    }
}
