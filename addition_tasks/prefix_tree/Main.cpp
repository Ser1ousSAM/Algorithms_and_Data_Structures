#include <iostream>
#include <string>
#include <chrono>
#include <unordered_map>
#include <fstream>
#include "PrefixTree.h"

void triedict(const std::string& text, std::string word)
{
    using namespace std;
    PrefixTree tree = PrefixTree();
    string str = "";
    for (const auto& ch : text)
    {
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '\'')
            str += ch;
        else if (str.size() > 0)
        {
            tree.insert(str);
            str = "";
        }
    }
    cout << "\ndict size: " << tree.size() << endl;
    cout << word << ": " << tree.find(word) << endl;
}

int main()
{
    using namespace std;
    string text;
    ifstream fin("engwiki_ascii.txt", ios::binary);
    if (!fin.is_open())
    {
        cout << "not open!" << endl;
        return 0;
    }
    text.append((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());

    string word = "wiki"; // finding word
    auto time_one = chrono::steady_clock::now();
    triedict(text, word);
    auto time_two = chrono::steady_clock::now();
    cout << "triedict  " << chrono::duration_cast<chrono::microseconds>(time_two - time_one).count() / 1e6 << " sec\n";
}