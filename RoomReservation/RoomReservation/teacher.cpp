#include "teacher.h"


Teacher::Teacher() {

}

Teacher::Teacher(int id, string name, string pwd) {
	this->m_empId = id;
	this->m_name = name;
	this->m_passWd = pwd;
}
//菜单界面
void Teacher::OperMenu() {
	cout << endl;
	cout << "欢迎教师：" << this->m_name << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.查看所有预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.审核预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

//显示所有的预约
void Teacher::ShowAllOrder() {
	OrderFile of;
	if (of.m_size == 0) {
		cout << "无预约记录" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_size; i++) {
		cout << i + 1 << "、 ";
		cout << "预约日期：周" << of.m_orderData[i]["date"];
		cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
		cout << " 机房号：" << of.m_orderData[i]["roomId"];
		string status = " 状态：";
		// 1 审核中  2 已预约  -1 预约失败  0 取消预约
		if ("1" == of.m_orderData[i]["status"]) {
			status += "审核中";
		}
		else if ("2" == of.m_orderData[i]["status"]) {
			status += "预约成功";
		}
		else if ("-1" == of.m_orderData[i]["status"]) {
			status += "预约失败";
		}
		else {
			status += "预约已取消";
		}
		cout << status << endl;
	}

	system("pause");
	system("cls");
}

//审核预约
void Teacher::ValidOrder() {
	//获取处于审核中的预约记录
	OrderFile of;
	if (of.m_size == 0) {
		cout << "无预约记录!" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "待审核的记录如下：" << endl;
	vector<int> v; //存放可以取消的预约记录在OrderFile中的索引
	int index = 0;
	
	for (int i = 0; i < of.m_size; i++) {
		//显示待审核的预约
		if ("1" == of.m_orderData[i]["status"]) {
			v.emplace_back(i);
			cout << ++index << "、";
			cout << "预约日期：周" << of.m_orderData[i]["date"];
			cout << " 时间段：" << (of.m_orderData[i]["interval"] == "1" ? "上午" : "下午");
			cout << " 机房号：" << of.m_orderData[i]["roomId"];
			string status = " 状态：审核中";
			cout << status << endl;
		}
	}

	cout << "请输入审核的记录，0代表返回" << endl;
	int option = 0;
	int ret = 0; //保存预约结果
	while (true) {
		cin >> option;

		if (option >= 0 && option <= v.size()) {
			//返回
			if (option == 0) {
				break;
			}
			else {
				cout << "请输入审核结果：" << endl;
				cout << "1、通过" << endl;
				cout << "2、不通过" << endl;
				cin >> ret;
				while (cin.fail()) {
					cin.clear();
					cin.ignore();
					cout << "输入格式有误，请重新输入" << endl;
					cin >> ret;
				}
				//预约通过
				if (ret == 1) {
					of.m_orderData[v[option - 1]]["status"] = "2";
				}
				//预约不通过
				else {
					of.m_orderData[v[option - 1]]["status"] = "-1";
				}
				of.UpdateOrder(); //更新预约记录
				cout << "审核完毕" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入" << endl;
	}
	system("pause");
	system("cls");
}