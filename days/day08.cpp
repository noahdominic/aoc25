#include "utils.hpp"
#include <algorithm>
#include <cmath>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

class Point3d {
public:
    double x;
    double y;
    double z;

    Point3d()
        : x(0)
        , y(0)
        , z(0) {}
    Point3d(double x_, double y_, double z_)
        : x(x_)
        , y(y_)
        , z(z_) {}

    double distanceTo(Point3d that) const {
        return sqrt((x - that.x) * (x - that.x) + (y - that.y) * (y - that.y) +
                    (z - that.z) * (z - that.z));
    }

    bool operator==(const Point3d& that) const {
        return x == that.x && y == that.y && z == that.z;
    }

    bool operator<(const Point3d& other) const {
        if (x != other.x)
            return x < other.x;
        if (y != other.y)
            return y < other.y;
        return z < other.z;
    }
};

std::ostream& operator<<(std::ostream& os, const Point3d& point) {
    os << "(" << point.x << ", " << point.y << ", " << point.z << ")";
    return os;
}

struct PointHash {
    size_t operator()(const Point3d& p) const {
        return std::hash<double>()(p.x) ^ std::hash<double>()(p.y) ^
               std::hash<double>()(p.z);
    }
};

struct Edge {
    std::pair<Point3d, Point3d> pointPair;
    double distance;
};

class DisjointSet {
public:
    std::unordered_map<Point3d, Point3d, PointHash> parent;
    std::unordered_map<Point3d, size_t, PointHash> size;

    Point3d find(const Point3d& x) {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            size[x] = 1;
        }
        if (!(parent[x] == x))
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(const Point3d& x, const Point3d& y) {
        Point3d rootX = find(x);
        Point3d rootY = find(y);
        if (!(rootX == rootY)) {
            // Merge smaller set into larger one for efficiency
            if (size[rootX] < size[rootY])
                std::swap(rootX, rootY);

            parent[rootY] = rootX;
            size[rootX] += size[rootY];
            size.erase(rootY); // rootY is no longer a root
        }
    }

    size_t getCircuitSize(const Point3d& x) {
        return size[find(x)];
    }
};

std::vector<Point3d> readPoints(const std::vector<std::string>& data) {
    std::vector<Point3d> points;
    std::transform(data.begin(), data.end(), std::back_inserter(points),
                   [](const std::string& s) {
                       std::vector<std::string> coords = utils::split(s, ",");
                       return Point3d(std::stod(coords[0]),
                                      std::stod(coords[1]),
                                      std::stod(coords[2]));
                   });
    return points;
}

long day08_part1() {
    const std::vector<std::string> data = utils::read_file("input/day08.txt");
    const std::vector<Point3d> points = readPoints(data);
    std::vector<Edge> edges;
    DisjointSet ds;
    std::map<Point3d, size_t> circuitSizes;
    int countdown = 1000;

    for (auto itFrom = points.begin(); itFrom + 1 != points.end(); ++itFrom) {
        for (auto itTo = itFrom + 1; itTo != points.end(); ++itTo) {
            edges.emplace_back((Edge){std::make_pair(*itFrom, *itTo),
                                      itFrom->distanceTo(*itTo)});
        }
    }

    std::sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {
        return a.distance < b.distance;
    });

    for (const auto& edge : edges) {
        ds.unite(edge.pointPair.first, edge.pointPair.second);
        --countdown;
        if (!countdown)
            break;
    }

    for (const auto& [key, value] : ds.parent) {
        circuitSizes[value] = ds.getCircuitSize(key);
    }

    size_t first = 0, second = 0, third = 0;

    for (const auto& [key, value] : circuitSizes) {
        if (value > first) {
            third = second;
            second = first;
            first = value;
        } else if (value > second) {
            third = second;
            second = value;
        } else if (value > third) {
            third = value;
        }
    }

    return first * second * third;
}

long day08_part2() {
    std::vector<std::string> data = utils::read_file("input/day08.txt");
    std::vector<Point3d> points = readPoints(data);
    std::vector<Edge> edges;
    DisjointSet ds;

    // Calculate distances
    for (auto itFrom = points.begin(); itFrom + 1 != points.end(); ++itFrom) {
        for (auto itTo = itFrom + 1; itTo != points.end(); ++itTo) {
            double distance = itFrom->distanceTo(*itTo);
            edges.emplace_back(
                (Edge){std::make_pair(*itFrom, *itTo), distance});
        }
    }

    std::sort(edges.begin(), edges.end(), [](const auto& a, const auto& b) {
        return a.distance < b.distance;
    });

    for (const auto& edge : edges) {
        ds.unite(edge.pointPair.first, edge.pointPair.second);
        // In case I read this and get confused in the future:
        // There is no need to check that there is only one set.   Just that
        // the first one you find contains all the items.
        if (ds.getCircuitSize(edge.pointPair.first) == points.size()) {
            return static_cast<long>(edge.pointPair.first.x) *
                   static_cast<long>(edge.pointPair.second.x);
        }
    }

    return -1; // something's wrong
}
