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
	void UpdateOrder();							//更新预约记录
	int m_size;									//记录预约条数
	map<int, map<string, string>> m_orderData; //记录所有预约信息的容器 key记录条数 value为键值对信息
};



#endif // !ORDERFILE_H_
