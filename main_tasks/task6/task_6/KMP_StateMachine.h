#pragma once
#include "PF.h"

class KMP_StateMachine
{
private:
	PF pf;
	int state;

public:
	
	const char* s;
	KMP_StateMachine(const char* s,int sz) {
		state = 0;
		this->s = s;
		pf.Init(s);
	}

	void Accept(char ch) {
		if (IsFinal()) {
			state = 0;
		}
		if (s[state] == ch) {
			state++;
		}
		else {
			state = pf[state];
		}
		
	}

	bool IsFinal() {
		return state == pf;
	}

};

