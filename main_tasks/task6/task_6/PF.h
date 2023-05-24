#pragma once
#ifdef PF_EXPORT
#  define EXPORT __declspec(dllexport)
#else
#  define EXPORT __declspec(dllimport)
#endif

class EXPORT PF
{
	int N = 0;
	int* pv = 0;
public:
	
	PF() {};
	PF(const PF&p); 
	~PF();

	PF&operator = (const PF&) = delete;

	operator int();
	int operator [](int i) const;
	// Инициализирует префикс-функцию строкой s
	void Init(const char *s);
};

