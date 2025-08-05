#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include "Graph.h"
#include "BaggageFlow.h"
#include "LostBaggage.h"
#include "DelayAnalysis.h"
#include "Sorting.h"
#include "Dashboard.h"
#include "FrequentFlyer.h"
#include "BaggageSecurity.h"

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getIntInput(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        try {
            return std::stoi(input);
        } catch (const std::exception&) {
            std::cout << "Invalid input. Please enter a valid number.\n";
        }
    }
}

int main() {
    Graph graph; 
    BaggageFlow bf; 
    LostBaggage lb;
    DelayAnalysis da; 
    Sorting sort; 
    Dashboard db;
    FrequentFlyer ff; 
    BaggageSecurity bs;

    std::cout << "=== GlobalAir System ===\n\n";
    std::cout << "Loading data files automatically...\n";
    
    // Automatically load all data files from data/ directory (relative to project root)
    graph.loadAirports("data/airports.dat");
    // Debug: Print all loaded IATA codes
    std::cout << "[DEBUG] Loaded IATA codes (" << graph.getNumAirports() << "): ";
    for (int i = 0; i < graph.getNumAirports(); ++i) {
        std::cout << graph.getAirportCode(i);
        if (i < graph.getNumAirports() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    graph.loadRoutes("data/routes.dat",0); 
    bf.loadManifest("data/baggage_manifest.csv");
    lb.loadLostBaggage("data/lost_baggage.csv");
    da.loadDelays("data/delays.csv");
    bs.loadRules("data/security_rules.txt");
    ff.loadFrequentFlyers("data/frequent_flyer.csv");
    
    // Load data for Dashboard
    db.loadDelays("data/delays.csv");
    db.loadLostBaggage("data/lost_baggage.csv");

    std::cout << "\nData loading complete! Press ENTER to continue...";
    std::string temp;
    std::getline(std::cin, temp);

    while (true) {
        std::cout << "\n=== GlobalAir Menu ===\n"
                  << "1: Shortest Path (Dijkstra/Bellman-Ford)\n"
                  << "2: Baggage Flow (Insert/Extract/Status)\n"
                  << "3: Lost Baggage (Report/Resolve/Query)\n"
                  << "4: Delay Analysis (Longest Chain)\n"
                  << "5: Sorting Algorithms\n"
                  << "6: Dashboard (Total Delayed + Top-K)\n"
                  << "7: Frequent Flyer (Top-K Analysis)\n"
                  << "8: Baggage Security (Risk Assessment)\n"
                  << "9: Exit\n"
                  << "Choice: ";
        
        std::getline(std::cin, temp);
        int choice = 0;
        try { 
            choice = std::stoi(temp); 
        } catch (const std::exception&) { 
            std::cout << "Invalid choice. Please enter a number 1-9.\n"; 
            continue; 
        }
        
        if (choice == 9) {
            std::cout << "Goodbye!\n";
            break;
        }
        
        switch(choice) {
            case 1: {
                std::string src, dst, costType;
                std::cout << "Source IATA: "; 
                std::getline(std::cin, src);
                std::cout << "Destination IATA: "; 
                std::getline(std::cin, dst);
                std::cout << "Cost type (distance/delay/cost): "; 
                std::getline(std::cin, costType);
                
                if (costType == "delay") {
                    graph.bellmanFord(src, dst);
                } else {
                    graph.dijkstra(src, dst);
                }
                break;
            }
            case 2: {
                std::cout << "Baggage Flow Options:\n";
                std::cout << "1: Insert next baggage\n";
                std::cout << "2: Extract next baggage\n";
                std::cout << "3: Show queue status\n";
                std::cout << "Choice: ";
                std::getline(std::cin, temp);
                int subChoice = std::stoi(temp);
                
                switch(subChoice) {
                    case 1: bf.insertNext(); break;
                    case 2: bf.extractNext(); break;
                    case 3: bf.showQueueStatus(); break;
                    default: std::cout << "Invalid choice.\n";
                }
                break;
            }
            case 3: {
                std::cout << "Lost Baggage Options:\n";
                std::cout << "1: Report lost baggage\n";
                std::cout << "2: Resolve lost baggage\n";
                std::cout << "3: Query baggage by ID\n";
                std::cout << "Choice: ";
                std::getline(std::cin, temp);
                int subChoice = std::stoi(temp);
                
                std::string id;
                std::cout << "Baggage ID: "; 
                std::getline(std::cin, id);
                
                switch(subChoice) {
                    case 1: lb.report(id); break;
                    case 2: lb.resolve(id); break;
                    case 3: lb.queryByID(id); break;
                    default: std::cout << "Invalid choice.\n";
                }
                break;
            }
            case 4: {
                std::string src;
                std::cout << "Starting airport IATA: "; 
                std::getline(std::cin, src);
                da.longestDelayChain(src);
                break;
            }
            case 5: {
                int n = getIntInput("Enter number of elements (N): ");
                std::vector<int> v(n);
                for(int i = 0; i < n; i++) {
                    v[i] = getIntInput("Enter value " + std::to_string(i) + ": ");
                }
                sort.runAll(v);
                break;
            }
            case 6: {
                std::cout << "=== Dashboard ===\n";
                db.showTotalDelayedFlights();
                std::cout << "\n";
                int k = getIntInput("Enter K for top-K airports by average delay: ");
                db.topKDelayProne(k);
                std::cout << "\n";
                std::string baggageID;
                std::cout << "Enter baggage ID to query: ";
                std::getline(std::cin, baggageID);
                db.queryLostBaggage(baggageID);
                break;
            }
            case 7: {
                std::string pid; 
                int k;
                std::cout << "Passenger ID: "; 
                std::getline(std::cin, pid);
                k = getIntInput("Enter K for top-K analysis: ");
                ff.topKByFlights(k); 
                std::cout << "\n";
                ff.topKByMiles(k);
                break;
            }
            case 8: {
                std::string id, pid, orig, dest, type, hist;
                std::cout << "Baggage ID: "; 
                std::getline(std::cin, id);
                std::cout << "Passenger ID: "; 
                std::getline(std::cin, pid);
                std::cout << "Origin: "; 
                std::getline(std::cin, orig);
                std::cout << "Destination: "; 
                std::getline(std::cin, dest);
                std::cout << "Baggage Type: "; 
                std::getline(std::cin, type);
                std::cout << "History: "; 
                std::getline(std::cin, hist);
                bs.assessBaggageRisk(id, pid, orig, dest, type, hist);
                break;
            }
            default: 
                std::cout << "Invalid choice. Please enter a number 1-9.\n";
        }
    }
    return 0;
}
