#include "student.h"
using namespace std;


Student::Student(int id, string name, string passWd) {
	//初始化属性
	this->m_id = id;
	this->m_name = name;
	this->m_passWd = passWd;

	//初始化机房信息
	ifstream ifs;
	ifs.open(COMPUTERROOM_FILE, ios::in);

	ComputerRoom com;
	while (ifs >> com.m_ComId && ifs >> com.m_maxNum) {
		m_comRoom.push_back(com);
	}
	ifs.close();
}

//菜单界面
void Student::OperMenu() {
	cout << endl;
	cout << "欢迎学生代表：" << this->m_name << "登录！" << endl;
	cout << "\t\t ----------------------------------\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          1.申请预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          2.查看我的预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          3.查看所有预约          |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          4.取消预约              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t|          0.注销登录              |\n";
	cout << "\t\t|                                  |\n";
	cout << "\t\t ----------------------------------\n";
	cout << "请选择您的操作： " << endl;
}

//申请预约
void Student::ApplyOrder() {
	cout << "机房开放时间为周一至周五" << endl;
	cout << "请输入申请预约的时间：" << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;

	int date = 0;		//日期
	int interval = 0;	//时间段
	int room = 0;		//机房编号

	while (true) {
		cin >> date;
		if (date >= 1 && date <= 5) {
			break;
		}
		//如果输入有错误
		cout << "输入有错误，请重新输入" << endl;
		//清空输入缓冲区,防止非数字的输入残存
		cin.clear();
		cin.ignore();
	}

	cout << "请输入申请预约时间段：" << endl;
	cout << "1、上午" << endl;
	cout << "2、下午" << endl;
	while (true) {
		cin >> interval;
		if (interval >= 1 && interval <= 2) {
			break;
		}
		//如果输入有错误
		cout << "输入有错误，请重新输入" << endl;
		//清空输入缓冲区,防止非数字的输入残存
		cin.clear();
		cin.ignore();
	}

	cout << "请选择机房：" << endl;
	for (int i = 0; i < m_comRoom.size(); i++) {
		cout << m_comRoom[i].m_ComId << "号机房容量为："
			<< m_comRoom[i].m_maxNum << endl;
	}
	while (true) {
		cin >> room;
		if (room >= 1 && room <= m_comRoom.size()) {
			break;
		}
		//如果输入有错误
		cout << "输入有错误，请重新输入" << endl;
		//清空输入缓冲区,防止非数字的输入残存
		cin.clear();
		cin.ignore();
	}

	cout << "预约成功！等待审核中" << endl;

	//保存在文件中
	ofstream ofs;
	ofs.open(ORDER_FILE, ios::app);

	ofs << "date:" << date << " "
		<< "interval:" << interval << " "
		<< "stuId:" << this->m_id << " "
		<< "stuName:" << this->m_name << " "
		<< "roomId:" << room << " "
		<< "status:" << 1 << endl;		// 1 审核中  2 已预约  -1 预约失败  0 取消预约
	ofs.close();

	system("pause");
	system("cls");	
}

//显示自身的预约
void Student::ShowOrder() {
	OrderFile of;

	if (of.m_size == 0) {
		cout << "无预约记录!" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = 0; i < of.m_size; i++) {
		if (this->m_id == atoi(of.m_orderData[i]["stuId"].c_str())) {
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
			else if("-1" == of.m_orderData[i]["status"]) {
				status += "预约失败";
			}
			else {
				status += "预约已取消";
			}
			cout << status << endl;
		}
	}

	system("pause");
	system("cls");
}

//显示所有的预约
void Student::ShowAllOrder() {
	OrderFile of;

	if (of.m_size == 0) {
		cout << "无预约记录!" << endl;
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

//取消自身的预约，预约成功或审核中的预约均可取消预约
void Student::CancelOrder() {
	
	//获取自身审核中或预约成功的预约记录
	OrderFile of;
	if (of.m_size == 0) {
		cout << "无预约记录!" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "审核中或预约成功的记录可以取消，可以取消的记录如下：" << endl;
	vector<int> v; //存放可以取消的预约记录在OrderFile中的索引
	int index = 1;
	for (int i = 0; i < of.m_size; i++) {
		//显示自身预约
		if (this->m_id == atoi(of.m_orderData[i]["stuId"].c_str())) {
			//显示预约成功或审核中的预约
			if (("1" == of.m_orderData[i]["status"]) || ("2" == of.m_orderData[i]["status"])) {
				v.emplace_back(i);
				cout << index++ << "、";
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
				cout << status << endl;
			}
		}
	}

	if (index == 1) {
		cout << "-----无可取消记录-----" << endl;
		cout << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "请输入取消的记录，0代表返回" << endl;
	int option = 0;
	while (true) {
		cin >> option;

		if (option >= 0 && option <= v.size()) {
			//返回
			if (option == 0) {
				
				break;
			}
			else {
				of.m_orderData[v[option - 1]]["status"] = "0";
				of.UpdateOrder(); //更新记录
				cout << "已取消预约" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入" << endl;
		//清空输入缓冲区,防止非数字的输入残存
		cin.clear();
		cin.ignore();
	}
	system("pause");
	system("cls");
}