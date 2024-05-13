// student id: 20538991

#include <iostream>
#include <vector>
#include <climits>
#include <cfloat>
#include <sstream>
#include "Graph.h"

using namespace std;

Graph &Graph::add_edge(int src, int tgt, float wt, bool replace) {
    if (src == tgt)  { 
        if (_nodes.size() <= (size_t)(src))
            _nodes.resize(src + 1); 
        return *this; 
    }
    if (_nodes.size() <= (size_t)(src)) _nodes.resize(src + 1);
    if (_nodes.size() <= (size_t)(tgt)) _nodes.resize(tgt + 1);
    vector<Graph::Edge> &v = _nodes.at(src);
    //auto it;
    Graph::Edge e(tgt,wt);
    for (auto it = v.begin(); it != v.end(); ++it) {
        if(it->dst == e.dst) {
            if (replace) it->wt = wt;
            else it->wt += wt;
            return *this;
        }
    }
    v.push_back(e);
    return *this;
}

float Graph::find_edge_weight(int src, int tgt) const {
    if (_nodes.size() <= (size_t)(src)) return Graph::FLOOR;
    //vector<Graph::Edge> &v = _nodes.at(src);
    for (auto it = _nodes.at(src).begin(); it != _nodes.at(src).end(); ++it) {
        if (it->dst == tgt) return it->wt;
    }
    return Graph::FLOOR;
}

string Graph::to_string() const {
    stringstream ret;
    ret << "# Graph - " << get_num_nodes() << " nodes." << "\n";
    ret << "# Edge lists:" << "\n";
    for (size_t i = 0; i < get_num_nodes(); ++i) {
        if (_nodes.at(i).begin() != _nodes.at(i).end()) {
            ret << i << " : ";
        }
        for (auto it = _nodes.at(i).begin(); it != _nodes.at(i).end(); ++it) {
            ret << "(" << it->dst << "," << it->wt << ")";
            if (++it == _nodes.at(i).end()) break;
            else {
                ret << " ";
                --it;
            }
        }
        if (_nodes.at(i).begin() != _nodes.at(i).end()) {
            ret << "\n";
        }
    }
    ret << "# End of Graph\n";
    return ret.str();
}