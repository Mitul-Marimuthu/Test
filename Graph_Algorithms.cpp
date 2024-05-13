//student id: 20538991

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include "Graph_Algorithms.h"
#include "Graph.h"
 
using namespace std;

float Gx::_get_max_capacity_path(const Graph &g, int src, int dst, vector<int> &path) {
    if (src == dst) return 1;
    //if ()
    vector<Gx::NW> nodes_visited;
    nodes_visited.push_back(Gx::NW(src,src,1));
    priority_queue<Gx::NW> processed;
    path.clear();
    for (size_t i = 0; i < g._nodes[src].size(); ++i) {
        if (g._nodes[src][i].wt <= 0) continue;
        processed.push(NW(g._nodes[src][i].dst, src, g._nodes[src][i].wt));
    }
    while (!processed.empty() && nodes_visited.size() != g._nodes.size()) {
        NW temp = processed.top();
        processed.pop();
        if (std::find(nodes_visited.begin(), nodes_visited.end(), temp) == nodes_visited.end()) {
            nodes_visited.push_back(temp);
        }
        else continue;
        if (temp.node == dst) break;
        for (size_t i = 0; i < g._nodes[temp.node].size(); ++i) {
            if (g._nodes[temp.node][i].wt <= 0) continue;
            Gx::NW t (g._nodes[temp.node][i].dst, temp.node, temp.weight+g._nodes[temp.node][i].wt);
            if (std::find(nodes_visited.begin(), nodes_visited.end(), t) == nodes_visited.end())
                processed.push(t);
        }
    //return 1;
    }
    cout << nodes_visited.size() << endl;
    if (nodes_visited.empty() || nodes_visited[nodes_visited.size() -1].node != dst) return -1;
     auto index = nodes_visited.end() -1;
     float total = index->weight;
    while(index != nodes_visited.end() && index->node != src) {
        path.push_back(index->node);
        index = std::find(nodes_visited.begin(), nodes_visited.end(), index->pred);
    }
    //cout << "first loop not" << endl;
    path.push_back(src);
    for (size_t i = 0; i < path.size()/2; ++i) {
        int temp = path[i];
        path[i] = path[path.size()-1-i];
        path[path.size()-1-i] = temp;
    }
    return total;
}

bool Gx::_is_cyclic(const Graph &g, size_t node, vector<bool> seen, vector<bool>& cycle_free) {
    if (cycle_free[node]) return false;
    if (seen[node]) return true;
    if (g._nodes[node].size() == 0) return false;
    for (auto it = g._nodes[node].begin(); it != g._nodes[node].end(); ++it) {
        seen[node] = true;
        bool b = _is_cyclic(g, it->dst, seen, cycle_free);
        if (b) return true;
    }
    return false;
}

bool Gx::is_cyclic(const Graph &g) {
    vector<bool> seen(g._nodes.size());
    vector<bool> cycle_free(g._nodes.size());
    for (size_t i = 0; i < g._nodes.size(); ++i) {
        bool b = _is_cyclic(g, i, seen, cycle_free);
        if (b) return true;
        else cycle_free[i] = true;
    }
    return false;
}

bool Gx::prune_unreachables(Graph &g, int src) {
    if (src < 0 || src >= (int)(g._nodes.size())) return false;
    vector<bool> nodes_visited(g._nodes.size());
    queue<int> needs_checking;
    needs_checking.push(src);
    // nodes_visited[src] = true;
    while (!needs_checking.empty()) {
        int top = needs_checking.front();
        needs_checking.pop();
        for (auto it = g._nodes[top].begin(); it != g._nodes[top].end(); ++it) {
            if (nodes_visited[it->dst]) continue;
            needs_checking.push(it->dst);
        }
        nodes_visited[top] = true;
    }
    for (size_t i = 0; i < g._nodes.size(); ++i) {
        if (!nodes_visited[i]) g._nodes[i].clear();
    } 
    return true;
}

size_t Gx::get_shortest_unweighted_path(const Graph &g, int src, int dst, vector<int> &path) {
    if (src == dst) return 1;
    //if ()
    vector<Gx::NW> nodes_visited;
    nodes_visited.push_back(Gx::NW(src,src,1));
    queue<Gx::NW> processed;
    path.clear();
    for (size_t i = 0; i < g._nodes[src].size(); ++i) {
        processed.push(NW(g._nodes[src][i].dst, src, 1));
    }
    while (!processed.empty() && nodes_visited.size() != g._nodes.size()) {
        NW temp = processed.front();
        processed.pop();
        if (std::find(nodes_visited.begin(), nodes_visited.end(), temp) == nodes_visited.end()) {
            nodes_visited.push_back(temp);
        }
        else continue;
        if (temp.node == dst) break;
        for (size_t i = 0; i < g._nodes[temp.node].size(); ++i) {
            Gx::NW t (g._nodes[temp.node][i].dst, temp.node, temp.weight+1);
            if (std::find(nodes_visited.begin(), nodes_visited.end(), t) == nodes_visited.end())
                processed.push(t);
        }
    }
    //cout << nodes_visited.size() << endl;
    if (nodes_visited.empty() || nodes_visited[nodes_visited.size() -1].node != dst) return string::npos;
    auto index = nodes_visited.end() -1;
    while(index != nodes_visited.end() && index->node != src) {
        path.push_back(index->node);
        index = std::find(nodes_visited.begin(), nodes_visited.end(), index->pred);
    }
    //cout << "first loop not" << endl;
    path.push_back(src);
    for (size_t i = 0; i < path.size()/2; ++i) {
        int temp = path[i];
        path[i] = path[path.size()-1-i];
        path[path.size()-1-i] = temp;
    }
    return path.size();
}

size_t Gx::get_shortest_weighted_path(const Graph &g, int src, int dst, vector<int> &path) {
    if (src == dst) return 1;
    //if ()
    vector<Gx::NW> nodes_visited;
    nodes_visited.push_back(Gx::NW(src,src,1));
    priority_queue<Gx::NW> processed;
    path.clear();
    for (size_t i = 0; i < g._nodes[src].size(); ++i) 
        processed.push(NW(g._nodes[src][i].dst, src, g._nodes[src][i].wt));
    while (!processed.empty() && nodes_visited.size() != g._nodes.size()) {
        NW temp = processed.top();
        processed.pop();
        if (std::find(nodes_visited.begin(), nodes_visited.end(), temp) == nodes_visited.end()) {
            nodes_visited.push_back(temp);
        }
        else continue;
        if (temp.node == dst) break;
        for (size_t i = 0; i < g._nodes[temp.node].size(); ++i) {
            Gx::NW t (g._nodes[temp.node][i].dst, temp.node, temp.weight+g._nodes[temp.node][i].wt);
            if (std::find(nodes_visited.begin(), nodes_visited.end(), t) == nodes_visited.end())
                processed.push(t);
        }
    }
    //cout << nodes_visited.size() << endl;
    if (nodes_visited.empty() || nodes_visited[nodes_visited.size() -1].node != dst) return string::npos;
    auto index = nodes_visited.end() -1;
    //size_t total = index->weight;
    while(index != nodes_visited.end() && index->node != src) {
        path.push_back(index->node);
        index = std::find(nodes_visited.begin(), nodes_visited.end(), index->pred);
    }
    //cout << "first loop not" << endl;
    path.push_back(src);
    for (size_t i = 0; i < path.size()/2; ++i) {
        int temp = path[i];
        path[i] = path[path.size()-1-i];
        path[path.size()-1-i] = temp;
    }
    return path.size();
}

float Gx::get_max_flow(const Graph &g, int src, int dst) {
    if (src < 0 || src >= (int)(g._nodes.size())) return 0;
    if (dst < 0 || src >= (int)(g._nodes.size())) return 0;
    if (src == dst) return 0;
    //Graph flow;
    Graph residual;
    float maxcap = 0;
    //cout << g.to_string() << endl;
    for (size_t i = 0; i < g._nodes.size(); ++i){
        for (size_t j = 0; j < g._nodes[i].size(); ++j) {
            //flow.add_edge(i,g._nodes[i][j].dst,0,false);
            residual.add_edge(i,g._nodes[i][j].dst,g._nodes[i][j].wt,false);
            //residual.add_edge(g._nodes[i][j].dst,i,0,false);
            if (g._nodes[i][j].dst == dst)
                maxcap += g._nodes[i][j].wt;
        }
    }
    //cout << "flow: " << flow.to_string() << endl;
    //cout << "residual: " << residual.to_string() << endl;
    vector<int> path;
    //prune_unreachables(residual, src);
    //float ret = 0;
    float temp = _get_max_capacity_path(residual, src, dst, path);
    //cout << temp;
    float flow = 0;
    while (flow < maxcap && temp > 0) {
        float mini = Gx::_get_capacity_of_this_path(residual, path);
        for (size_t i = 0; i < path.size() -1; ++i) {
            //cout << "1" << path[i] << " " << path[i+1] << endl;
            residual.add_edge(path[i], path[i+1], (mini*-1), false);
            //cout << "2" << endl;
            residual.add_edge(path[i+1], path[i], mini, false);
            //cout << "3" << endl;
            //flow.add_edge(path[i], path[i+1], mini, false);
        }
        cout << residual.to_string() << endl;
        //cout << mini << endl;
        flow += mini;
        temp = _get_max_capacity_path(residual, src, dst, path);
        //prune_unreachables(residual, src);
    }
    return flow;
    // vector<bool> seen(g._nodes.size());
    // vector<bool> ln(g._nodes.size());
    // return dfs(flow, residual, src, dst, path, seen, ln);
}

float Gx::dfs(Graph &flow, Graph &residual, int src, int dst, vector<int> path, 
    vector<bool> &seen, vector<bool> &_leads_nowhere) {
    cout << src << " " << " " << seen[src] << endl;
    if (src == dst) {
        //cout << "found" << endl;
        path.push_back(src);
        //cout << residual.to_string() << endl;
        //for (int i : path) ;
        cout << endl;
        float mini = Gx::_get_capacity_of_this_path(residual, path);
        //cout << "done" << endl;
        for (size_t i = 0; i < path.size() -1; ++i) {
            //cout << "1" << path[i] << " " << path[i+1] << endl;
            residual.add_edge(path[i], path[i+1], (mini*-1), false);
            //cout << "2" << endl;
            residual.add_edge(path[i+1], path[i], mini, false);
            //cout << "3" << endl;
            //flow.add_edge(path[i], path[i+1], mini, false);
        }
        //cout << residual.to_string() << endl;
        // for (size_t i = path.size() -1; i > 0; --i) {
        //     residual._nodes[i][i-1].wt+= mini;
        // }
        //cout << "leaving "  << mini << endl;
        
        // for (int i : path) cout << i << " ";
        //     cout << endl;
        return mini;
    }
    //cout << residual.to_string() << endl;
    float ret = 0;
    bool only_reverse = true;
    for (size_t i = 0; i < residual._nodes[src].size(); i++) {
        if (residual.find_edge_weight(src, residual._nodes[src][i].dst) != 0) {
            only_reverse = false;
            break;
        }
    }
    if (seen[src] || only_reverse) {
        cout << "nothing" << endl;
        _leads_nowhere[src] = true;
        return 0;
    }
    //if (seen[src]) return 0;
    if (_leads_nowhere[src]) return 0; 
    else {
        path.push_back(src);
        //seen[src] = true;
        for (size_t i = 0; i < residual._nodes[src].size(); ++i) {
            // cout << "front" << endl;
            // for (int i : path) cout << i << " ";
            // cout << endl;
            cout << src << " " << residual._nodes[src][i].dst <<" " << residual._nodes[src][i].wt << endl;
            if (residual.find_edge_weight(src, residual._nodes[src][i].dst) == 0) continue;
            if (_leads_nowhere[residual._nodes[src][i].dst]) continue;
            cout << "passed" << endl;
            //path.push_back(residual._nodes[src][i].dst);
            seen[src] = true;
            double d = dfs(flow, residual, residual._nodes[src][i].dst, dst, path, seen, _leads_nowhere);
            ret += d;
            seen[src] = false;
            //if (d != 0)
            for (int i : path) _leads_nowhere[i] = false;
            //cout << residual.to_string() << endl;
            // path.pop_back();
            // path.push_back(src);
            //cout << ret << endl;
            //cout << "back" << endl;
        }
    }
    return ret;
}

float Gx::_get_capacity_of_this_path(const Graph &g, const vector<int> &path) {
    if (path.size() <= 1) return 0;
    // for (int i : path) cout << i << " ";
    // cout << endl;
    //cout << g.to_string() << endl;
    float mini = g.find_edge_weight(path[0],path[1]);
    for (size_t i = 1; i < path.size() -1; ++i) {
        //cout << "Edge : " << path[i] << " " << path[i+1] << " num: " << mini << endl;
        //cout << "Next weight: " <<
        mini = min(mini, g.find_edge_weight(path[i],path[i+1]));
    }
    return mini;
}