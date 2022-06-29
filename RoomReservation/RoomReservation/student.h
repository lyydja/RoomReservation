#ifndef STUDENT_H_
#define STUDENT_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "identity.h"
#include "computerroom.h"
#include "globalfile.h"
#include "orderfile.h"

using std::cout;
using std::cin;




class Student : public Identity
{
public:
	Student() {};
	Student(int id, string name, string passWd); //有参构造
	~Student() {};
	virtual void OperMenu(); //菜单界面
	void ApplyOrder();		//申请预约
	void ShowOrder();		//显示自身的预约
	void ShowAllOrder();	//显示所有的预约
	void CancelOrder();		//取消自身的预约

public:
	int m_id; //学号
	vector<ComputerRoom> m_comRoom; //机房容量
};


#endif // !STUDENT_H_

