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
* ��ʦ���幦��
* �鿴���е�ԤԼ --�鿴ȫ��ԤԼ��Ϣ�Լ�ԤԼ״̬
* ���ԤԼ		--��ѧ����ԤԼ�������
* ע����¼ 		--�˳���¼
*/

class Teacher : public Identity
{
public:
	Teacher();
	Teacher(int id, string name, string pwd);
	~Teacher() {};
	virtual void OperMenu(); //�˵�����
	void ShowAllOrder();	//��ʾ���е�ԤԼ
	void ValidOrder();		//���ԤԼ

public:
	int m_empId; //ְ����

};




#endif // !TEACHER_H_
