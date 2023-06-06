#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <map>
#include <set>
#include <iomanip>

using namespace std;

bool is_number(const std::string &s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void get_number_convert(int &first, int &second) {
    string input;
    while (true) {
        getline(cin, input);
        string word;
        stringstream iss(input);
        bool isMinus = false;
        bool zero = false;
        while (iss >> word) {
            if (word[0] == '-' && word[1] == '1') {
                isMinus = true;
                word[0] = '0';
            }
            if (is_number(word)) {
                if (zero == 0) {
                    zero = true;
                    if (isMinus) {
                        first = -1 * stoi(word);
                    } else {
                        first = stoi(word);
                    }
                    if (first == -1)
                        return;
                } else {
                    second = stoi(word);
                    return;
                }
            }
        }
        cout << "please, do a correct int input" << '\n';
    }
}

void get_correct_direction(bool &get_correct_direction) {
    string input;
    while (true) {
        getline(cin, input);
        if (is_number(input)) {
            int n = stoi(input);
            if (n == 0 || n == 1) {
                get_correct_direction = (n % 2 == 0);
                return;
            } else
                cout << "please, do a correct boolean input" << '\n';
        } else {
            cout << "please, do a correct boolean input" << '\n';
        }
    }

}

bool isContainValue(const map<int, vector<int>>& graph, const int &finding_key) {
    bool is_Contain = false;
    for (const auto &[key, value]: graph) {
        if (finding_key == key) {
            is_Contain = true;
            break;
        }
    }
    if (is_Contain)
        return true;
    return false;
}

void DFS_strong_connected(const int v, map<int, vector<int>> &graph, map<int, bool> &mark) {
    mark[v] = true;
    for (auto neighbor: graph[v]) {
        if (mark[neighbor] != true) {
            DFS_strong_connected(neighbor, graph, mark); // Load from the another node
        }
    }
}

void printConnections(vector<vector<int>> &Connections) {
    cout << "Connections:\n";
    for (int i = 0; i < Connections.size(); i++) {
        cout << i + 1 << ") ";
        set<int> temp_set;
        for (int j : Connections[i]) {
            temp_set.insert(j);
        }
        for (auto const &j: temp_set) {
            cout << j << " ";
        }
        cout << '\n';
    }
    cout << '\n';
}

void DFS(const int v, map<int, vector<int>> &graph, map<int, bool> &mark, int &color, map<int, int> &colors,
         vector<int> &temp_connect) {
    mark[v] = true;
    colors[v] = color;
    temp_connect.push_back(v);
    for (const auto &value: graph[v]) // Foreach edge
    {
        if (mark[value] != 1) {
            temp_connect.push_back(value);
            DFS(value, graph, mark, color, colors, temp_connect); // Load from the another node
        }
    }
}

//only for the undirected graphs
int amountOfConnectivity(map<int, vector<int>> &graph, vector<vector<int>> &Connections) {
    int color = 1;
    map<int, int> colors;
    for (const auto &[key, value]: graph) {
        colors.insert(make_pair(key, 0));
    }
    map<int, bool> mark;
    for (const auto &[key, value]: graph) {
        mark.insert(make_pair(key, 0));
    }
    for (const auto &[key, value]: graph) {
        if (mark[key] != 1) {
            vector<int> temp_connect;
            DFS(key, graph, mark, color, colors, temp_connect);
            Connections.push_back(temp_connect);
            color++;
        }
    }
    set<int> count;
    for (const auto &[key, value]: colors) {
        count.insert(value);
    }
    return count.size();
}

//x_i connected with each of x_j, exists the only one connectivity component
bool isStrongConnection(map<int, vector<int>> &graph) {
    for (const auto &[key_external, value_external]: graph) {
        map<int, bool> mark;
        for (const auto &[key, value]: graph) {
            mark.insert(make_pair(key, 0));
        }
        DFS_strong_connected(key_external, graph, mark);
        for (const auto &[key, value]: mark) {
            if (mark[key] == false)
                return false;
        }
    }
    return true;
}

//x_i connected with each of x_j or the other way
bool isOneWayConnection(map<int, vector<int>> &graph) {
//DFS_Strong from external vertex(taking all marks) and merge marks with DFS_Strong ways from another.
    for (const auto &[key_external, value_external]: graph) {
        map<int, bool> temp_external_marks;
        for (const auto &[key, value]: graph) {
            temp_external_marks.insert(make_pair(key, false));
        }
        DFS_strong_connected(key_external, graph, temp_external_marks);
        bool is_strong_vertex = true;
        for (const auto &[key, value]: temp_external_marks) {
            if (temp_external_marks[key] == false) {
                is_strong_vertex = false;
                break;
            }
        }
        if (is_strong_vertex) {
            continue;
        }


        map<int, bool> temp_internal_marks;
        for (const auto &[key, value]: graph) {
            temp_internal_marks.insert(make_pair(key, false));
        }
        for (const auto &[key_internal, value_internal]: graph) {
            if (key_internal != key_external) {
                for (const auto &[key, value]: temp_internal_marks) {
                    temp_internal_marks[key] = false;
                }
                DFS_strong_connected(key_internal, graph, temp_internal_marks);
                if (temp_internal_marks[key_external]) {
                    temp_external_marks[key_internal] = true;
                }
            }
        }
        for (const auto &[key, value]: temp_external_marks) {
            if (!temp_external_marks[key])
                return false;
        }
    }
    return true;
}

//x_i connected with each of x_j provided the graph is becoming undirected
bool isWeak(map<int, vector<int>> &graph) {
    map<int, vector<int>> temp_graph;
    for (const auto &[key, values]: graph) {
        for (auto value: values) {
            if (temp_graph.contains(key)) {
                temp_graph[key].push_back(value);
            } else {
                temp_graph.insert(make_pair(key, vector<int>() = {value}));
            }
            if (key != value) {
                temp_graph[value].push_back(key);
            }
        }
    }
    vector<vector<int>> useful;
    if (amountOfConnectivity(temp_graph, useful) == 1)
        return true;
    return false;
};

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

void
print_incident_matrix(std::string_view comment, const map<int, vector<int>> &graph, bool isDirected, int countOfEdges,
                      vector<int> &vertecies, const map<int, vector<int>> &direct_graph_for_incident) {
    std::cout << comment << '\n';
    map<int, vector<int>> matrix;
    for (int & vertecie : vertecies) {
        matrix.insert(make_pair(vertecie, vector<int>(countOfEdges, 0)));
    }

    map<int, vector<int>> direct_graph;
    if (isDirected) {
        direct_graph = graph;
    } else {
        direct_graph = direct_graph_for_incident;
    }
    //to count all edges build undirected to directed, for one-way
    int curr_column = 0;
    for (const auto &[key, values]: direct_graph) {
        for (auto value: values) {
            if (value == key) {
                matrix[key][curr_column] = 2;
            } else {
                matrix[key][curr_column] = 1;
                if (isDirected) {
                    matrix[value][curr_column] = -1;
                } else {
                    matrix[value][curr_column] = 1;
                }
            }
            curr_column++;
        }
    }
    cout << " " << setw(4);
    for (int i = 0; i < countOfEdges; i++) {
        cout << setw(5) << i + 1;
    }
    cout << "\n";
    for (const auto &[key, values]: matrix) {
        cout << key << setw(5);
        for (auto value: values) {
            cout << value << setw(5);
        }
        cout << '\n';
    }
    std::cout << '\n';
}

int calculateCountOfVertices(map<int, vector<int>> &graph, vector<int> &vertecies) {
    set<int> vertecies_set;
    for (const auto &[key, value]: graph) {
        vertecies_set.insert(key);
        for (auto i: value)
            vertecies_set.insert(i);
    }
    for (const auto value: vertecies_set) {
        vertecies.push_back(value);
    }
    return vertecies_set.size();
}

int calculateCountOfLoops(map<int, vector<int>> &graph) {
    int count = 0;
    for (const auto &[key, value]: graph) {
        for (auto i: value) {
            if (key == i) {
                count++;
            }
        }
    }
    return count;
}

int calculateMaxDegreeOut(map<int, vector<int>> &graph) {
    int maxx = 0;
    for (const auto &[key, value]: graph) {
        int temp = 0;
        for (auto _: value) {
            temp++;
        }
        if (temp > maxx)
            maxx = temp;
    }
    return maxx;
}

int calculateMaxDegreeIn(map<int, vector<int>> &graph) {
    map<int, int> maxx_vals;
    for (const auto &[key, value]: graph) {
        maxx_vals.insert(make_pair(key, 0));
    }
    for (const auto &[key, value]: graph) {
        for (auto i: value) {
            maxx_vals[i]++;
        }
    }
    int maxx = 0;
    for (const auto &[key, value]: maxx_vals) {
        if (value > maxx)
            maxx = value;
    }
    return maxx;
}

int calculateMaxDegreeInAndOut(map<int, vector<int>> &graph) {
    int maxx = 0;
    for (const auto &[key, value]: graph) {
        int temp = 0;
        for (auto i: value) {
            temp++;
            if (i == key)
                temp++;
        }
        if (temp > maxx) {
            maxx = temp;
        }
    }
    return maxx;
}

int main() {
    cout << "DEVELOPER KHARITONOV 2012\n";
    map<int, vector<int>> graph, direct_graph_for_incident;
    cout << "Choose a type of graph(0 - Direct, 1 - Undirect):\n";
    bool isDirectedGraph = 0;
    get_correct_direction(isDirectedGraph);
    cout
            << "Enter edges with 2 positive integer nodes separated by a space, on one line you can put the only one edge. To finish an input put -1 in a first node.\n";
    int first, second;
    int countOfEdges = 0;
    while (true) {
        get_number_convert(first, second);
        if (first == -1) {
            break;
        }
        if (graph.contains(first)) {
            graph[first].push_back(second);
            direct_graph_for_incident[first].push_back(second);
        } else {
            graph.insert(make_pair(first, vector<int>() = {second}));
            direct_graph_for_incident.insert(make_pair(first, vector<int>() = {second}));
        }
        if (!isDirectedGraph && second != first) {
            graph[second].push_back(first);
        }
        countOfEdges++;
    }
    vector<int> vertecies;
    int countOfVertices = calculateCountOfVertices(graph, vertecies);
    int countOfLoops = calculateCountOfLoops(graph);

    print_incident_list("Your graph by an incident list:", graph);
    print_incident_matrix("Your graph by an incident_matrix:", graph, isDirectedGraph, countOfEdges, vertecies,
                          direct_graph_for_incident);
    cout << "Count Of Vertices:" << countOfVertices << '\n';
    cout << "Count Of Loops:" << countOfLoops << '\n';
    cout << "Count Of Edges:" << countOfEdges << '\n';
    if (isDirectedGraph) {
        cout << "Max degree of your directed graph is:" << '\n';
        cout << "In vertex:" << calculateMaxDegreeIn(graph) << '\n';
        cout << "Out of vertex:" << calculateMaxDegreeOut(graph) << '\n';
    } else {
        cout << "Max degree of your Undirected graph is:" << calculateMaxDegreeInAndOut(graph) << '\n';
    }
    if (!isDirectedGraph) {
        vector<vector<int>> Connections;
        int countConnections = amountOfConnectivity(graph, Connections);
        if (countConnections == 1) {
            cout << "Connected graph";
        } else {
            cout << "Unconnected graph";
        }
        cout << '\n';
        cout << "Connections count:" << countConnections << '\n';
        printConnections(Connections);
    } else {
        if (isStrongConnection(graph)) {
            cout << "Strong connected graph\n";
        } else if (isOneWayConnection(graph)) {
            cout << "One-way connected graph\n";
        } else if (isWeak(graph)) {
            cout << "Weak connected graph\n";
        } else {
            cout << "Unconnected graph\n";
        }
    }
    return 0;
}
