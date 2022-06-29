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
* ����Ա���幦��
* ����˺� 		--���ѧ�����ʦ���˺ţ���Ҫ���ѧ����Ż��ְ�����Ƿ��ظ�
* �鿴�˺�		--����ѡ��鿴ѧ�����ʦ��ȫ����Ϣ
* �鿴����		--�鿴���л�������Ϣ
* ���ԤԼ		--�������ԤԼ��¼
* ע����¼		--�˳���¼
*/


class Admin :public Identity
{
public:
	Admin();
	Admin(string name, string pwd);
	~Admin() {};
	virtual void OperMenu();	//�˵�����
	void AddPerson();			//����˺�
	void ShowPerson();			//��ʾ�˺�
	void ShowComputerRoom();	//��ʾ������Ϣ
	void CleanOrder();			//���ԤԼ
	bool CheckRepeat(int id, int option); //����˺��Ƿ��ظ�
	void InitVector();			//��ʼ�������ӿ�
public:
	vector<Student> m_vStu;			//ѧ������
	vector<Teacher> m_vTea;			//��ʦ����
	vector<ComputerRoom> m_vCom;	//������Ϣ����

};


#endif // !ADMIN_H_
