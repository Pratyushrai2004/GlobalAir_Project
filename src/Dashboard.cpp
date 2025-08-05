#include "Dashboard.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>

void Dashboard::loadDelays(const std::string& path) {
    std::cout << "[Dashboard] Loading delays data from " << path << "\n";
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "[Dashboard] Error: Could not open delays file: " << path << "\n";
        return;
    }
    
    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string airport, delayStr, timestamp;
        
        if (std::getline(iss, airport, ',') && 
            std::getline(iss, delayStr, ',') && 
            std::getline(iss, timestamp)) {
            
            try {
                int delayMinutes = std::stoi(delayStr);
                delays.push_back({airport, delayMinutes, timestamp});
                
                // Group delays by airport for average calculation
                airportDelays[airport].push_back(delayMinutes);
                count++;
            } catch (const std::exception&) {
                // Skip invalid lines
                continue;
            }
        }
    }
    std::cout << "[Dashboard] Successfully loaded " << count << " delay records\n";
    file.close();
}

void Dashboard::loadLostBaggage(const std::string& path) {
    std::cout << "[Dashboard] Loading lost baggage data from " << path << "\n";
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "[Dashboard] Error: Could not open lost baggage file: " << path << "\n";
        return;
    }
    
    std::string line;
    int count = 0;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string baggageID, passengerID, location, status, description;
        
        if (std::getline(iss, baggageID, ',') && 
            std::getline(iss, passengerID, ',') && 
            std::getline(iss, location, ',') && 
            std::getline(iss, status, ',') && 
            std::getline(iss, description)) {
            
            lostBaggageMap[baggageID] = {baggageID, passengerID, location, status, description};
            count++;
        }
    }
    std::cout << "[Dashboard] Successfully loaded " << count << " lost baggage records\n";
    file.close();
}

void Dashboard::showTotalDelayedFlights() {
    int totalDelayed = 0;
    for (const auto& delay : delays) {
        if (delay.delayMinutes > 0) {
            totalDelayed++;
        }
    }
    std::cout << "[Dashboard] Total flights delayed: " << totalDelayed << "\n";
}

void Dashboard::topKDelayProne(int k) {
    std::cout << "[Dashboard] Showing top-" << k << " airports by average delay\n";
    
    // Calculate average delays for each airport
    std::vector<std::pair<std::string, double>> airportAverages;
    for (const auto& pair : airportDelays) {
        const std::string& airport = pair.first;
        const std::vector<int>& delays = pair.second;
        
        double sum = 0;
        for (int delay : delays) {
            sum += delay;
        }
        double average = sum / delays.size();
        airportAverages.push_back({airport, average});
    }
    
    // Sort by average delay (descending)
    std::sort(airportAverages.begin(), airportAverages.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });
    
    // Display top-K
    std::cout << std::setw(10) << "Airport" << " | " << std::setw(15) << "Avg Delay (min)" << "\n";
    std::cout << std::string(30, '-') << "\n";
    
    for (int i = 0; i < std::min(k, (int)airportAverages.size()); i++) {
        std::cout << std::setw(10) << airportAverages[i].first << " | " 
                  << std::setw(15) << std::fixed << std::setprecision(1) 
                  << airportAverages[i].second << "\n";
    }
}

void Dashboard::queryLostBaggage(const std::string& baggageID) {
    auto it = lostBaggageMap.find(baggageID);
    if (it != lostBaggageMap.end()) {
        const auto& record = it->second;
        std::cout << "[Dashboard] Lost Baggage Details for " << baggageID << ":\n";
        std::cout << "  Passenger ID: " << record.passengerID << "\n";
        std::cout << "  Last Known Location: " << record.lastKnownLocation << "\n";
        std::cout << "  Status: " << record.status << "\n";
        std::cout << "  Description: " << record.description << "\n";
    } else {
        std::cout << "[Dashboard] Baggage ID " << baggageID << " not found in records.\n";
    }
}
