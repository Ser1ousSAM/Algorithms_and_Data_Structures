#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <vector>

size_t naive(const std::string& str, const std::string& sub)
{
    size_t n = str.size(), m = sub.size(), j = 0;
    for(size_t i = 0; i < n - m + 1; i++)
    {
        for(j = 0; j < m; j++)
        {
            if(str[i + j] != sub[j])
                break;
        }
        if(j == m)
            return i;
    }
    return std::string::npos;
}

/*
bababcbacbcbcabcbabcbabababcaba
0012301201010010123012345456012
*/
std::vector<int> prefix_function(std::string s) {
    int n = (int)s.length();
    std::vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

size_t kmp(const std::string& str, const std::string& sub)
{
    // ваша быстрая реализация KMP
    return std::string::npos;
}

size_t bm(const std::string& str, const std::string& sub)
{
    // ваша быстрая реализация BM
    return std::string::npos;
}



void print(std::vector<int> nums){
    for(auto num : nums){
        std::cout << num << "";
    }
    std::cout << '\n';
}

int main() {

    using namespace std;

    string str, sub = "was born in a small town called Sceptre";
    ifstream fin("/home/gleb/Desktop/University/Algorithms_and_Data_Structures/main_tasks/task6/engwiki_ascii.txt", ios::binary);
    if(!fin.is_open())
    {
        cout << "not open!" << endl;
        return 0;
    }
    str.append((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());

    size_t n = 10;
    std::vector<size_t> times(n), indx(n);

    cout << "\nstd::find\n";
    for(size_t i = 0; i < n; i++)
    {
        auto time_one = chrono::high_resolution_clock::now();
        auto index = str.find(sub);
        if(index == std::string::npos)
            std::cout << "not found\n";
        else
            indx[i] = index;
        auto time_two = chrono::high_resolution_clock::now();
        times[i] = chrono::duration_cast<chrono::nanoseconds>(time_two - time_one).count();
    }
    for(size_t i = 0; i < n; i++)
    {
        cout << indx[i] << '\t' << times[i] << endl;
    }

    cout << "\nnaive\n";
    for(size_t i = 0; i < n; i++)
    {
        auto time_one = chrono::high_resolution_clock::now();
        auto index = naive(str, sub);
        if(index == std::string::npos)
            std::cout << "not found\n";
        else
            indx[i] = index;
        auto time_two = chrono::high_resolution_clock::now();
        times[i] = chrono::duration_cast<chrono::nanoseconds>(time_two - time_one).count();
    }
    for(size_t i = 0; i < n; i++)
    {
        cout << indx[i] << '\t' << times[i] << endl;
    }

    std::string s = "bababcbacbcbcabcbabcbabababcaba";
    std::vector<int> nums = prefix_function(s);
    print (nums);
    return 0;
}
