// Practice.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <memory>

using namespace std;

class Function;

class Variable {
public:	
	float a = 0;
	Function *creator = NULL;

	Variable(float a) {
		this->a = a;
	}
};

using PVariable = shared_ptr<Variable>;


class Function {
public:
	vector<PVariable> v;
	PVariable forward(PVariable v1, PVariable v2) {

		v.push_back(v1);
		v.push_back(v2);

		PVariable pv = PVariable(new Variable(0));
		pv->creator = this;
		pv->a += v1->a;
		pv->a += v2->a;

		return pv;
	}

	PVariable forward(PVariable v1) {
		v.push_back(v1);

		PVariable pv = PVariable(new Variable(0));
		pv->creator = this;
		pv->a += v1->a;

		return pv;
	}
};

void traverse(PVariable v) {
	cout << v->a << endl;
	Function *f = v->creator;
	if (f == NULL) return;

	for (int i = 0; i < f->v.size(); i++) {
		traverse(f->v[i]);
	}
}

int main(void)
{
	PVariable v1 = PVariable(new Variable(1));
	PVariable v2 = PVariable(new Variable(1));
	Function *f1 = new Function();
	Function *f2 = new Function();
	Function *f3 = new Function();

	PVariable r1 = f1->forward(v1, v2);
	PVariable r2 = f2->forward(r1);
	PVariable r3 = f3->forward(r2);

	traverse(r3);

	return 0;
}