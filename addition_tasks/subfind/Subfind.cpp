#include <iostream>
#include <string>
#include <chrono>
#include <fstream>
#include <vector>

using namespace std;

size_t naive(const std::string &str, const std::string &sub)
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

// https://e-maxx.ru/algo/prefix_function

// https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/
size_t kmp(string &txt, const string &pat)
{
	
	
	
	int M = pat.size();
	int N = txt.size();

	int * pi = new int [M];
	pi[0] = 0;
	for(int i = 1; i < M; ++i)
	{
		int j = pi[i - 1];
		while(j > 0 && pat[i] != pat[j])
			j = pi[j - 1];
		if(pat[i] == pat[j]) ++j;
		pi[i] = j;
	}
	
	for(int i = 0; i < M; i++)
	{
		std::cout << pi[i];
	}
	std::cout << std::endl;

	int i = 0;
	int j = 0;
	//while ((N - i) >= (M - j)) {
	/*if (pat[j] == txt[i]) {
	    ++j;
	    ++i;
	}
	if (j == M) {
					delete [] pi;
	    return i - j;
	} else if (i < N && pat[j] != txt[i]) {
	    if (j != 0)
	        j = pi[j - 1];
	    else
	        ++i;
	}*/
	for(int i = 0; i < N; ++i)
	{
		while(j > 0 && txt[i] != pat[j])
			j = pi[j - 1];
		if(txt[i] == pat[j])
			++j;
		if(j == M)
		{
			delete [] pi;
			return i - M + 1;
		}
	}
	delete [] pi;
	return std::string::npos;
}

// https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/
size_t bmSearch(const string &text, const string &pattern)
{
	int m = pattern.size();
	int n = text.size();

	int badchar[128];
	int i;
	for(i = 0; i < 128; i++)
		badchar[i] = -1;
	for(i = 0; i < m; i++)
		badchar[(int) pattern[i]] = i;

	int s = 0;
	while(s <= (n - m))
	{
		int j = m - 1;

		while(j >= 0 && pattern[j] == text[s + j])
			j--;

		if(j < 0)
		{
			return s;
		}
		else
			s += max(1, j - badchar[text[s + j]]);
	}
	return std::string::npos;
}

int main()
{
	using namespace std;

	string str, sub = "assists with 56 the following season";

	string filename = "engwiki_ascii.txt";
	ifstream fin(filename, ios::binary);
	if(!fin.is_open())
	{
		cout << "not open! " << filename << endl;
		return 0;
	}
	str.append((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());

	size_t n = 5;
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
		times[i] = chrono::duration_cast<chrono::milliseconds>(time_two - time_one).count();
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
		times[i] = chrono::duration_cast<chrono::milliseconds>(time_two - time_one).count();
	}
	for(size_t i = 0; i < n; i++)
	{
		cout << indx[i] << '\t' << times[i] << endl;
	}

	cout << "\nKMP\n";
	for(size_t i = 0; i < n; i++)
	{
		auto time_one = chrono::high_resolution_clock::now();
		auto index = kmp(str, sub);
		if(index == std::string::npos)
			std::cout << "not found\n";
		else
			indx[i] = index;
		auto time_two = chrono::high_resolution_clock::now();
		times[i] = chrono::duration_cast<chrono::milliseconds>(time_two - time_one).count();
	}
	for(size_t i = 0; i < n; i++)
	{
		cout << indx[i] << '\t' << times[i] << endl;
	}

	cout << "\nBM\n";
	for(size_t i = 0; i < n; i++)
	{
		auto time_one = chrono::high_resolution_clock::now();
		auto index = bmSearch(str, sub);
		if(index == std::string::npos)
			std::cout << "not found\n";
		else
			indx[i] = index;
		auto time_two = chrono::high_resolution_clock::now();
		times[i] = chrono::duration_cast<chrono::milliseconds>(time_two - time_one).count();
	}
	for(size_t i = 0; i < n; i++)
	{
		cout << indx[i] << '\t' << times[i] << endl;
	}
	return 0;
}

/*
link:
https://ru.wikibooks.org/wiki/%D0%A0%D0%B5%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D0%B8_%D0%B0%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC%D0%BE%D0%B2/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%91%D0%BE%D0%B9%D0%B5%D1%80%D0%B0_%E2%80%94_%D0%9C%D1%83%D1%80%D0%B0
*/
