#ifndef ROOMRESERV_H_
#define ROOMRESERV_H_

#include <iostream>
#include "identity.h"
#include "student.h"
#include "teacher.h"
#include "admin.h"
using std::cout;
using std::cin;

class RoomReserv
{
public:
	RoomReserv() {};
	~RoomReserv() {};
	void ShowMainMenu();						//显示菜单
	void StudentMenu(Identity*& student);		//学生子菜单
	void TeacherMenu(Identity*& teacher);		//教师子菜单
	void AdminMenu(Identity*& admin);			//管理员子菜单
	void LoginIn(string fileName, int type);	//登陆功能
	
	void Loop(); //主流程
	void Init(); //初始化
};


#endif // !ROOMRESERV_H_

