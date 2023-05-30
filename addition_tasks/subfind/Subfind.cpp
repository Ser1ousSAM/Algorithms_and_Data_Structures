#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

size_t naive(const std::string &str, const std::string &sub) {
    size_t n = str.size(), m = sub.size(), j = 0;
    for (size_t i = 0; i < n - m + 1; i++) {
        for (j = 0; j < m; j++) {
            if (str[i + j] != sub[j])
                break;
        }
        if (j == m)
            return i;
    }
    return std::string::npos;
}

// https://e-maxx.ru/algo/prefix_function
vector<int> prefix_function(string s) {
    int n = (int) s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; ++i) {
        int j = pi[i - 1];
        while (j > 0 && s[i] != s[j])
            j = pi[j - 1];
        if (s[i] == s[j]) ++j;
        pi[i] = j;
    }
    return pi;
}

//find the first occurrence of sub
size_t kmp(const std::string &str, const std::string &sub) {
    auto n = (long long) sub.length();
    string merged_str = sub + "#" + str;
    vector<int> pi = prefix_function(merged_str);
    for (long long i = n + 1; i < merged_str.length(); ++i) {
        if (pi[i] == n)
            //to find all occurrence of sub just add all i-th in vector
            return i - 2 * n;
    }
    return -1;
}

size_t bmOptimised(const std::string &str, const std::string &sub) {
    if (str.length() < sub.length()) {
        return -1;
    }

    if (!sub.length()) {
        return str.length(); //сыс
    }

    typedef unordered_map<char, int> TStopTable;
    typedef unordered_map<int, int> TSufficsTable;
    TStopTable stop_table;
    TSufficsTable suffics_table;

    for (int i = 0; i < sub.length(); ++i) {
        stop_table[sub[i]] = i;
    }

    string rt(sub.rbegin(), sub.rend());
    vector<int> p = prefix_function(sub), pr = prefix_function(rt);
    for (int i = 0; i < sub.length() + 1; ++i) {
        suffics_table[i] = sub.length() - p.back();
    }

    for (int i = 1; i < sub.length(); ++i) {
        int j = pr[i];
        suffics_table[j] = min(suffics_table[j], i - pr[i] + 1);
    }

    for (int shift = 0; shift <= str.length() - sub.length();) {
        int pos = sub.length() - 1;

        while (sub[pos] == str[pos + shift]) {
            if (pos == 0) return shift;
            --pos;
        }

        if (pos == sub.length() - 1) {
            TStopTable::const_iterator stop_symbol = stop_table.find(str[pos + shift]);
            int stop_symbol_additional = pos - (stop_symbol != stop_table.end() ? stop_symbol->second : -1);
            shift += stop_symbol_additional;
        } else {
            shift += suffics_table[sub.length() - pos - 1];
        }
    }
    return -1;
}

size_t bmDefault(const std::string &str, const std::string &sub) {
    // Этап 1: формирование таблицы смещений
    std::unordered_set<char> S;  // уникальные символы в образе
    int M = sub.length();           // число символов в образе
    std::unordered_map<char, int> d; // словарь смещений

    for (int i = M - 2; i >= 0; --i) {  // итерации с предпоследнего символа
        if (S.count(sub[i]) == 0) {    // если символ еще не добавлен в таблицу
            d[sub[i]] = M - i - 1;
            S.insert(sub[i]);
        }
    }

    if (S.count(sub[M - 1]) == 0) {     // отдельно формируем последний символ
        d[sub[M - 1]] = M;
    }

    d['*'] = M;                     // смещения для прочих символов

    // Этап 2: поиск образа в строке
    int N = str.length();
    int i = M - 1;

    if (N >= M) {
        while (i < N) {
            int k = 0;
            int j = 0;
            bool flBreak = false;
            for (j = M - 1; j >= 0; --j) {
                if (str[i - k] != sub[j]) {
                    int off;
                    if (j == M - 1) {
                        off = d.count(str[i]) ? d[str[i]] : d['*']; // смещение, если не равен последний символ образа
                    } else {
                        off = d[sub[j]]; // смещение, если не равен не последний символ образа
                    }
                    i += off;   // смещение счетчика строки
                    flBreak = true; // если несовпадение символа, то flBreak = true
                    break;
                }
                ++k;    // смещение для сравниваемого символа в строке
            }

            if (!flBreak) { // если дошли до начала образа, значит, все его символы совпали
                return i - k + 1;
            }
        }
    }
    return -1;
}

int main() {
    using namespace std;

    string str, sub = "was born in a small town called Sceptre";

    string filename = "engwiki_ascii.txt";
    ifstream fin(filename, ios::binary);
    if (!fin.is_open()) {
        cout << "not open! " << filename << endl;
        return 0;
    }
    str.append((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());

    size_t n = 10;
    std::vector<size_t> times(n), indx(n);

    cout << "\nstd::find\n";
    for (size_t i = 0; i < n; i++) {
        auto time_one = chrono::high_resolution_clock::now();
        auto index = str.find(sub);
        if (index == std::string::npos)
            std::cout << "not found\n";
        else
            indx[i] = index;
        auto time_two = chrono::high_resolution_clock::now();
        times[i] = chrono::duration_cast<chrono::milliseconds>(time_two - time_one).count();
    }
    for (size_t i = 0; i < n; i++) {
        cout << indx[i] << '\t' << times[i] << endl;
    }

    cout << "\nnaive\n";
    for (size_t i = 0; i < n; i++) {
        auto time_one = chrono::high_resolution_clock::now();
        auto index = naive(str, sub);
        if (index == std::string::npos)
            std::cout << "not found\n";
        else
            indx[i] = index;
        auto time_two = chrono::high_resolution_clock::now();
        times[i] = chrono::duration_cast<chrono::milliseconds>(time_two - time_one).count();
    }
    for (size_t i = 0; i < n; i++) {
        cout << indx[i] << '\t' << times[i] << endl;
    }

    cout << "\nKMP\n";
    for (size_t i = 0; i < n; i++) {
        auto time_one = chrono::high_resolution_clock::now();
        auto index = kmp(str, sub);
        if (index == std::string::npos)
            std::cout << "not found\n";
        else
            indx[i] = index;
        auto time_two = chrono::high_resolution_clock::now();
        times[i] = chrono::duration_cast<chrono::milliseconds>(time_two - time_one).count();
    }
    for (size_t i = 0; i < n; i++) {
        cout << indx[i] << '\t' << times[i] << endl;
    }

    cout << "\nBM Бойер — Мур — Хорспул\n";
    for (size_t i = 0; i < n; i++) {
        auto time_one = chrono::high_resolution_clock::now();
        auto index = bmDefault(str, sub);
        if (index == std::string::npos)
            std::cout << "not found\n";
        else
            indx[i] = index;
        auto time_two = chrono::high_resolution_clock::now();
        times[i] = chrono::duration_cast<chrono::milliseconds>(time_two - time_one).count();
    }
    for (size_t i = 0; i < n; i++) {
        cout << indx[i] << '\t' << times[i] << endl;
    }

    cout << "\nBM Optimised\n";
    for (size_t i = 0; i < n; i++) {
        auto time_one = chrono::high_resolution_clock::now();
        auto index = bmOptimised(str, sub);
        if (index == std::string::npos)
            std::cout << "not found\n";
        else
            indx[i] = index;
        auto time_two = chrono::high_resolution_clock::now();
        times[i] = chrono::duration_cast<chrono::milliseconds>(time_two - time_one).count();
    }
    for (size_t i = 0; i < n; i++) {
        cout << indx[i] << '\t' << times[i] << endl;
    }

    return 0;
}

/*
link:
https://ru.wikibooks.org/wiki/%D0%A0%D0%B5%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D0%B8_%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D0%BE%D0%B2/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%91%D0%BE%D0%B9%D0%B5%D1%80%D0%B0_%E2%80%94_%D0%9C%D1%83%D1%80%D0%B0
*/
