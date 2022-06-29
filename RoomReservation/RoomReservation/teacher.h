#ifndef TEACHER_H_
#define TEACHER_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "identity.h"
#include "computerroom.h"
#include "globalfile.h"
#include "orderfile.h"

/*
* 教师具体功能
* 查看所有的预约 --查看全部预约信息以及预约状态
* 审核预约		--对学生的预约进行审核
* 注销登录 		--退出登录
*/

class Teacher : public Identity
{
public:
	Teacher();
	Teacher(int id, string name, string pwd);
	~Teacher() {};
	virtual void OperMenu(); //菜单界面
	void ShowAllOrder();	//显示所有的预约
	void ValidOrder();		//审核预约

public:
	int m_empId; //职工号

};




#endif // !TEACHER_H_
