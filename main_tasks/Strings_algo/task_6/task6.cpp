#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

//O(N^2 * log N)
int distinctWithSet(string str) {
    set<string> result;
    for (int i = 0; i <= str.length(); i++) {
        for (int j = 1; j <= str.length() - i; j++) {
            result.insert(str.substr(i, j));
        }
    }
    return result.size();
}

std::vector<int> prefix_function(std::string s) {
    int n = (int) s.length();
    std::vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

//O(N^2)
int distinctWithPrefixFunc(std::string s) {
    int sol = 0;
    for (int i = 0; i < s.size(); ++i) {
        string x = s.substr(0, i + 1);
        reverse(x.begin(), x.end());
        vector<int> z = prefix_function(x);
        int mx = 0;
        for (int j = 0; j < x.size(); ++j) {
            mx = max(mx, z[j]);
        }
        sol += (i + 1) - mx;
    }
    return sol;
}

int main() {
    std::string s = "abbba";
    prefix_function(s);
    int count = distinctWithPrefixFunc(s);
    std::cout << "O(N^2) Count of Distinct Substrings: " << count << std::endl;

    count = distinctWithSet(s);
    std::cout << "O(N^2 * log N) Count of Distinct Substrings: " << count << std::endl;
    return 0;
}