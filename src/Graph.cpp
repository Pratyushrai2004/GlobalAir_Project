#include "Graph.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
#include <limits>
#include <algorithm>

void Graph::loadAirports(const std::string& filepath) {
    airportToIndex.clear();
    indexToAirport.clear();
    adj.clear();

    std::ifstream in(filepath);
    if (!in.is_open()) {
        std::cerr << "[ERROR] Could not open airports file: " << filepath << std::endl;
        return;
    }
    std::string line;
    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string id,name,city,country,iata;
        std::getline(ss,id,',');
        std::getline(ss,name,',');
        std::getline(ss,city,',');
        std::getline(ss,country,',');
        std::getline(ss,iata,',');
        // Remove quotes if present
        if (!iata.empty() && iata.front() == '"' && iata.back() == '"') {
            iata = iata.substr(1, iata.size() - 2);
        }
        if (iata != "\\N" && !iata.empty()) {
            int idx = indexToAirport.size();
            airportToIndex[iata] = idx;
            indexToAirport.push_back(iata);
            adj.emplace_back();
        }
    }
}

void Graph::loadRoutes(const std::string& filepath, int mode) {
    // mode==0 → distance in 7th column; mode==1 → delay in 8th column
    std::ifstream in(filepath);
    std::string line;
    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string airline, aid, src, srcid, dst, dstid;
        std::string distStr, delayStr, aircraft;
        std::getline(ss, airline, ',');
        std::getline(ss, aid,     ',');
        std::getline(ss, src,     ',');
        std::getline(ss, srcid,   ',');
        std::getline(ss, dst,     ',');
        std::getline(ss, dstid,   ',');
        std::getline(ss, distStr, ',');
        std::getline(ss, delayStr,',');
        std::getline(ss, aircraft,',');

        if (src == "\\N" || dst == "\\N") continue;
        auto itU = airportToIndex.find(src);
        auto itV = airportToIndex.find(dst);
        if (itU == airportToIndex.end() || itV == airportToIndex.end()) continue;

        double w = 1.0;
        try {
            if (mode == 0 && !distStr.empty()) {
                w = std::stod(distStr);
            } else if (mode == 1 && !delayStr.empty()) {
                w = std::stod(delayStr);
            } else {
                // fallback default
                w = (aircraft == "CR2" ? 500.0 : 1000.0);
            }
        } catch (...) {
            w = (aircraft == "CR2" ? 500.0 : 1000.0);
        }

        int u = itU->second;
        int v = itV->second;
        adj[u].push_back({v, w});
    }
}

int Graph::getAirportIndex(const std::string& code) const {
    auto it = airportToIndex.find(code);
    return (it == airportToIndex.end() ? -1 : it->second);
}

std::string Graph::getAirportCode(int idx) const {
    if (idx < 0 || idx >= (int)indexToAirport.size()) return "";
    return indexToAirport[idx];
}

int Graph::getNumAirports() const {
    return (int)indexToAirport.size();
}

const std::vector<Edge>& Graph::getAdj(int u) const {
    return adj[u];
}

void Graph::dijkstra(const std::string& src, const std::string& dst) {
    int srcIdx = getAirportIndex(src);
    int dstIdx = getAirportIndex(dst);
    if (srcIdx == -1) {
        std::cout << "Error: Source airport '" << src << "' not found.\n";
        return;
    }
    if (dstIdx == -1) {
        std::cout << "Error: Destination airport '" << dst << "' not found.\n";
        return;
    }
    int n = getNumAirports();
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    std::vector<int> parent(n, -1);
    std::vector<bool> visited(n, false);
    dist[srcIdx] = 0.0;
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, std::greater<std::pair<double, int>>> pq;
    pq.push({0.0, srcIdx});
    while (!pq.empty()) {
        double currentDist = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        if (visited[u]) continue;
        visited[u] = true;
        if (u == dstIdx) break;
        for (const Edge& edge : adj[u]) {
            int v = edge.to;
            double weight = edge.weight;
            if (!visited[v] && currentDist + weight < dist[v]) {
                dist[v] = currentDist + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    if (dist[dstIdx] == std::numeric_limits<double>::infinity()) {
        std::cout << "No path found from " << src << " to " << dst << ".\n";
    } else {
        std::cout << "Shortest path from " << src << " to " << dst << ":\n";
        std::cout << "Total distance: " << dist[dstIdx] << "\n";
        std::vector<std::string> path;
        int current = dstIdx;
        while (current != -1) {
            path.push_back(getAirportCode(current));
            current = parent[current];
        }
        std::reverse(path.begin(), path.end());
        std::cout << "Path: ";
        for (size_t i = 0; i < path.size(); ++i) {
            if (i > 0) std::cout << " -> ";
            std::cout << path[i];
        }
        std::cout << "\n";
    }
}

void Graph::bellmanFord(const std::string& src, const std::string& dst) {
    int srcIdx = getAirportIndex(src);
    int dstIdx = getAirportIndex(dst);
    if (srcIdx == -1) {
        std::cout << "Error: Source airport '" << src << "' not found.\n";
        return;
    }
    if (dstIdx == -1) {
        std::cout << "Error: Destination airport '" << dst << "' not found.\n";
        return;
    }
    int n = getNumAirports();
    std::vector<double> dist(n, std::numeric_limits<double>::infinity());
    std::vector<int> parent(n, -1);
    dist[srcIdx] = 0.0;
    for (int i = 0; i < n - 1; ++i) {
        for (int u = 0; u < n; ++u) {
            for (const Edge& edge : adj[u]) {
                int v = edge.to;
                double weight = edge.weight;
                if (dist[u] != std::numeric_limits<double>::infinity() && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                }
            }
        }
    }
    bool hasNegativeCycle = false;
    for (int u = 0; u < n; ++u) {
        for (const Edge& edge : adj[u]) {
            int v = edge.to;
            double weight = edge.weight;
            if (dist[u] != std::numeric_limits<double>::infinity() && dist[u] + weight < dist[v]) {
                hasNegativeCycle = true;
                break;
            }
        }
        if (hasNegativeCycle) break;
    }
    if (hasNegativeCycle) {
        std::cout << "Warning: Negative cycle detected in the graph.\n";
    }
    if (dist[dstIdx] == std::numeric_limits<double>::infinity()) {
        std::cout << "No path found from " << src << " to " << dst << ".\n";
    } else {
        std::cout << "Shortest path from " << src << " to " << dst << " (Bellman-Ford):\n";
        std::cout << "Total distance: " << dist[dstIdx] << "\n";
        std::vector<std::string> path;
        int current = dstIdx;
        while (current != -1) {
            path.push_back(getAirportCode(current));
            current = parent[current];
        }
        std::reverse(path.begin(), path.end());
        std::cout << "Path: ";
        for (size_t i = 0; i < path.size(); ++i) {
            if (i > 0) std::cout << " -> ";
            std::cout << path[i];
        }
        std::cout << "\n";
    }
}
