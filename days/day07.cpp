#include <string>
#include <vector>
#include <iostream>
#include <bitset>
#include <algorithm>
#include "utils.hpp"
#include <set>
#include <unordered_map>

#define EMPTY_SPACE '.'
#define SOURCE 'S'
#define SPLITTER '^'
#define LIGHT '|'

long
day07_part1()
{
    std::vector<std::string> data = utils::read_file("input/day07.txt");
    std::set<size_t> light_idxs;

    // Find the initial source position
    const size_t source_pos = data[0].find(SOURCE);
    if (source_pos != std::string::npos) {
        light_idxs.insert(source_pos);
    }

    long splitter_count = 0;

    for (size_t scan_idx = 1; scan_idx < data.size(); ++scan_idx) {
        std::set<size_t> splitter_idxs;

        // Identify splitter positions in the current row
        for (size_t light_idx : light_idxs) {
            if (data[scan_idx][light_idx] == SPLITTER) {
                splitter_idxs.insert(light_idx);
            }
        }

        // Process splitters
        for (size_t splitter_idx : splitter_idxs) {
            if (light_idxs.count(splitter_idx)) {
                ++splitter_count;
                light_idxs.insert(splitter_idx - 1);
                light_idxs.insert(splitter_idx + 1);
                light_idxs.erase(splitter_idx);
            }
        }
    }

    return splitter_count;
}

struct Vertex
{
    size_t x;
    size_t y;

    bool operator<(const Vertex& other) const {
        if (x != other.x) return x < other.x;
        return y < other.y;
    }

    bool operator==(const Vertex& other) const {
        return x == other.x && y == other.y;
    }
};

// Hash function for Vertex
struct VertexHash {
    size_t operator()(const Vertex& v) const {
        return std::hash<size_t>()(v.x) ^ std::hash<size_t>()(v.y);
    }
};

long
dfs(Vertex current,
    std::unordered_map<Vertex, std::set<Vertex>, VertexHash>& graph,
    std::vector<Vertex>& targets,
    std::unordered_map<Vertex, long, VertexHash>& memo)
{
    // If we've already computed the number of paths from this vertex, return it
    auto memo_it = memo.find(current);
    if (memo_it != memo.end()) {
        return memo_it->second;
    }

    // Base case. Check if current vertex is in targets
    for (const auto& target : targets) {
        if (current == target) {
            memo[current] = 1;
            return 1;
        }
    }

    long count = 0;
    auto graph_it = graph.find(current);
    if (graph_it != graph.end()) {
        for (const auto& neighbour : graph_it->second) {
            count += dfs(neighbour, graph, targets, memo);
        }
    }

    memo[current] = count;
    return count;
}

long
count_paths_to_all_lowest_row(Vertex source,
    std::unordered_map<Vertex, std::set<Vertex>, VertexHash> adjacency_graph,
    std::vector<Vertex> targets)
{
    std::unordered_map<Vertex, long, VertexHash> memo;
    return dfs(source, adjacency_graph, targets, memo);
}

long
day07_part2()
{
    std::vector<std::string> data = utils::read_file("input/day07.txt");
    std::unordered_map<Vertex, std::set<Vertex>, VertexHash> adjacency_graph;

    std::set<size_t> light_idxs;

    // Find the initial source position
    const size_t source_pos = data[0].find(SOURCE);
    if (source_pos != std::string::npos) {
        light_idxs.insert(source_pos);
    }

    long splitter_count = 0;

    for (size_t scan_idx = 1; scan_idx < data.size(); ++scan_idx) {
        std::set<size_t> splitter_idxs;

        // Identify splitter positions in the current row
        for (size_t light_idx : light_idxs) {
            if (data[scan_idx][light_idx] == SPLITTER) {
                splitter_idxs.insert(light_idx);
            }
        }

        // Process splitters
        for (size_t splitter_idx : splitter_idxs) {
            if (light_idxs.count(splitter_idx)) {
                ++splitter_count;

                // Insert new light positions if within bounds
                if (splitter_idx > 0) {
                    light_idxs.insert(splitter_idx - 1);
                    adjacency_graph[Vertex{scan_idx - 1, splitter_idx}].insert(Vertex{scan_idx, splitter_idx - 1});
                    data[scan_idx][splitter_idx - 1] = LIGHT;

                }
                if (splitter_idx + 1 < data[0].size()) {
                    light_idxs.insert(splitter_idx + 1);
                    adjacency_graph[Vertex{scan_idx - 1, splitter_idx}].insert(Vertex{scan_idx, splitter_idx + 1});
                    data[scan_idx][splitter_idx + 1] = LIGHT;

                }

                light_idxs.erase(splitter_idx);
            }
        }

        // Connect unsplit lights to the next row
        for (size_t light_idx : light_idxs) {
            if (splitter_idxs.count(light_idx) == 0) {
                if (data[scan_idx-1][light_idx] == LIGHT || data[scan_idx-1][light_idx] == SOURCE)
                {
                    data[scan_idx][light_idx] = LIGHT;
                    adjacency_graph[Vertex{scan_idx - 1, light_idx}].insert(Vertex{scan_idx, light_idx});
                
                }
            }
        }
    }

    std::vector<Vertex> targets;

    for (size_t col = 0; col < data[0].size(); ++col) {
        if (data[data.size() - 1][col] == LIGHT) {
            targets.push_back(Vertex{data.size() - 1, col});
        }
    }

    return count_paths_to_all_lowest_row(Vertex{0, source_pos}, adjacency_graph, targets);
}