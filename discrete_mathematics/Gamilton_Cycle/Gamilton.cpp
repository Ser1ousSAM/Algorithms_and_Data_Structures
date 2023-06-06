//C++20 version
#include <iostream>
#include <vector>
#include <string>
#include <string_view>
#include <sstream>
#include <map>
#include <set>
#include <stack>

using namespace std;

bool is_number(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

void get_number_convert(int& first, int& second) {
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
                    }
                    else {
                        first = stoi(word);
                    }
                    if (first == -1)
                        return;
                }
                else {
                    second = stoi(word);
                    return;
                }
            }
        }
        cout << "please, do a correct int input" << '\n';
    }
}

void get_correct_direction(bool& get_correct_direction) {
    string input;
    while (true) {
        getline(cin, input);
        if (is_number(input)) {
            int n = stoi(input);
            if (n == 0 || n == 1) {
                get_correct_direction = (n % 2 == 0);
                return;
            }
            else
                cout << "please, do a correct boolean input" << '\n';
        }
        else {
            cout << "please, do a correct boolean input" << '\n';
        }
    }

}


void print_graph(std::string_view comment, const map<int, vector<int>>& m) {
    std::cout << comment << '\n';
    for (const auto& [key, value] : m) {
        std::cout << '[' << key << "] = ";
        for (auto i : value)
            cout << i << "; ";
        cout << '\n';
    }

    std::cout << '\n';
}

void print_Hamiltonian(vector<stack<int>>& all_cycles) {
    vector<stack<int>> temp_stacks;
    for (auto i : all_cycles) {
        stack<int>temp_stack;
        while (!i.empty()) {
            temp_stack.push(i.top());
            i.pop();
        }
        temp_stacks.push_back(temp_stack);
    }
    vector<string>cycles_with_cyclic_shift;
    vector<pair<vector<int>, bool>>answers_without_shifts;
    for (auto i : temp_stacks) {
        string temp_str;
        vector<int> temp_numbers;
        while (!i.empty()) {
            temp_numbers.push_back(i.top());
            temp_str += to_string(i.top());
            i.pop();
        }
        answers_without_shifts.emplace_back(temp_numbers, true);
        cycles_with_cyclic_shift.push_back(temp_str);
    }
    for (int i = 0; i < cycles_with_cyclic_shift.size(); i++) {
        for (int j = i + 1; j < cycles_with_cyclic_shift.size(); j++) {
            if ((cycles_with_cyclic_shift[i] + cycles_with_cyclic_shift[i]).find(cycles_with_cyclic_shift[j]) != std::string::npos) {//with shift
                answers_without_shifts[i].second = false;
                break;
            }
        }
    }
    for (const auto& i : answers_without_shifts) {
        if (i.second) {
            for (auto j : i.first) {
                cout << j << " ";
            }
            cout << '\n';
        }
    }
}

void ham(int& start_point, const int u, map<int, bool>& vis, int& count, map<int, vector<int>>& graph, stack<int> hamiltonian_cycle,
    vector<stack<int>>& all_cycles) {
    vis[u] = true;
    count++;
    hamiltonian_cycle.push(u);
    for (const auto& v : graph[u]) {
        if (!vis[v]) {
            ham(start_point, v, vis, count, graph, hamiltonian_cycle, all_cycles);
        }
        if (v == start_point && count == vis.size()) {
            all_cycles.push_back(hamiltonian_cycle);
        }
    }
    vis[u] = false;
    hamiltonian_cycle.pop();
    count--;
}

void Find_Hamiltonians(map<int, vector<int>>& graph, vector<stack<int>>& all_cycles) {
    for (const auto& [key, values] : graph) {
        int count = 0;
        stack<int>hamiltonian_cycle;
        map<int, bool> vis;
        for (const auto& [key1, value1] : graph) {
            vis.insert(make_pair(key1, 0));
        }
        int start_point = key;
        ham(start_point, key, vis, count, graph, hamiltonian_cycle, all_cycles);
    }
}


//Теорема Дирака - её используем
//Если n⩾3 и deg v⩾n/2 для любой вершины v неориентированного графа G, то G — гамильтонов граф.

//Теорема Оре
//Если n⩾3 и deg u+deg v⩾n для любых двух различных несмежных вершин u и v неориентированного графа G, то G — гамильтонов граф.

int main() {
    cout << "KHARITONOV DEVELOPER  2012\n";
    map<int, vector<int>> graph;
    cout << "Choose a type of graph(0 - Direct, 1 - Undirect):\n";
    bool isDirectedGraph = false;
    get_correct_direction(isDirectedGraph);
    cout << "Enter edges with 2 positive integer nodes separated by a space, on one line you can put the only one edge. To finish an input put -1 in a first node.\n";
    int first, second;
    while (true) {
        get_number_convert(first, second);
        if (first == -1) {
            break;
        }
        if (graph.contains(first)) {
            graph[first].push_back(second);
        }
        else {
            graph.insert(make_pair(first, vector<int>() = { second }));
        }
        if (!isDirectedGraph && second != first) {
            graph[second].push_back(first);
        }
    }
    if(graph.empty()){
        cout << "No graph => No cycles => no Hamilton :D\n";
    }else{
        print_graph("Your graph by a list of vertices:", graph);
        vector<stack<int>> all_cycles;
        Find_Hamiltonians(graph, all_cycles);
        if (all_cycles.empty() || (graph.size()==2 && !isDirectedGraph))
            cout << "No cycles, no Hamilton :D\n";
        else {
            print_Hamiltonian(all_cycles);
        }
    }
    return 0;
}
