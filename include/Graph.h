#pragma once
#include <string>
#include <vector>
#include <unordered_map>

struct Edge {
    int to;
    double weight;
};

class Graph {
    std::unordered_map<std::string,int> airportToIndex;
    std::vector<std::string> indexToAirport;
    std::vector<std::vector<Edge>> adj;

public:
    /**
     * @brief Load airports from CSV.
     * Each line: id,name,city,country,IATA,...
     * Skips IATA="\\N" or empty.
     */
    void loadAirports(const std::string& filepath);

    /**
     * @brief Load routes from CSV.
     * @param mode 0 = distance (7th column), 1 = delay (8th column).
     * Default is 0 so graph.loadRoutes(path) still compiles.
     * CSV columns: airline,aid,src,srcid,dst,dstid,distance,delay,...
     */
    void loadRoutes(const std::string& filepath, int mode = 0);

    /// Get numeric index for an airport code, or -1 if unknown
    int getAirportIndex(const std::string& code) const;

    /// Get the IATA code for a given index, or "" if out of range
    std::string getAirportCode(int idx) const;

    /// Number of airports loaded
    int getNumAirports() const;

    /// Adjacency list for algorithms
    const std::vector<Edge>& getAdj(int u) const;

    /// Shortest path algorithms
    void dijkstra(const std::string& src, const std::string& dst);
    void bellmanFord(const std::string& src, const std::string& dst);
};
