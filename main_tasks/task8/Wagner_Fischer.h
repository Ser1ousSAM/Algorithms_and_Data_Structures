#pragma once

class WF
{
public:
	WF() {
		pm = nullptr;
		M = N = 0;
	}
	WF(const WF&) = delete;
	int* pm;
	int M, N;
	std::string s;
	std::string t;
	void Init(const char* sc, const char* tc) {
		if (pm != nullptr) {
			delete[] pm;
			M = N = 0;
		}
		s = std::string(sc);
		t = std::string(tc);
		M = s.length() + 1;
		N = t.length() + 1;
		pm = new int[M * N];
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < N; j++) {
				if (i == 0) {
					pm[i * N + j] = j;
				}
				else if (j == 0) {
					pm[i * N + j] = i;
				}
				else {
					int cost = (s[i - 1] == t[j - 1]) ? 0 : 1;
					pm[i * N + j] = std::min(pm[(i - 1) * N + j] + 1,
						std::min(pm[i * N + (j - 1)] + 1,
							pm[(i - 1) * N + (j - 1)] + cost));
				}
			}
		}
	}
	int Rows() const {
		return M;
	}
	int Columns() const {
		return N;
	}
	int Get(int i, int j) const {
		if (i >= M || j >= N) {
			throw std::out_of_range("get: index out of range");
		}
		return pm[i * N + j];
	}
	void Set(int i, int j, int val) {
		if (i >= M || j >= N) {
			throw std::out_of_range("set: index out of range");
		}
		pm[i * N + j] = val;
	}
	int Distance() const {
		return pm[M * N - 1];
	}
	~WF() {
		delete[] pm;
	}

};

