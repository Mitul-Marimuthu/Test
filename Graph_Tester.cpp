#include <iostream>
#include <vector>
#include "Graph.h"
#include "Graph_Algorithms.h"

using namespace std;

int main() {
    Graph g;
    g.add_edge(10,12,1012, true);
    g.add_edge(12,0,1200,true);
    // g.add_edge(3,1,301,true);
    // g.add_edge(3,9,309,true);
    // g.add_edge(4,3,403,true);
    // g.add_edge(5,8,508,true);
    // g.add_edge(7,3,703,true);
    // g.add_edge(7,6,706,true);
    // g.add_edge(7,0,700,true);
    // g.add_edge(8,9,1618,true);
    // g.add_edge(8,6,806,true);
    // g.add_edge(8,5,805,true);
    // g.add_edge(8,1,801,true);
    // g.add_edge(9,0,900,true);
    // g.add_edge(9,2,902,true);
    // g.add_edge(12,15,1215,true);
    // g.add_edge(13,3,1303,true);
    // g.add_edge(12,17,1217,true);
    // g.add_edge(13,2,1302,true);
    // g.add_edge(13,15,1314,true);
    // g.add_edge(14,15,1415,true);
    // g.add_edge(15,16,1516,true);
    // g.add_edge(15,3,1503,true);
    // g.add_edge(15,1,1501,true);
    // g.add_edge(16,6,3211,true);
    // g.add_edge(16,3,3206,true);
    // g.add_edge(16,17,1617,true);
    // g.add_edge(16,18,3236,true);
    // g.add_edge(16,2,1602,true);
    // g.add_edge(17,6,1706,true);
    // g.add_edge(18,7,1807,true);
    // g.add_edge(18,5,1805,true);
    // g.add_edge(15,2,1502,true);
    // g.add_edge(16,1,1601,true);
    // g.add_edge(17,9,1709,true);
    cout << g.to_string() << endl;
    vector<int> path;
    float flow = Gx::get_max_flow(g, 10, 0);
    cout << flow << endl;
    //size_t t = Gx::get_shortest_unweighted_path(g, 8,3,path);
    // for (int i : path) cout << i << " ";
    // cout << endl;
}