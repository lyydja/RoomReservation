#ifndef ORDERFILE_H_
#define ORDERFILE_H_

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include "globalfile.h"

using namespace std;

class OrderFile
{
public:
	OrderFile();
	void UpdateOrder();							//����ԤԼ��¼
	int m_size;									//��¼ԤԼ����
	map<int, map<string, string>> m_orderData; //��¼����ԤԼ��Ϣ������ key��¼���� valueΪ��ֵ����Ϣ
};



#endif // !ORDERFILE_H_
