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
	void ShowMainMenu();						//��ʾ�˵�
	void StudentMenu(Identity*& student);		//ѧ���Ӳ˵�
	void TeacherMenu(Identity*& teacher);		//��ʦ�Ӳ˵�
	void AdminMenu(Identity*& admin);			//����Ա�Ӳ˵�
	void LoginIn(string fileName, int type);	//��½����
	
	void Loop(); //������
	void Init(); //��ʼ��
};


#endif // !ROOMRESERV_H_

