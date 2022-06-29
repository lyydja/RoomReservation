#ifndef IDENTITY_H_
#define IDENTITY_H_

#include <iostream>
using namespace std;

//职工抽象类
class Identity {
public:
	virtual void OperMenu() = 0;
	string m_name;	//用户名
	string m_passWd;	//密码
};



#endif

