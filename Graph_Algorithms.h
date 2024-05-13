//student id: 20538991

#include <iostream>
#include <vector>
#include "Graph.h"

#ifndef Graph_Algorithms_h
#define Graph_Algorithms_h

class Gx {
    private: 
        struct NW {
            int node, pred;
            float weight;
            NW(int n = -1, int m = -1, float wt = -1) : node(n), pred(m), weight(wt) {}
            bool operator<(const NW &that) const { return this->weight > that.weight; }
            bool operator>(const NW &that) const { return this->weight < that.weight; }
            bool operator==(const NW &that) const { return this->node == that.node; }
        };

        static float _get_capacity_of_this_path(const Graph &g, const vector<int> &path);
        static float _get_max_capacity_path(const Graph &g, int src, int dst, vector<int> &path);
        static bool _is_cyclic(const Graph &g, size_t node, vector<bool> seen, vector<bool>& cycle_free);
        static float dfs(Graph &flow, Graph &residual, int src, int dst, vector<int> path, 
            vector<bool> &seen, vector<bool> &_leads_nowhere);

    public:
        static bool is_cyclic(const Graph &g);
        static bool prune_unreachables(Graph &g, int src);
        static size_t get_shortest_unweighted_path(const Graph &g, int src, int dst, vector<int> &path);
        static size_t get_shortest_weighted_path(const Graph &g, int src, int dst, vector<int> &path);

        static float get_max_flow(const Graph &g, int src, int dst);

        friend class Tests;
};

#endif /* Graph_Algoritms_h */