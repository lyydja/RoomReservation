#ifndef ADMIN_H_
#define ADMIN_H_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "identity.h"
#include "computerroom.h"
#include "globalfile.h"
#include "student.h"
#include "teacher.h"


/*
* 管理员具体功能
* 添加账号 		--添加学生或教师的账号，需要检测学生编号或教职工号是否重复
* 查看账号		--可以选择查看学生或教师的全部信息
* 查看机房		--查看所有机房的信息
* 清空预约		--清空所有预约记录
* 注销登录		--退出登录
*/


class Admin :public Identity
{
public:
	Admin();
	Admin(string name, string pwd);
	~Admin() {};
	virtual void OperMenu();	//菜单界面
	void AddPerson();			//添加账号
	void ShowPerson();			//显示账号
	void ShowComputerRoom();	//显示机房信息
	void CleanOrder();			//清空预约
	bool CheckRepeat(int id, int option); //检查账号是否重复
	void InitVector();			//初始化容器接口
public:
	vector<Student> m_vStu;			//学生容器
	vector<Teacher> m_vTea;			//教师容器
	vector<ComputerRoom> m_vCom;	//机房信息容器

};


#endif // !ADMIN_H_
