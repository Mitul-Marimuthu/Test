// student id: 20538991

#include <iostream>
#include <vector>
#include <climits>
#include <cfloat>

#ifndef Graph_h
#define Graph_h

using namespace std;

class Graph {
    public:
        struct Edge {
            int dst;
            float wt;

            Edge(int tgt = -1, float w = 0) : dst(tgt), wt(w) {}
            bool operator==(const Edge &that) const { return dst == that.dst && wt == that.wt; }
            bool operator!=(const Edge &that) const { return dst != that.dst || wt != that.wt; }
        };

    protected:
        static double constexpr FLOOR = 1e-6;
        vector<vector<Edge>> _nodes;

    public:
        size_t get_num_nodes() const { return _nodes.size(); }
        bool is_empty() const { return _nodes.empty(); }
        void clear() { _nodes.clear(); }
        string to_string() const;

        Graph &add_edge(int src, int tgt, float wt, bool replace=true);
        float find_edge_weight(int src, int tgt) const;

        friend class Tests;
        friend class Gx;
};

#endif /* Graph_h */