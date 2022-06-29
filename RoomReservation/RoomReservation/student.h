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
	Student(int id, string name, string passWd); //�вι���
	~Student() {};
	virtual void OperMenu(); //�˵�����
	void ApplyOrder();		//����ԤԼ
	void ShowOrder();		//��ʾ�����ԤԼ
	void ShowAllOrder();	//��ʾ���е�ԤԼ
	void CancelOrder();		//ȡ�������ԤԼ

public:
	int m_id; //ѧ��
	vector<ComputerRoom> m_comRoom; //��������
};


#endif // !STUDENT_H_

