#include <iostream>
#include <vector>
#include <string_view>
#include <map>
#include <set>
#include <utility>

#define INT_MAX 10000000

using namespace std;

int calculateCountOfVertices(map<int, vector<int>> &graph) {
    set<int> vertices_set;
    for (const auto &[key, value]: graph) {
        vertices_set.insert(key);
        for (auto i: value)
            vertices_set.insert(i);
    }
    return vertices_set.size();
}

void print_incident_list(std::string_view comment, const map<int, vector<int>> &m) {
    std::cout << comment << '\n';
    for (const auto &[key, value]: m) {
        std::cout << '[' << key << "] = ";
        for (auto i: value)
            cout << i << "; ";
        cout << '\n';
    }

    std::cout << '\n';
}

struct edge
{
    int to;
    float length;
};

using node = std::vector<edge>;
using graph = std::vector<node>;
void add_edge( graph& g, int start, int finish, float length ) {
    if ((int)g.size() <= (std::max)(start, finish))
        g.resize( (std::max)(start,finish)+1 );
    g[start].push_back( {finish, length} );
    g[finish].push_back( {start, length} );
}

using path = std::vector<int>;

struct result {
    float distance;
    path p;
};
result dijkstra(const graph &graph, int source, int target) {
    std::vector<float> min_distance( graph.size(), INT_MAX );
    min_distance[ source ] = 0;
    std::set< std::pair<int,int> > active_vertices;
    active_vertices.insert( {0,source} );

    while (!active_vertices.empty()) {
        int where = active_vertices.begin()->second;
        if (where == target)
        {
            float cost = min_distance[where];
            // std::cout << "cost is " << cost << std::endl;
            path p{where};
            while (where != source) {
                int next = where;
                for (edge e : graph[where])
                {
                    // std::cout << "examine edge from " << where << "->" << e.to << " length " << e.length << ":";

                    if (min_distance[e.to] == INT_MAX)
                    {
                        // std::cout << e.to << " unexplored" << std::endl;
                        continue;
                    }

                    if (e.length + min_distance[e.to] != min_distance[where])
                    {
                        // std::cout << e.to << " not on path" << std::endl;
                        continue;
                    }
                    next = e.to;
                    p.push_back(next);
                    // std::cout << "backtracked to " << next << std::endl;
                    break;
                }
                if (where==next)
                {
                    // std::cout << "got lost at " << where << std::endl;
                    break;
                }
                where = next;
            }
            std::reverse( p.begin(), p.end() );
            return {cost, std::move(p)};
        }
        active_vertices.erase( active_vertices.begin() );
        for (auto ed : graph[where])
            if (min_distance[ed.to] > min_distance[where] + ed.length) {
                active_vertices.erase( { min_distance[ed.to], ed.to } );
                min_distance[ed.to] = min_distance[where] + ed.length;
                active_vertices.insert( { min_distance[ed.to], ed.to } );
            }
    }
    return {INT_MAX};
}

int main() {
    cout << "DEVELOPER KHARITONOV 2012\n";
    graph g;
    map<int, vector<int>> graph_by_incident_list;
    cout
            << "Enter edges with 2 positive integer nodes and float weight separated by a space, on one line you can put the only one edge. To finish an input put -1 in a first node.\n"
               "Example:1 2 3 means node 1 to node 2 connected by edge with weight = 3\n"
               "\nPlease, enter vertices from the set of natural numbers sequentially, otherwise output will be invalid:\n"
               "For example: 1 2 10 (edge 1->2 with weight 10)\n"
               "             2 3 15 (edge 2->3 with weight 15)\n"
               "             4 5 20 (edge 4->5 with weight 20, another component of connectivity)\n"
               "             and so on ... Until -1 (input endpoint)\n";
    int first, second;
    float weight;
    int countOfEdges = 0;
    while (true) {
        cin >> first;
        if (first == -1)
            break;
        cin >> second;
        if (second == -1)
            break;
        cin >> weight;
        if (weight == -1) {
            break;
        }

        if (graph_by_incident_list.contains(first)) {
            graph_by_incident_list[first].push_back(second);
        } else {
            graph_by_incident_list.insert(make_pair(first, vector<int>() = {second}));
        }
        add_edge(g, first, second, weight);
        countOfEdges++;
    }
    int countOfVertices = calculateCountOfVertices(graph_by_incident_list);
    print_incident_list("Your graph by an incident list:", graph_by_incident_list);

    cout << "Enter a source:\n";
    int st;
    cin >> st;

    st--;
    for (int i = 1; i < countOfVertices+1; i++){
        if (i!=st+1){
            auto r = dijkstra(g, st+1, i);
            if (r.distance != INT_MAX){
                std::cout << "min path from " << st+1 << " to "<< i << " = " << r.distance << ": ";
                for (int x:r.p) {
                    std::cout << x;
                    if (x!=i){
                        cout << " -> ";
                    }
                }
            }
            else{
                cout << "path from " << st+1 << " to "<< i << " doesn't exist :(";
            }

            std::cout << "\n";
        }
    }
    return 0;
}